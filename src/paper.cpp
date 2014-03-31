#include "paper.hpp"
#include "cell.hpp"

#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <unistd.h>

using namespace std;

paper::paper(int xx, int yy, int ss/*=300*/)
{
	x = xx;
	y = yy;

	s = ss;
	cells = new cell*[s];
	for (int i = 0 ; i < s ; i++) {
		cells[i] = new cell[s];
		for (int j = 0 ; j < s ; j++)
			cells[i][j].set_xy(i,j);
	}
}

paper::~paper()
{

}

void paper::draw()
{
	// glRecti(x,y,x+s,y+s);
	for (int i = 0 ; i < s ; i++) {
		for (int j = 0; j < s; j++) {
			cells[i][j].draw(x, y);
		}
	}
}

void paper::update(bool burn)
{
	if (burn)
	{
		cout << "Burning!" << endl;
		sleep(1);
		glutPostRedisplay();
	}
}