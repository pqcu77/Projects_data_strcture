#include "storage.h"
#include <vector>
#include <iostream>
#include <tuple>
#include "CImg.h"
#include <fstream>
#include <filesystem>
#include "readImage.h"

using namespace std;
using namespace cimg_library;

typedef tuple<int, int, unsigned char, int> GrayTuple;
typedef tuple<int, int, tuple<unsigned char, unsigned char, unsigned char>, int> ColorTuple;

// 确定图片后缀
string determine_formats(const string& filename) {
    size_t dot_pos = filename.find_last_of(".");
    if (dot_pos != string::npos && dot_pos != filename.length() - 1) {
        string format = filename.substr(dot_pos);
        if (format == ".png" || format == ".ppm" || format == ".jpg" || format == ".jpeg" || format == ".bmp") {
            return format;
        }
    }
    return ".png"; // 默认格式
}

// function2 -对三元组数据进行压缩，并保存
// 灰度图像压缩
vector<GrayTuple> compressGrayData(vector<GrayTuple>& grayData, string filename) {
    vector<GrayTuple> compressedData;
    if (grayData.empty()) return compressedData;
    auto prev = grayData[0];
    int cnt = 1; // count the num of the same pixel;

    for (size_t i = 1; i < grayData.size(); i++) {
        if (grayData[i] == prev) {
            cnt++;
        } else {
            compressedData.push_back(make_tuple(get<0>(prev), get<1>(prev), get<2>(prev), cnt));
            prev = grayData[i];
            cnt = 1;
        }
    }

    compressedData.push_back(make_tuple(get<0>(prev), get<1>(prev), get<2>(prev), cnt));
    SaveCompressedGrayData(compressedData, "CompressData_save/compressed_gray_data" + filename + ".dat");
    return compressedData;
}

// 彩色图像压缩
vector<ColorTuple> compressColorData(vector<ColorTuple>& colorData, string filename) {
    vector<ColorTuple> compressedData;
    if (colorData.empty()) return compressedData;

    auto prev = colorData[0];
    int cnt = 1;

    for (size_t i = 1; i < colorData.size(); i++) {
        if (get<0>(colorData[i]) == get<0>(prev) && get<1>(colorData[i]) == get<1>(prev) &&
            get<2>(get<2>(colorData[i])) == get<2>(get<2>(prev)) &&
            get<1>(get<2>(colorData[i])) == get<1>(get<2>(prev)) &&
            get<0>(get<2>(colorData[i])) == get<0>(get<2>(prev))) {
            cnt++;
        } else {
            compressedData.push_back(make_tuple(get<0>(prev), get<1>(prev), make_tuple(get<0>(get<2>(prev)), get<1>(get<2>(prev)), get<2>(get<2>(prev))), cnt));
            prev = colorData[i];
            cnt = 1;
        }
    }

    compressedData.push_back(make_tuple(get<0>(prev), get<1>(prev), make_tuple(get<0>(get<2>(prev)), get<1>(get<2>(prev)), get<2>(get<2>(prev))), cnt));
    SaveCompressedColorData(compressedData, "CompressData_save/compressed_color_data" + filename + ".dat");
    return compressedData;
}

// function2-对压缩信息进行解码，得到原始数据进行保存
void decodeGrayData(vector<GrayTuple>& data, string filename, int width, int height) {
    if (data.empty()) return;
    CImg<unsigned char> img(width, height, 1, 1, 0);
    int x = 0, y = 0;
    for (auto& p : data) {
        int cnt = get<3>(p);
        unsigned char pix = get<2>(p);
        while (cnt-- > 0) {
            img(x, y) = pix;
            x++;
            if (x >= width) {
                x = 0;
                y++;
            }
        }
    }
    string format = determine_formats(filename);
    string path = "Picture_save/" + filename.substr(0, filename.find_last_of(".")) + "_decode" + format;
    img.save(path.c_str());
}

void decodeColorData(vector<ColorTuple>& data, string filename, int width, int height) {
    if (data.empty()) return;
    CImg<unsigned char> img(width, height, 1, 3, 0);
    for (auto& p : data) {
        int x = get<0>(p);
        int y = get<1>(p);
        unsigned char r = get<0>(get<2>(p));
        unsigned char g = get<1>(get<2>(p));
        unsigned char b = get<2>(get<2>(p));
        int cnt = get<3>(p);

        for (int i = 0; i < cnt; i++) {
            img(x, y, 0, 0) = r;
            img(x, y, 0, 1) = g;
            img(x, y, 0, 2) = b;
            x++;
            if (x >= width) {
                x = 0;
                y++;
            }
        }
    }
    string format = determine_formats(filename);
    string path = "Picture_save/" + filename.substr(0, filename.find_last_of(".")) + "_decode" + format;
    img.save(path.c_str());
}

// 保存压缩的灰度数据
void SaveCompressedGrayData(const vector<GrayTuple>& data, const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    for (const auto& p : data) {
        ofs.write(reinterpret_cast<const char*>(&p), sizeof(GrayTuple));
    }
    ofs.close();
}

// 加载压缩的灰度数据
vector<GrayTuple> LoadCompressedGrayData(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "Error opening file for reading: " << filename << endl;
        return {};
    }
    vector<GrayTuple> data;
    GrayTuple p;
    while (ifs.read(reinterpret_cast<char*>(&p), sizeof(GrayTuple))) {
        data.push_back(p);
    }
    ifs.close();
    return data;
}

// 保存压缩的彩色数据
void SaveCompressedColorData(const vector<ColorTuple>& data, const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    for (const auto& p : data) {
        ofs.write(reinterpret_cast<const char*>(&p), sizeof(ColorTuple));
    }
    ofs.close();
}

// 加载压缩的彩色数据
vector<ColorTuple> LoadCompressedColorData(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "Error opening file for reading: " << filename << endl;
        return {};
    }
    vector<ColorTuple> data;
    ColorTuple p;
    while (ifs.read(reinterpret_cast<char*>(&p), sizeof(ColorTuple))) {
        data.push_back(p);
    }
    ifs.close();
    return data;
}