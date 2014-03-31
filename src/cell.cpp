#include "cell.hpp"

#include <GL/gl.h>
#include <GL/freeglut.h>

void cell::draw(int x_off, int y_off)
{
	if (b_state == UNBURNT) {
		glColor3ub(0xf5,0xef,0xce);
		// if (90 <= x and x <=100 and 90 <= y and y <= 100)
		// 	glColor3ub(0,0,0);
		glRecti(
			x_off + x,
			y_off + y,
			x_off + x+1,
			y_off + y+1);
	}
}