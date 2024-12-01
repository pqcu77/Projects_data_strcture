#include<iostream>
#include "CImg.h"
#include"readImage.h"
#include"storage.h"
using namespace std;
using namespace cimg_library;

void color2gray(const char* filename,string name){
    CImg<unsigned char> colorImg(filename);
    CImg<unsigned char> grayImg(colorImg.width(),colorImg.height(),1,1,0);
    if(colorImg.spectrum()==3){
        for(int y=0;y<colorImg.height();y++){
            for(int x=0;x<colorImg.width();x++){
                grayImg(x, y) = colorImg(x, y, 0, 0) * 0.299 + colorImg(x, y, 0, 1) * 0.587 + colorImg(x, y, 0, 2) * 0.114;
            }
        }
    }

    string path = "Picture_save/" + name + ".ppm";
    grayImg.save(path.c_str());

    //չʾͼƬ���ұ�֤ͼ���������Ļ�ɿ����ĵط�
    CImgDisplay display(grayImg, "input picture");
    // ���ô���λ�úʹ�С��ȷ������Ļ��Χ����ʾ
    int window_x = 100;
    int window_y = 100;
    display.move(window_x, window_y);

    while (!display.is_closed()) {
        display.wait();
    }
}

// int main(){
//     color2gray("photo_test/color-block.ppm", "color-block_gray");
//     color2gray("photo_test/lena-128-gray.ppm", "lena-128_gray");
//     return 0;
// }