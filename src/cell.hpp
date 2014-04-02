#ifndef CELL_HPP
#define CELL_HPP

#include <vector>

using namespace std;

enum burn_state
{
	UNBURNT,
	BURNING,
	BURNT
};

class cell
{
private:
	int x, y;
	burn_state b_state;
	int burn_start;
	int burn_duration;
	int char_threshold;

public:
	cell();
	
	inline void set_xy(int xx, int yy) { x = xx; y = yy; }
	inline burn_state state() { return b_state; }
	void draw(int x_off, int y_off, int t);
	void check_burnt(int t);
	void set_burning(int t);
};

#endif