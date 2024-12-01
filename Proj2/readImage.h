#ifndef READIMAGE_H
#define READIMAGE_H

#include "CImg.h"
#include <vector>
#include <tuple>
#include <string>
#include<iostream>

using namespace cimg_library;
using namespace std;

typedef tuple<int, int, unsigned char,int> GrayTuple;
typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>,int> ColorTuple;

vector<GrayTuple> readGray(const char* filename);
vector<ColorTuple> readColor(const char* filename);
void readImage(const char* image_path, const string& name);
string determine_format(const string& filename);
#endif // READIMAGE_H