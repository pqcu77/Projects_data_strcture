#include "readImage.h"
#include "storage.h"
#include "CImg.h"
#include "SizesShift.h"
#include "color2gray.h"
#include <iostream>
#include <string>

using namespace cimg_library;
using namespace std;

typedef tuple<int, int, unsigned char, int> GrayTuple;
typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>, int> ColorTuple;

struct GrayPic {
    vector<GrayTuple> data;
    vector<GrayTuple> compressdata;
    int width;
    int height;
    string filename;
};

struct ColorPic {
    vector<ColorTuple> data;
    vector<ColorTuple> compressdata;
    int width;
    int height;
    string filename;
};

int menu() {
    int choice;
    cout << "==============================================================" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "-----------------Welcome to the Image Processor---------------" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "==============================================================" << endl;
    cout << "-----------------------------Menu-----------------------------" << endl;
    cout << "-------------1. Read and Write Image Data---------------------" << endl;
    cout << "-------------2. Compress Image Data---------------------------" << endl;
    cout << "-------------3. Convert Color Image to Grayscale--------------" << endl;
    cout << "-------------4. Resize Image----------------------------------" << endl;
    cout << "-------------0. Exit Program----------------------------------" << endl;
    cout << "==============================================================" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "---------Please enter a number to select a function!----------" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "==============================================================" << endl;

    cin >> choice;

    string path;
    string name;
    int wid, hei;
    vector<GrayPic> g;
    vector<ColorPic> p;

    switch (choice) {
    case 1:
        cout << "Please enter the image path:" << endl;
        cin >> path;
        cout << "Please enter the filename to save as:" << endl;
        cin >> name;
        readImage(path.c_str(), name);
        break;
    case 2:
        cout << "Please enter the image path:" << endl;
        cin >> path;
        cout << "Please enter the filename to save as:" << endl;
        cin >> name;
        {
            CImg<unsigned char> img(path.c_str());
            if (img.spectrum() == 1) {
                vector<GrayTuple> gt = readGray(path.c_str());
                GrayPic tmp;
                tmp.data = gt;
                tmp.compressdata = compressGrayData(gt,name);
                tmp.filename = name;
                tmp.width = img.width();
                tmp.height = img.height();
                g.push_back(tmp);
                decodeGrayData(tmp.compressdata, name, tmp.width, tmp.height);
            }
            else if (img.spectrum() == 3) {
                vector<ColorTuple> ct = readColor(path.c_str());
                ColorPic tmp;
                tmp.data = ct;
                tmp.compressdata = compressColorData(ct,name);
                tmp.filename = name;
                tmp.width = img.width();
                tmp.height = img.height();
                p.push_back(tmp);
                decodeColorData(tmp.compressdata, name, tmp.width, tmp.height);
            }
        }
        break;
    case 3:
        cout << "Please enter the image path:" << endl;
        cin >> path;
        cout << "Please enter the filename to save as:" << endl;
        cin >> name;
        color2gray(path.c_str(), name);
        break;
    case 4:
        cout << "Please enter the image path:" << endl;
        cin >> path;
        cout << "Please enter the image name:" << endl;
        cin >> name;
        cout << "Please enter the desired size for the image (width*height):" << endl;
        cin >> wid >> hei;
        enlarge(path, wid, hei, name);
        break;
    case 0:
        return 0;
    default:
        cout << "Invalid choice, please try again." << endl;
        break;
    }
    return 1;
}
// #include "readImage.h"
// #include "storage.h"
// #include "CImg.h"
// #include "SizesShift.h"
// #include "color2gray.h"
// #include <iostream>
// #include <string>

// using namespace cimg_library;
// using namespace std;

// typedef tuple<int, int, unsigned char, int> GrayTuple;
// typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>, int> ColorTuple;

// struct GrayPic {
//     vector<GrayTuple> data;
//     vector<GrayTuple> compressdata;
//     int width;
//     int height;
//     string filename;
// };

// struct ColorPic {
//     vector<ColorTuple> data;
//     vector<ColorTuple> compressdata;
//     int width;
//     int height;
//     string filename;
// };

// int menu() {
//     int choice;
//     cout << "======================================" << endl;
//     cout << "--------------------------------------" << endl;
//     cout << "-----------欢迎使用图片处理器-----------" << endl;
//     cout << "--------------------------------------" << endl;
//     cout << "======================================" << endl;
//     cout << "----------------菜单栏-----------------" << endl;
//     cout << "--------1.图像数据的读取与写入存储-------" << endl;
//     cout << "--------2.图像数据的压缩存储------------" << endl;
//     cout << "--------3.彩色图像转变为灰度图像---------" << endl;
//     cout << "--------4.图像尺寸的缩放----------------" << endl;
//     cout << "--------0.退出程序----------------------" << endl;
//     cout << "======================================" << endl;
//     cout << "--------------------------------------" << endl;
//     cout << "---------请输入编号来选择功能！----------" << endl;
//     cout << "--------------------------------------" << endl;
//     cout << "======================================" << endl;

//     cin >> choice;

//     string path;
//     string name;
//     int wid, hei;
//     vector<GrayPic> g;
//     vector<ColorPic> p;

//     switch (choice) {
//     case 1:
//         cout << "请输入图片的路径:" << endl;
//         cin >> path;
//         cout << "请输入想保存为的文件名:" << endl;
//         cin >> name;
//         readImage(path.c_str(), name);
//         break;
//     case 2:
//         cout << "请输入图片的路径" << endl;
//         cin >> path;
//         cout << "请输入想保存为的文件名：" << endl;
//         cin >> name;
//         {
//             CImg<unsigned char> img(path.c_str());
//             if (img.spectrum() == 1) {
//                 vector<GrayTuple> gt = readGray(path.c_str());
//                 GrayPic tmp;
//                 tmp.data = gt;
//                 tmp.compressdata = compressGrayData(gt);
//                 tmp.filename = name;
//                 tmp.width = img.width();
//                 tmp.height = img.height();
//                 g.push_back(tmp);
//                 decodeGrayData(tmp.compressdata, name, tmp.width, tmp.height);
//             }
//             else if (img.spectrum() == 3) {
//                 vector<ColorTuple> ct = readColor(path.c_str());
//                 ColorPic tmp;
//                 tmp.data = ct;
//                 tmp.compressdata = compressColorData(ct);
//                 tmp.filename = name;
//                 tmp.width = img.width();
//                 tmp.height = img.height();
//                 p.push_back(tmp);
//                 decodeColorData(tmp.compressdata, name, tmp.width, tmp.height);
//             }
//         }
//         break;
//     case 3:
//         cout << "请输入图片路径：" << endl;
//         cin >> path;
//         cout << "请输入您想保存的文件名" << endl;
//         cin >> name;
//         color2gray(path.c_str(), name);
//         break;
//     case 4:
//         cout << "请输入图片路径：" << endl;
//         cin >> path;
//         cin >> name;
//         cout << "请输入您想将此图片转换成的图片大小(width*height)" << endl;
//         cin >> wid >> hei;
//         enlarge(path, wid, hei, name);
//         break;
//     case 0:
//         return 0;
//     default:
//         cout << "无效的选择，请重新输入。" << endl;
//         break;
//     }
//     return 1;
// }

