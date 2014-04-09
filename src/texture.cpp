#include "texture.hpp"

#include <fstream>
#include <iostream>

using namespace std;

void texture::set(int s, string texfile)
{
	ifstream fd;
	fd.open(texfile);

	size = s;
	texmatrix = new directions*[s];

	if (fd.good()) {
		for (int i = 0 ; i < size ; i++) {
			texmatrix[i] = new directions[s];
			for (int j = 0 ; j < size ; j++) {
				fd >> texmatrix[i][j].up
				   >> texmatrix[i][j].lt
				   >> texmatrix[i][j].rt
				   >> texmatrix[i][j].dn;
			}
		}
	}

	fd.close();
}

texture::~texture()
{
	for (int i = 0 ; i < size ; i++)
		delete [] texmatrix[i];

	delete [] texmatrix;
}