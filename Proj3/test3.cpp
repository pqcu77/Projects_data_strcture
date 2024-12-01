#include <iostream>
#include "Expression2.h"
using namespace std;

void testCompoundExpr() {
    try {
        // 测试用例1: 简单表达式
        Expression expr1, expr2;
        expr1.ReadExpr("x");  // 第一个表达式: x
        expr2.ReadExpr("2");  // 第二个表达式: 2
        
        cout << "Expression 1: ";
        expr1.WriteExpr();
        cout << "Expression 2: ";
        expr2.WriteExpr();

        // 测试加法复合
        Expression add = Expression::CompoundExpr('+', expr1, expr2);
        cout << "After compound (+): ";
        add.WriteExpr();
        cout << "Tree structure:" << endl;
        add.DisplayTree();
        
        // 给变量赋值并计算结果
        add.Assign('x', 3);
        cout << "Value after assigning x=3: " << add.Value() << endl;

        // 测试用例2: 复杂表达式
        Expression expr3, expr4;
        expr3.ReadExpr("+x2");  // 第一个表达式: x+2
        expr4.ReadExpr("*23");  // 第二个表达式: 2*3
        
        cout << "\nExpression 3: ";
        expr3.WriteExpr();
        cout << "Expression 4: ";
        expr4.WriteExpr();

        // 测试乘法复合
        Expression mult = Expression::CompoundExpr('*', expr3, expr4);
        cout << "After compound (*): ";
        mult.WriteExpr();
        cout << "Tree structure:" << endl;
        mult.DisplayTree();
        
        mult.Assign('x', 1);
        cout << "Value after assigning x=1: " << mult.Value() << endl;

    } catch (const Expression::ExpressionException& e) {
        cout << "Error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Standard error: " << e.what() << endl;
    }
}

int main() {
    testCompoundExpr();
    return 0;
}