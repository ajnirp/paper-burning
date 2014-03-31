#ifndef PAPER_HPP
#define PAPER_HPP

#include "cell.hpp"

class paper
{
private:
	int x, y; // bottom left
	int s; // side length
	cell** cells;

public:
	paper(int xx, int yy, int ss=300);
	~paper();

	void draw();
	void update(bool burn);
};


#endif