#ifndef PAPER_HPP
#define PAPER_HPP

#include "cell.hpp"
#include "texture.hpp"
#include <vector>
#include <string>

class paper
{
private:
	int x, y; // bottom left
	int s; // side length
	cell** cells;
	texture texmap;

	void accumulate_unburnt(int i, int j, vector<cell*> & accumulated, bool use_texmap=false);

public:
	paper(int xx, int yy, string texfile, int ss=300);
	~paper();

	inline int get_x() { return x; }
	inline int get_y() { return y; }
	void draw(int t);
	void update(int t);
	bool contains(int xx, int yy);
	inline cell* cell_at(int i, int j) { return &cells[i][j]; }
	void start_burning(vector<pair<int,int> > & burn_points);
	void start_burning(pair<int,int> burn_point, int t);

	void print_burning();
};


#endif