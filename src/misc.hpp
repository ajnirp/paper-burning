#ifndef MISC_HPP
#define MISC_HPP

#include <stdlib.h>
#include <time.h>

#include <string>
#include <fstream>

using namespace std;

inline float random2() { return (float) rand() / RAND_MAX; }

void write_texture(string filename, int s);

#endif