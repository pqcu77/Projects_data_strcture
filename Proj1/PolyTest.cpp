#include<iostream>
#include"Polynomial calculator.h"

using namespace std;

int main() {
    // 测试 ReadPoly 函数
    cout << "Testing ReadPoly:" << endl;
    PolyNode *poly1 = ReadPoly();
    printPoly(poly1);
    cout << endl;

    // 测试 AddPoly 函数
    cout << "Testing AddPoly:" << endl;
    PolyNode *poly2 = ReadPoly();
    PolyNode *sum = AddPoly(poly1, poly2);
    printPoly(sum);
    cout << endl;

    // 测试 SubPoly 函数
    cout << "Testing SubPoly:" << endl;
    PolyNode *diff = SubPoly(poly1, poly2);
    printPoly(diff);
    cout << endl;

    // 测试 MulPoly 函数
    cout << "Testing MulPoly:" << endl;
    PolyNode *product = MulPoly(poly1, poly2);
    printPoly(product);
    cout << endl;

    // 测试 cal_derived_function 函数
    cout << "Testing cal_derived_function:" << endl;
    PolyNode *derived = cal_derived_function(poly1);
    printPoly(derived);
    cout << endl;

    // 测试 getVal 函数
    cout << "Testing getVal:" << endl;
    double value = getVal(poly1, 2); // 计算 poly1 在 x=2 时的值
    cout << "Value of poly1 at x=2: " << value << endl;

    // 清理内存
    deletePoly(poly1); // 需要实现一个删除多项式的函数
    deletePoly(poly2);
    deletePoly(sum);
    deletePoly(diff);
    deletePoly(product);
    deletePoly(derived);

    return 0;
}