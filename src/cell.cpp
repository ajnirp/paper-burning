#include "cell.hpp"

#include <GL/gl.h>
#include <GL/freeglut.h>

#include <vector>

void cell::draw(int x_off, int y_off)
{
	/* Set color */
	if (b_state == UNBURNT)
		glColor3ub(0xf5,0xef,0xce);
	else if (b_state == BURNT)
		glColor3ub(0,0,0);
	else if (b_state == BURNING) {
		glColor3ub(0xff,0,0);
	}

	/* Draw the cell */
	glRecti(x_off + x,
			y_off + y,
			x_off + x+1,
			y_off + y+1);
}

/* check if burning time is over and set to BURNT if need be */
void cell::check_burnt(int t)
{
	if (t >= burn_start + burn_duration)
		b_state = BURNT;
}

/* Set the cell to start burning at time t (now) */
void cell::set_burning(int t)
{
	burn_start = t;
	b_state = BURNING;
}