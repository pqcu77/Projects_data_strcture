# ��Ŀ��־

## һ����Ŀ����

### 1. ͼ�����ݵĶ�ȡ��д��洢����չʾͼƬ

### 1.1 ��װ�����ÿ���������done����

* **��װC++������** ��ȷ��ϵͳ�ϰ�װ��C++����������GCC��Clang����
* **��װCImg**

- **�ĳ�ʹ��CImg�ˣ�Ū�˺ܾã�������mingw�İ汾̫���ˣ����º�����������С�**

### ��Ŀʵʩ����

### ʵ��˼·

1. **ͼ�����ݵĶ�ȡ��д��洢** ��(done!)

* ʹ��CImg���ȡ��д��ͼ���ļ���
* ʹ��CImg����ʾ����չʾͼ��

1. **ͼ�����ݵ�ѹ���洢** ��(done!)

* ��ȡͼƬ����ͼƬ��Ϣ����Ԫ��ṹ�洢��
* ����Ԫ�����ݽ���ѹ���洢��
* ��ȡѹ��������ݽ��н��룬�õ�ԭʼͼ�����ݣ������б��档

1. **��ɫͼ��ת��Ϊ�Ҷ�ͼ��** ��(done!)

* ʹ��CImg���ȡ��ɫͼ��
* ����ɫͼ��ת��Ϊ�Ҷ�ͼ��
* ���沢չʾ�Ҷ�ͼ��

1. **ͼ��ߴ������** ��

* ʹ��CImg���ȡͼ��
* ʵ��ͼ������Ź��ܡ�
* ���沢չʾ���ź��ͼ��

### ��ϸ����

#### 1. ͼ�����ݵĶ�ȡ��д��洢(done!)

* ʹ��CImg��� `CImg` ������ȡ��д��ͼƬ�ļ���

ʾ�����룺

C++

```cpp
#include "CImg.h"
using namespace cimg_library;

int main() {
    // ��ȡͼ��
    CImg<unsigned char> image("input.png");
  
    // ��ʾͼ��
    CImgDisplay display(image, "Image");

    // ����ͼ��
    image.save("output.png");

    // ���ִ��ڴ򿪣�ֱ���û��ر���
    while (!display.is_closed()) {
        display.wait();
    }
    return 0;
}
```

#### 2. ͼ�����ݵ�ѹ���洢(done!)

* ��ͼ������ת��Ϊ��Ԫ��ṹ������ѹ���洢��
* ѹ���㷨����ѡ��򵥵�RLE��Run-Length Encoding���ȡ�

1. **��ȡͼ������** ��

* ʹ��CImg���ȡͼ��
* ��ͼ������ת��Ϊ��Ԫ��ṹ `(x, y, color)`��

1. **ѹ����Ԫ������** ��

* ѡ��ѹ���㷨����Run-Length Encoding��Huffman����ȣ���
* ����Ԫ�����ݽ���ѹ����

1. **�洢ѹ������** ��

* ��ѹ��������ݴ洢���ļ��С�

1. **��ȡ�ͽ�ѹ������** ��

* ���ļ��ж�ȡѹ�����ݡ�
* ��ѹ�����ݽ��н��룬�õ�ԭʼͼ�����ݡ�

1. **���������ͼ��** ��

* ʹ��CImg�⽫���������ݱ���Ϊͼ��
* 

ʾ�����루α���룩��

C++

```cpp
// ��ͼ������ת��Ϊ��Ԫ��ṹ
// ѹ���洢
// ���벢�ָ�ԭʼͼ������
```

#### 3. ��ɫͼ��ת��Ϊ�Ҷ�ͼ��(done!)

* ʹ��CImg��� `RGBtoYCbCr` ����ת����ɫͼ��Ϊ�Ҷ�ͼ��

ʾ�����룺

C++

```cpp
#include "CImg.h"
using namespace cimg_library;

int main() {
    // ��ȡ��ɫͼ��
    CImg<unsigned char> color_image("input.ppm");

    // ת��Ϊ�Ҷ�ͼ��
    CImg<unsigned char> gray_image = color_image.RGBtoYCbCr().channel(0);

    // ��ʾ�Ҷ�ͼ��
    CImgDisplay display(gray_image, "Gray Image");

    // ����Ҷ�ͼ��
    gray_image.save("gray_output.ppm");

    // ���ִ��ڴ򿪣�ֱ���û��ر���
    while (!display.is_closed()) {
        display.wait();
    }
    return 0;
}
```

#### 4. ͼ��ߴ������

* ʹ��CImg��� `resize` ����ʵ��ͼ������š�
* ˼������˫���Բ�ֵ��Ӧ��ϵ��
  * �ֱ���������������˹�3�ε����Բ�ֵ����ͼ��ʾ������x������2�ε����Բ�ֵ�����R1(x, y1)��R2(x, y2)������ʱ�㣬����y�������1�ε����Բ�ֵ�ó�P(x, y)��ʵ���ϵ���2����ķ�����y��xҲ��һ���Ľ����
  * ![1730535568806](image/working_on/1730535568806.png)

ʾ�����룺

C++

```cpp
#include "CImg.h"
using namespace cimg_library;

int main() {
    // ��ȡͼ��
    CImg<unsigned char> image("input.png");

    // ����ͼ��
    CImg<unsigned char> resized_image = image.resize(image.width() / 2, image.height() / 2);

    // ��ʾ���ź��ͼ��
    CImgDisplay display(resized_image, "Resized Image");

    // �������ź��ͼ��
    resized_image.save("resized_output.png");

    // ���ִ��ڴ򿪣�ֱ���û��ر���
    while (!display.is_closed()) {
        display.wait();
    }
    return 0;
}
```

### �ܽ�

* **��ȡ��д��** ��ʹ��CImg��� `load` �� `save` ������
* **ѹ���洢** �����һ��ѹ���㷨����RLE������ͼ������ת��Ϊ��Ԫ��ṹ��ѹ���洢��
* **��ɫת�Ҷ�** ��ʹ��CImg��� `RGBtoYCbCr` ��������ֻ����Yͨ����
* **ͼ������** ��ʹ��CImg��� `resize` ������

1. **��������** ��

* ��װ������C++��������OpenCV�⡣

1. **�ֽ׶�ʵ��** ��

* �����������ֽܷ׶α�д�����ʵ�֣�����ÿ���׶ν��в��Ժ���֤��

1. **���������** ��

* ʹ���ṩ��PPM��ʽ�������ݽ�����֤��ȷ������������ȷʵ�֡�

1. **��д�ĵ�** ��

* ��¼��Ŀ�����˼·��ʹ�õ��㷨��ʵ��ϸ�ڣ�׫д��Ŀ�ĵ���

## ��������ʵʩʱ��������������

1. ��װopenCV��ʱ������˺ܴ�����⣬Ȼ����CImg������Ҳ���У�������������mingw�汾����������ʹ��CImg�ˣ�opencvδ���ԡ�
2. CImg��ȡͼƬ�����Ҳ��֪����ʲôԭ��
   *CImgû�ж�ȡͼƬ�Ľ��������ƺ�������Ҫ��װImageMagick��Ȼ���ڱ����ʱ������ļ�·�������ϣ��Ҿ��ú�������д��cmakefile����makefile�������б����������
3. �������`g++ -o test test.cpp -I D:\Desktop\data_strcture\Proj2\CImg -I E:\software\ImageMagick-7.1.1-Q16\include -L E:\software\ImageMagick-7.1.1-Q16\lib -lCORE_RL_Magick++_ -lCORE_RL_MagickCore_ -lCORE_RL_MagickWand_ -lgdi32`

`g++ -o test2 test2.cpp -I D:\Desktop\data_strcture\Proj2\CImg -I E:\software\ImageMagick-7.1.1-Q16\include -L E:\software\ImageMagick-7.1.1-Q16\lib -lCORE_RL_Magick++_ -lCORE_RL_MagickCore_ -lCORE_RL_MagickWand_ -lgdi32`

4. ������ʹ�õ���CImg������[The CImg Library - C++ Template Image Processing Toolkit - Reference Documentation](https://cimg.eu/reference/structcimg__library_1_1CImg.html#accb8526e4303186fb6246ac1301fdf66)

![1730362037177](image/working_on/1730362037177.png)

��ȡ��Ϣ����λ����Ϣ����ɫ��Ϣ�����Ի�ȡ�ҶȻ�RGB����channel��

![1730362095703](image/working_on/1730362095703.png)

![1730362423082](image/working_on/1730362423082.png)
