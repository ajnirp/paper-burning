#include <iostream>
#include <vector>
#include <utility>
#include <unistd.h>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "cell.hpp"
#include "paper.hpp"
#include "misc.hpp"

#define FRAMES_PER_SECOND 30

using namespace std;

/* Global variables */
int window_id;
int window_height = 400;
int window_width = 400;
bool burning = false;
int paper_side = 300;
paper p(50,50,"spreadvel.tex", paper_side);
vector<pair<int,int> > burn_points;
int sim_time = 0;

/* Callbacks */
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);

/* Callback definitions */
void display()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	p.draw(sim_time);

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
			glutDestroyWindow(window_id);
			break;

		case ' ':
			if (not burning) {
				cout << "Caught spacebar key" << endl;
				if (burn_points.empty())
					cout << "No points to burn!" << endl;
				else {
					burning = true;
					p.start_burning(burn_points);
					glutTimerFunc(0,timer,0);

				}
				glutPostRedisplay();
			}
			break;

		case 'f':
			if (burning) {
				p.print_burning();
			}
			break;
	}
}

void special(int key, int x, int y) {}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN and button == GLUT_DOWN)
	{
		if (not burning) {
			if (p.contains(x, window_width - y)) {
				cout << "Added: " << x << " " << window_width - y << " to burn start" << endl;
				pair<int,int> temp(x - p.get_x(), window_width - y - p.get_y());
				burn_points.push_back(temp);
			}
			else cout << "Clicked outside paper" << endl;
		}
		else {
			if (p.contains(x, window_width - y)) {
				pair<int,int> temp(x - p.get_x(), window_width - y - p.get_y());
				p.start_burning(temp, sim_time);
			}
			else cout << "Clicked outside paper" << endl;
		}
	}
}

void timer(int value)
{
	sim_time = value;
	p.update(value);
	glutPostRedisplay();
	glutTimerFunc(1000.f/FRAMES_PER_SECOND, timer, value+1);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(window_height, window_width);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_width)/2, (glutGet(GLUT_SCREEN_HEIGHT)-window_height)/2);

	window_id = glutCreateWindow("Paper Burning");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	glutMainLoop();

	write_texture("spreadvel.tex", paper_side);

	cout << "Exited cleanly" << endl;
	return 0;
}