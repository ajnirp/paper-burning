#include <iostream>
#include <vector>
#include <utility>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "cell.hpp"
#include "paper.hpp"

using namespace std;

/* Global variables */
int windowId;
int window_height = 400;
int window_width = 400;
bool burning = false;
paper p(50,50,300);
vector<pair<int,int> > burn_start;

/* Callbacks */
void display()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	p.update(burning);
	p.draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	if (h == 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, w, 0.0, h, -1., 1.);
	glViewport(0, 0, w, h);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			cout << "Caught escape key" << endl;
			glutDestroyWindow(windowId);
			break;

		case ' ':
			cout << "Caught spacebar key" << endl;
			if (burn_start.empty())
				cout << "No points to burn!" << endl;
			else {
				cout << "Toggling burning: now ";
				burning = not burning;
				cout << (burning ? "ON" : "OFF") << endl;
			}
			glutPostRedisplay();
			break;
	}
}

void special(int key, int x, int y) {}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN and button == GLUT_DOWN)
	{
		if (not burning) {
			cout << "Added: " << x << " " << window_width - y << " to burn start" << endl;
			pair<int,int> temp(x, window_width - y);
			burn_start.push_back(temp);
		}
		else {
			cout << "Cannot add point while burning is going on" << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(window_height, window_width);
	glutInitWindowPosition(0, 0);

	windowId = glutCreateWindow("Paper Burning");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	glutMainLoop();

	cout << "Exited cleanly" << endl;
	return 0;
}