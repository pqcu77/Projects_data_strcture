#ifndef STORAGE_H
#define STORAGE_H

#include "CImg.h"
#include <vector>
#include <tuple>
#include "readImage.h"
#include<iostream>

using namespace cimg_library;
using namespace std;
typedef tuple<int, int, unsigned char,int> GrayTuple;
typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>,int> ColorTuple;


vector<GrayTuple> compressGrayData(vector<GrayTuple>& grayData,string filename);
vector<ColorTuple> compressColorData(vector<ColorTuple>& colorData,string filename);
void decodeGrayData(vector<GrayTuple>& data,string  filename,int width,int height);
void decodeColorData(vector<ColorTuple> &data, string filename, int width, int height);
string determine_format(const string &filepath);
void SaveCompressedGrayData(const vector<GrayTuple>& data, const string& filename);
vector<GrayTuple> LoadCompressedGrayData(const string& filename);
void SaveCompressedColorData(const vector<ColorTuple>& data, const string& filename);
vector<ColorTuple> LoadCompressedColorData(const string& filename);
string determine_formats(const string &filename);

#endif // STORAGE_H