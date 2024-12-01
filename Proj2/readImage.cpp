#include "readImage.h"
#include <vector>
#include <tuple>
#include <string>
#include "CImg.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cimg_library;

typedef tuple<int, int, unsigned char, int> GrayTuple;
typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>, int> ColorTuple;

// // 函数声明
// string determine_format(const string& filename);

// function1: 实现将图片读入并保存，以及展示图片
void readImage(const char* image_path, const string& name) {
    // read image from path
    CImg<unsigned char> img(image_path);

    // showing the pic in a window && set the window position
    CImgDisplay display(img, "input picture");
    // 设置窗口位置和大小，确保在屏幕范围内显示
    int window_x = 100;
    int window_y = 100;
    display.move(window_x, window_y);

    // store the original picture
    string format = determine_format(image_path);
    string address = "Picture_save/" + name + format; // 给每张图片一个唯一的名字带上后缀

    img.save(address.c_str()); // string to char[]

    // showing pic
    while (!display.is_closed()) {
        display.wait();
    }
}

// function2：实现读取图片并将图片存储为三元组数据格式
vector<GrayTuple> readGray(const char* filename) {
    CImg<unsigned char> img(filename);
    vector<tuple<int, int, unsigned char, int>> gray;
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            gray.push_back(make_tuple(x, y, img(x, y), 0)); // 存储坐标和像素值
        }
    }
    return gray;
}

vector<ColorTuple> readColor(const char* filename) {
    CImg<unsigned char> img(filename);
    vector<tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>, int>> color;
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            color.push_back(make_tuple(x, y, make_tuple(img(x, y, 0, 0), img(x, y, 0, 1), img(x, y, 0, 2)), 0));
        }
    }
    return color;
}

// 确定图片后缀
string determine_format(const string& filename) {
    size_t dot_pos = filename.find_last_of(".");
    if (dot_pos != string::npos && dot_pos != filename.length() - 1) {
        string format = filename.substr(dot_pos);
        if (format == ".png" || format == ".ppm" || format == ".jpg" || format == ".jpeg" || format == ".bmp") {
            return format;
        }
    }
    return ".png"; // 默认格式
}
// #include "readImage.h"
// typedef tuple<int, int, unsigned char,int> GrayTuple;
// typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>,int> ColorTuple;

// //fuction1:实现将图片读入并保存，以及展示图片
// void readImage(const char* image_path, const string& name) {
//     // read image from path
//     CImg<unsigned char> img(image_path);

//     // showing the pic in a window && set the window position
//     CImgDisplay display(img, "input picture");
//     // 设置窗口位置和大小，确保在屏幕范围内显示
//     int window_x = 100;
//     int window_y = 100;
//     display.move(window_x, window_y);

//     // store the original picture
//     string address = "Picture_save/" + name; // 给每张图片一个唯一的名字
    
//     img.save(address.c_str()); // string to char[]

//     // showing pic
//     while (!display.is_closed()) {
//         display.wait();
//     }
// }

// //function2：实现读取图片并将图片存储为三元组数据格式
// vector<GrayTuple> readGray(const char* filename) {
//     CImg<unsigned char> img(filename);
//     vector<tuple<int, int, unsigned char,int>> gray;
//     for (int y = 0; y < img.height(); y++) {
//         for (int x = 0; x < img.width(); x++) {
//             gray.push_back(make_tuple(x, y, img(x, y),0)); // 存储坐标和像素值
//         }
//     }
//     return gray;
// }

// vector<ColorTuple> readColor(const char* filename) {
//     CImg<unsigned char> img(filename);
//     vector<tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>,int>> color;
//     for (int y = 0; y < img.height(); y++) {
//         for (int x = 0; x < img.width(); x++) {
//             color.push_back(make_tuple(x, y, make_tuple(img(x, y, 0, 0), img(x, y, 0, 1), img(x, y, 0, 2)),0));
//         }
//     }
//     return color;
// }

