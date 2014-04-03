#ifndef COLOR_HPP
#define COLOR_HPP

struct color
{
	int r;
	int g;
	int b;

	inline color() { r = g = b = 0; }
	inline color(int rr, int gg, int bb) { r = rr; g = gg; b = bb; }

	inline color operator*(float scalar) { return color((int)(scalar*r), (int)(scalar*g), (int)(scalar*b)); }
	inline color operator+(color c) { return color(r+c.r,g+c.g,b+c.b); }
};

#endif