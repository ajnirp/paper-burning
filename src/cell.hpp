#ifndef CELL_HPP
#define CELL_HPP

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
public:
	inline cell() { b_state = UNBURNT; }
	inline void set_xy(int x, int y) { this->x = x; this->y = y; }
	inline burn_state state() { return b_state; }
	void draw(int x_off, int y_off);
};

#endif