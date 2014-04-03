#include "cell.hpp"

#include <GL/gl.h>
#include <GL/freeglut.h>

#include <vector>

cell::cell()
{
	b_state = UNBURNT;
	burn_duration = 10;
	char_threshold = 10;
	char_color = color(0xf8,0x52,0x11);
	burn_color = color(0xff,0,0);
}

void cell::draw(int x_off, int y_off, int t)
{
	/* Set color */
	if (b_state == UNBURNT) {
		glColor3ub(0xf5,0xef,0xce);
	}
	else if (b_state == BURNT) {
		int time_past_burn = t - burn_start - burn_duration;
		float charring_amount = (float)time_past_burn / (float)char_threshold;
		if (charring_amount >= 1) {
			glColor3ub(0,0,0);
		}
		else {
			color intermed_char = char_color*(1-charring_amount);
			// glColor3ub((1-charring_amount)*0xf8,(1-charring_amount)*0x52,(1-charring_amount)*0x11);
			glColor3ub(intermed_char.r, intermed_char.g, intermed_char.b);
		}
	}
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