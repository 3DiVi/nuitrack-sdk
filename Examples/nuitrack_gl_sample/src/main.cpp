#include "NuitrackGLSample.h"
#include <GL/freeglut.h>
#include <iostream>

NuitrackGLSample sample;

void closeWindow()
{
	sample.release();
	glutDestroyWindow(glutGetWindow());
	exit(EXIT_FAILURE);
}

// Keyboard handler
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	// On Esc key press
	case 27:
	{
		closeWindow();
	}

	default:
	{
		// Do nothing otherwise
		break;
	}
	}
}

void mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		sample.nextViewMode();
	}
}

// Update tracking data and visualize it
void display()
{
	// Delegate this action to example's main class
	bool update = sample.update();
	if (!update)
	{
		// End the work if update failed
		closeWindow();
	}

	// Do flush and swap buffers to update viewport
	glFlush();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void showHelpInfo()
{
	std::cout << "Usage: nuitrack_gl_sample [path/to/nuitrack.config]\n"
				 "Press Esc to close window." << std::endl;
}

int main(int argc, char* argv[])
{
	showHelpInfo();
	
	// Prepare sample to work
	if (argc < 2)
		sample.init();
	else
		sample.init(argv[1]);

	auto outputMode = sample.getOutputMode();

	// Initialize GLUT window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(outputMode.xres, outputMode.yres);
	glutCreateWindow("Nuitrack GL Sample (Nuitrack API)");
	//glutSetCursor(GLUT_CURSOR_NONE);

	// Connect GLUT callbacks
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouseClick);
	glutCloseFunc(closeWindow);
	
	// Setup OpenGL
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


	glOrtho(0, outputMode.xres, outputMode.yres, 0, -1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	// Start main loop
	glutMainLoop();

	return 0;
}
