
#include<iostream>
#include"Cimg.h"
#include<algorithm>

using namespace std;
using namespace cimg_library;

// ȷ��ͼƬ��׺
string get_file_extension(const string& filename) {
    size_t dot_pos = filename.find_last_of(".");
    if (dot_pos != string::npos) {
        return filename.substr(dot_pos);
    }
    return ".unknown";
}

// ͼƬ����-������ʹ��˫���Բ�ֵ��
void enlarge(string filename, int width, int height, string name) {
    CImg<unsigned char> img(filename.c_str());
    CImg<unsigned char> largeImg(width, height, 1, img.spectrum(), 0);
    float x_ratio = img.width() / static_cast<float>(width);
    float y_ratio = img.height() / static_cast<float>(height);

    cimg_forXY(largeImg, x, y) { // ��ͬ��˫��Ƕ��ѭ������x��y
        // ����ԭͼ�ж�Ӧ��λ��
        float gx = x * x_ratio;
        float gy = y * y_ratio;
        // Ѱ����Χ�ٽ����ĸ������
        int gx1 = static_cast<int>(gx);
        int gy1 = static_cast<int>(gy);
        int gx2 = (gx1 + 1 < img.width()) ? gx1 + 1 : gx1;
        int gy2 = (gy1 + 1 < img.height()) ? gy1 + 1 : gy1;
        // �����ֵ
        float dx = gx - gx1;
        float dy = gy - gy1;

        for (int c = 0; c < img.spectrum(); ++c) {
            float val = (1 - dx) * (1 - dy) * img(gx1, gy1, 0, c) +    // ���Ͻ����صĹ���
                        dx * (1 - dy) * img(gx2, gy1, 0, c) +          // ���Ͻ����صĹ���
                        (1 - dx) * dy * img(gx1, gy2, 0, c) +          // ���½����صĹ���
                        dx * dy * img(gx2, gy2, 0, c);                 // ���½����صĹ���
            largeImg(x, y, 0, c) = static_cast<unsigned char>(val);
        }
    }

    string extension = get_file_extension(filename);
    string save_path = "Picture_save/sizes_" + name + extension;

    largeImg.save(save_path.c_str());

    CImgDisplay display(largeImg, "SizesShift");
    // ���ô���λ�úʹ�С��ȷ������Ļ��Χ����ʾ
    int window_x = 100;
    int window_y = 100;
    display.move(window_x, window_y);
    while (!display.is_closed()) {
        display.wait();
    }
}
