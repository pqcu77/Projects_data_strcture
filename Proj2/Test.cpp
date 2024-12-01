#include "readImage.h"
#include "storage.h"
#include "CImg.h"
#include <iostream>
#include <string>

using namespace cimg_library;
using namespace std;

struct GrayPic{
    vector<GrayTuple> data;
    vector<GrayTuple> compressdata;
    int width;
    int height;
    string filename;
};

struct ColorPic{
    vector<ColorTuple> data;
    vector<ColorTuple> compressdata;
    int width;
    int height;
    string filename;
};

int main() {
    // funtion1:
    // readImage("photo_test/color-block.png", "color-block");
    // readImage("photo_test/lena-512-gray.png", "lena");
    readImage("photo_test/color-block.ppm","ppm");

    // // function2
    // string filename;
    // cin >> filename;
    // CImg<unsigned char> img(filename.c_str());

    // if (img.spectrum() == 1) {
    //     cout << "The image is gray." << endl;
    //     GrayPic pg;
    //     pg.width = img.width();
    //     pg.height = img.height();
    //     pg.filename = filename;
    //     cout << "readGray:" << endl;
    //     pg.data = readGray(filename.c_str());
    //     cout << "readGray done" << endl;
    //     cout << "compressGray" << endl;
    //     pg.compressdata = compressGrayData(pg.data);
    //     cout << "compressGray done" << endl;
    //     cout<<"decodeGray"<<endl;
    //     decodeGrayData(pg.compressdata,"pg",pg.width,pg.height);
    //     cout<<"decodeGray done"<<endl;
    // } else if (img.spectrum() == 3) {
    //     cout << "The image is colorful." << endl;
    //     ColorPic pc;
    //     pc.width = img.width();
    //     pc.height = img.height();
    //     pc.filename = filename;
    //     pc.data = readColor(filename.c_str());
    //     pc.compressdata = compressColorData(pc.data);
    //     decodeColorData(pc.compressdata,"pc",pc.width,pc.height);
    // }

    
    return 0;
}