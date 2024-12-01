
#include <iostream>
#include "Expression2.h"
#include <iomanip>

using namespace std;

void testDerivative() {
    Expression expr;
    string input;
    char variable;
    
    while (true) {
        cout << "\n====== Derivative Test Program ======\n";
        cout << "Enter expression (or 'q' to quit): ";
        getline(cin, input);
        
        if (input == "q" || input == "Q") {
            break;
        }
        
        try {
            expr.ReadExpr(input);
            cout << "Original expression: ";
            expr.WriteExpr();
            cout << endl;
            
            cout << "Enter variable to differentiate with respect to: ";
            cin >> variable;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲
            
            Expression derivative = expr.Diff(variable);
            cout << "\nDerivative with respect to " << variable << ": ";
            derivative.WriteExpr();
            cout << "\nSimplified: ";
            derivative.MergeConst();  // 如果有实现简化函数的话
            derivative.WriteExpr();
            cout << endl;
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    cout << "Test program ended.\n";
}

// 主函数
int main() {
    testDerivative();
    return 0;
}