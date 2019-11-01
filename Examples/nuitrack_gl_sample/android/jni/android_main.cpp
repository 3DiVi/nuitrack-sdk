#include "NuitrackGLSample.h"

#include <EGL/egl.h>
#include <android_native_app_glue.h>

#include <cstdlib>
#include <memory>

struct engine
{
	struct android_app* app;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	bool update;

	std::unique_ptr<NuitrackGLSample> sample;
};

int init_display(struct engine* engine)
{
	engine->sample.reset(new NuitrackGLSample);
	engine->sample->init();

	auto outputMode = engine->sample->getOutputMode();

	const EGLint attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_NONE, EGL_NONE
	};

	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
	context = eglCreateContext(display, config, NULL, NULL);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrthof(0, outputMode.xres, outputMode.yres, 0, -1, 1);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	return 0;
}

void term_display(struct engine* engine)
{
	if (engine->display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
				EGL_NO_CONTEXT);

		if (engine->context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(engine->display, engine->context);
		}

		if (engine->surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(engine->display, engine->surface);
		}

		eglTerminate(engine->display);
	}

	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;

	if (engine->sample)
		engine->sample->release();

	exit(0);
}

void draw_frame(struct engine* engine)
{
	if (engine->app->window == NULL && engine->display == EGL_NO_DISPLAY)
	{
		return;
	}

	engine->update = engine->sample->update();

	glFlush();
	eglSwapBuffers(engine->display, engine->surface);
}

void handle_cmd(android_app* app, int32_t cmd)
{
	struct engine* engine = (struct engine*) app->userData;
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		if (engine->app->window != NULL)
		{
			init_display(engine);
		}
		break;

	case APP_CMD_TERM_WINDOW:
		term_display(engine);
		break;
	}
}

int32_t handle_input_event(struct android_app *application, AInputEvent * event)
{
	struct engine * engine = static_cast<struct engine *>(application->userData);
	int32_t et = AInputEvent_getType(event);

	switch ( et )
	{
		case AINPUT_EVENT_TYPE_MOTION:
		{
			switch ( AInputEvent_getSource(event) )
			{
				case AINPUT_SOURCE_TOUCHSCREEN:
				case AINPUT_SOURCE_MOUSE:
				case AINPUT_SOURCE_TOUCHPAD:
					if ( AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN )
					{
						engine->sample->nextViewMode();
					}
					break;
				default:
					break;
			}
			break;
		}
		default:
			break;
	}
	return 0;
}

void android_main(android_app* app)
{
	struct engine engine;

	app_dummy();

	memset(&engine, 0, sizeof(engine));
	app->userData = &engine;
	app->onAppCmd = handle_cmd;
	engine.app = app;
	engine.update = true;
	engine.app->onInputEvent = handle_input_event;

	while (true)
	{
		int ident;
		int events;
		android_poll_source* source;

		while ((ident = ALooper_pollAll(0, NULL, &events, (void**) &source))
				>= 0)
		{
			if (source != NULL)
			{
				source->process(app, source);
			}

			if (app->destroyRequested != 0)
			{
				term_display(&engine);
				return;
			}
		}

		if (!engine.update)
		{
			term_display(&engine);
			return;
		}

		draw_frame(&engine);
	}
}
