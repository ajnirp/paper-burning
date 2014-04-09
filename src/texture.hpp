#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

using namespace std;

struct directions
{
	float up;
	float lt;
	float rt;
	float dn;
};

class texture
{
private:
	int size;
	directions** texmatrix;

public:
	inline texture() {}
	void set(int s, string texfile);
	~texture();

	inline directions at(int i, int j) { return texmatrix[i][j]; }
};

#endif