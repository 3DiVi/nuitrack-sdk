#include "NiGLSample.h"

#include <GL/glut.h>

#include <iostream>

NiGLSample sample;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	{
		sample.release();
		glutDestroyWindow(glutGetWindow());
		exit(EXIT_FAILURE);
	}

	default:
	{
		break;
	}
	}
}

void display()
{
	bool update = sample.update();

	if (!update)
	{
		sample.release();
		glutDestroyWindow(glutGetWindow());
		exit(EXIT_FAILURE);
	}

	glFlush();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void showHelpInfo()
{
	std::cout << "Press Esc to close window." << std::endl;
}

int main(int argc, char* argv[])
{
	showHelpInfo();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Nuitrack GL Sample (OpenNI API)");
	glutSetCursor(GLUT_CURSOR_NONE);

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glOrtho(0, 640, 480, 0, -1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	sample.init();

	glutMainLoop();

	return 0;
}
