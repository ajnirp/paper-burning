#include "paper.hpp"
#include "cell.hpp"
#include "misc.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/gl.h>
#include <GL/freeglut.h>

using namespace std;

paper::paper(int xx, int yy, int bspd, int ss/*=300*/)
{
	x = xx;
	y = yy;

	burn_speed = bspd;

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
	for (int i = 0 ; i < s ; i++)
		delete [] cells[i];

	delete [] cells;
}

void paper::draw(int t)
{
	for (int i = 0 ; i < s ; i++) {
		for (int j = 0; j < s; j++) {
			cells[i][j].draw(x, y, t);
		}
	}
}

void paper::accumulate_unburnt(int i, int j, vector<cell*> & accumulated)
{
	double threshold = 0.3; // 0.3 gives a nice simulation
	// double threshold = 1;
	if ((i+1 < s) and (cells[i+1][j].state() == UNBURNT)) {
		if (random2() <= threshold)
			accumulated.push_back(&cells[i+1][j]);
	}
	if ((j+1 < s) and (cells[i][j+1].state() == UNBURNT)) {
		if (random2() <= threshold)
			accumulated.push_back(&cells[i][j+1]);
	}
	if ((i-1 >= 0) and (cells[i-1][j].state() == UNBURNT)) {
		if (random2() <= threshold)
			accumulated.push_back(&cells[i-1][j]);
	}
	if ((j-1 >= 0) and (cells[i][j-1].state() == UNBURNT)) {
		if (random2() <= threshold)
			accumulated.push_back(&cells[i][j-1]);
	}
}

void paper::update(int t)
{
	/* accumulate unburnt neighbours of burning cells */
	vector<cell*> accumulated;
	for (int i = 0 ; i < s ; i++) {
		for (int j = 0 ; j < s ; j++) {
			if (cells[i][j].state() == BURNING) {
				accumulate_unburnt(i,j,accumulated);
				/* check if burning time is over and set to BURNT if need be */
				cells[i][j].check_burnt(t);
			}
		}
	}
	/* set the cells in 'accumulated' to burning */
	for (cell* c : accumulated) c->set_burning(t);
}

bool paper::contains(int xx, int yy)
{
	return (x <= xx and xx <= x+s and y <= yy and yy < y+s);
}

void paper::start_burning(vector<pair<int,int> > & burn_points)
{
	for (pair<int,int> p : burn_points) {
		int i = p.first;
		int j = p.second;
		cells[i][j].set_burning(0);
	}
}

void paper::start_burning(pair<int,int> burn_point, int t)
{
	int i = burn_point.first;
	int j = burn_point.second;
	cells[i][j].set_burning(t);
}

// void paper::print_burning()
// {
// 	int count1 = 0;
// 	int count2 = 0;
// 	int count3 = 0;
// 	for (int i = 0 ; i < s ; i++)
// 		for (int j = 0 ; j < s ; j++) {
// 			if (cells[i][j].state() == UNBURNT)
// 				count1++;
// 			if (cells[i][j].state() == BURNING)
// 				count2++;
// 			if (cells[i][j].state() == BURNT)
// 				count3++;
// 		}
// 	cout << count1 << " ";
// 	cout << count2 << " ";
// 	cout << count3 << endl;
// }