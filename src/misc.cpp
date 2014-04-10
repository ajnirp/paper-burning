#include "misc.hpp"

#include <iostream>

using namespace std;

void write_texture(string filename, int s)
{
	ofstream fd;
	fd.precision(2);
	fd.open(filename.c_str());
	for (int i = 0 ; i < s ; i++) {
		for (int j = 0 ; j < s ; j++) {
			for (int dir = 0 ; dir < 4 ; dir++) {
				// round spread velocity to 2 decimal places
				float spread_velocity = (float)((int)(random2()*100)) / 100.f;
				if (spread_velocity > 0.8) spread_velocity = 0.8;

				// boost probability, then clamp
				// spread_velocity -= 0.1;
				// if (spread_velocity <= 0) spread_velocity = 0.02;

				fd << spread_velocity << " ";
			}
		}
		fd << "\n";
	}
}