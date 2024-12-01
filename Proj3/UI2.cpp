#include <windows.h>
#include <string>
#include<iostream>
#include <map>
#include <sstream>
#include "Expression2.h"
using namespace std;

// 全局变量
HWND hwndVar, hwndVal, hwndDiffVar;  // 输入框
HWND hwndResult, hwndTree;  // 显示结果
HWND hwndCalc, hwndAssign, hwndDiff,hwndClear;  // 按钮
Expression currentExpr;  // 当前表达式
HWND hwndExpr1, hwndExpr2,hwndExpr;  // 两个表达式输入框
HWND hwndOpCombo;  // 运算符选择下拉框
HWND hwndCompound,hwndMergeConst;  // 复合按钮
//输出捕获
class OutputCapture {
private:
    stringstream buffer;
    streambuf* oldCout;
    bool captured;

public:
    OutputCapture() : captured(false) {
        oldCout = cout.rdbuf(buffer.rdbuf());
        captured = true;
    }

    ~OutputCapture() {
        if (captured) {
            cout.rdbuf(oldCout);
        }
    }

    string getOutput() {
        string output = buffer.str();
        buffer.str("");  // 清空缓冲区
        buffer.clear();  // 清除状态位
        return output;
    }
};
//文本处理
string formatOutput(const std::string& text) {
    string formatted;
    for (char c : text) {
        if (c == '\n') {
            formatted += "\r\n";  // Windows换行需要\r\n
        } else {
            formatted += c;
        }
    }
    return formatted;
}
string ProcessTreeOutput(const string& input) {
    stringstream ss(input);
    string line;
    string result;
    while (getline(ss, line)) {
        // 保持每行的前导空格
        size_t firstNonSpace = line.find_first_not_of(" ");
        if (firstNonSpace != string::npos) {
            // 使用制表符替换空格组（可选）
            // string spaces(firstNonSpace, ' ');
            result += line + "\r\n";
        } else {
            result += line + "\r\n";
        }
    }
    return result;
}
// 窗口回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // 创建输入控件
            // 第一个表达式输入区
            CreateWindow("STATIC", "Expression 1:", 
                WS_CHILD | WS_VISIBLE,
                10, 140, 100, 20, 
                hwnd, NULL, NULL, NULL);
            hwndExpr = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                100, 10, 200, 20, 
                hwnd, NULL, NULL, NULL);

            hwndExpr1 = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                100, 140, 200, 20, 
                hwnd, NULL, NULL, NULL);

            // 第二个表达式输入区
            CreateWindow("STATIC", "Expression 2:", 
                WS_CHILD | WS_VISIBLE,
                10, 170, 100, 20, 
                hwnd, NULL, NULL, NULL);
            
            hwndExpr2 = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                100, 170, 200, 20, 
                hwnd, NULL, NULL, NULL);

            // 运算符选择下拉框
            hwndOpCombo = CreateWindow("COMBOBOX", "", 
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
                310, 140, 40, 100, 
                hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "Expression:", 
                WS_CHILD | WS_VISIBLE,
                10, 10, 80, 20, 
                hwnd, NULL, NULL, NULL);
            
            CreateWindow("STATIC", "Variable:", 
                WS_CHILD | WS_VISIBLE,
                10, 40, 70, 20, 
                hwnd, NULL, NULL, NULL);
            
            hwndVar = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                100, 40, 30, 20, 
                hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "Value:", 
                WS_CHILD | WS_VISIBLE,
                140, 40, 40, 20, 
                hwnd, NULL, NULL, NULL);
            
            hwndVal = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                190, 40, 50, 20, 
                hwnd, NULL, NULL, NULL);

            // 添加运算符选项
            SendMessage(hwndOpCombo, CB_ADDSTRING, 0, (LPARAM)"+");
            SendMessage(hwndOpCombo, CB_ADDSTRING, 0, (LPARAM)"-");
            SendMessage(hwndOpCombo, CB_ADDSTRING, 0, (LPARAM)"*");
            SendMessage(hwndOpCombo, CB_ADDSTRING, 0, (LPARAM)"/");
            SendMessage(hwndOpCombo, CB_ADDSTRING, 0, (LPARAM)"^");
            SendMessage(hwndOpCombo, CB_SETCURSEL, 0, 0);
            // 复合按钮
            hwndCompound = CreateWindow("BUTTON", "Compound", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                310, 170, 80, 30, 
                hwnd, (HMENU)5, NULL, NULL);

            // 求导变量输入
            CreateWindow("STATIC", "Diff var:", 
                WS_CHILD | WS_VISIBLE,
                10, 70, 70, 20, 
                hwnd, NULL, NULL, NULL);
            
            hwndDiffVar = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                100, 70, 30, 20, 
                hwnd, NULL, NULL, NULL);

            // 按钮
            hwndCalc = CreateWindow("BUTTON", "Calculate", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10, 100, 80, 30, 
                hwnd, (HMENU)1, NULL, NULL);

            hwndAssign = CreateWindow("BUTTON", "Assign", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                100, 100, 80, 30, 
                hwnd, (HMENU)2, NULL, NULL);

            hwndDiff = CreateWindow("BUTTON", "Derivative", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                190, 100, 80, 30, 
                hwnd, (HMENU)3, NULL, NULL);
            hwndMergeConst = CreateWindow(
                "BUTTON",                          // Button class
                "Merge Constants",                 // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                380, 100,                         // x, y position (adjust as needed)
                120, 30,                          // width, height
                hwnd,                             // Parent window
                (HMENU)6,                         // Button identifier (use a unique ID)
                GetModuleHandle(NULL),
                NULL);
            // 结果显示区域
            hwndResult = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
                10, 210, 380, 100,  // 调整位置
                hwnd, NULL, NULL, NULL);

            // 树形显示区域
            hwndTree = CreateWindow("EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL| ES_LEFT,
                10, 320, 380, 200, 
                hwnd, NULL, NULL, NULL);
            
            //清空窗口
            hwndClear = CreateWindow("BUTTON", "Clear",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                280, 100, 80, 30,
                hwnd, (HMENU)4, NULL, NULL);
            // 在 WM_CREATE 中修改字体设置
            HFONT hFont = CreateFont(
                16,                    // 字体高度
                0,                     // 字体宽度（0表示使用默认）
                0,                     // 文本倾斜角度
                0,                     // 字符基线的倾斜角度
                FW_NORMAL,            // 字体粗细
                FALSE,                // 斜体
                FALSE,                // 下划线
                FALSE,                // 删除线
                ANSI_CHARSET,         // 字符集
                OUT_DEFAULT_PRECIS,   // 输出精度
                CLIP_DEFAULT_PRECIS,  // 裁剪精度
                CLEARTYPE_QUALITY,    // 输出质量
                FIXED_PITCH | FF_MODERN, // 字体间距和字体族
                "Consolas"            // 字体名称
            );

            if (hFont) {
                SendMessage(hwndTree, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(hwndResult, WM_SETFONT, (WPARAM)hFont, TRUE);
            }
            

            break;
        }

        case WM_COMMAND: {
            if (HIWORD(wParam) == BN_CLICKED) {
                char exprBuf[256], varBuf[2], valBuf[32], diffVarBuf[2];
                GetWindowText(hwndExpr, exprBuf, 256);
                GetWindowText(hwndVar, varBuf, 2);
                GetWindowText(hwndVal, valBuf, 32);
                GetWindowText(hwndDiffVar, diffVarBuf, 2);

        try {
            switch (LOWORD(wParam)) {
                case 1: { // Calculate
                    if (strlen(exprBuf) == 0) {
                        MessageBox(hwnd, "Please input an expression!", "Error", MB_OK | MB_ICONERROR);
                        break;
                    }
                    
                    currentExpr.ReadExpr(exprBuf);
                    
                    // 捕获中缀表达式输出
                    OutputCapture infixCapture;
                    currentExpr.WriteExpr();
                    string infix = formatOutput(infixCapture.getOutput());
                    
                    OutputCapture treeCapture;
                    currentExpr.DisplayTree();
                    string tree = ProcessTreeOutput(formatOutput(treeCapture.getOutput()));
                    
                    // 组合结果
                    string result = "Expression: ";
                    result += exprBuf;
                    result += "\r\nParsed as: ";
                    result += infix;
                    result += "\r\nValue: ";
                    result += to_string(currentExpr.Value());
                    
                    // 显示结果和树
                    SetWindowText(hwndResult, result.c_str());
                    SetWindowText(hwndTree, tree.c_str());
                    break;
                }

                case 2: { // Assign
                    if (!varBuf[0]) {
                        MessageBox(hwnd, "Please input a variable!", "Error", MB_OK | MB_ICONERROR);
                        break;
                    }
                    if (!valBuf[0]) {
                        MessageBox(hwnd, "Please input a value!", "Error", MB_OK | MB_ICONERROR);
                        break;
                    }
                    
                    currentExpr.Assign(varBuf[0], atoi(valBuf));
                    
                    // 捕获赋值后的表达式
                    OutputCapture infixCapture;
                    currentExpr.WriteExpr();
                    string infix = formatOutput(infixCapture.getOutput());
                    
                    string result = "After assigning ";
                    result += varBuf[0];
                    result += " = ";
                    result += valBuf;
                    result += "\r\nExpression: ";
                    result += infix;
                    result += "\r\nValue = ";
                    result += to_string(currentExpr.Value());
                    
                    SetWindowText(hwndResult, result.c_str());
                    break;
                }
                
                case 3: { // 偏导
                    try {
                        if (!diffVarBuf[0]) {
                            MessageBox(hwnd, "Please input a variable for derivative!", "Error", MB_OK | MB_ICONERROR);
                            break;
                        }
                        
                        if (strlen(exprBuf) == 0) {
                            MessageBox(hwnd, "Please input an expression first!", "Error", MB_OK | MB_ICONERROR);
                            break;
                        }

                        Expression expr;
                        string result = "====== Derivative Result ======\r\n";
                        
                        try {
                            expr.ReadExpr(exprBuf);
                            result += "Original expression: ";
                            
                            // 捕获原始表达式输出
                            {
                                OutputCapture origCapture;
                                expr.WriteExpr();
                                result += origCapture.getOutput();
                                result += "\r\n";
                            }
                            
                            // 计算导数
                            Expression derivative = expr.Diff(diffVarBuf[0]);
                            result += "Derivative with respect to ";
                            result += diffVarBuf[0];
                            result += ":\r\n";
                            
                            // 捕获导数表达式输出
                            {
                                OutputCapture derivCapture;
                                derivative.WriteExpr();
                                result += derivCapture.getOutput();
                                result += "\r\n";
                            }
                            
                            // 简化并显示结果
                            result += "Simplified:\n";
                            derivative.MergeConst();
                            {
                                OutputCapture simplifiedCapture;
                                derivative.WriteExpr();
                                result += simplifiedCapture.getOutput();
                            }
                            
                            // 显示结果
                            SetWindowText(hwndResult, result.c_str());
                            
                            // 可选：同时显示一个弹窗
                            MessageBox(hwnd, result.c_str(), "Derivative Result", MB_OK | MB_ICONINFORMATION);
                            
                        } catch (const Expression::ExpressionException& e) {
                            string errorMsg = "Error in expression: ";
                            errorMsg += e.what();
                            MessageBox(hwnd, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
                        }
                        
                    } catch (const exception& e) {
                        string errorMsg = "Unexpected error: ";
                        errorMsg += e.what();
                        MessageBox(hwnd, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
                    }
                    break;
                }
                case 4: { // Clear
                    SetWindowText(hwndExpr,"");
                    SetWindowText(hwndVar,"");
                    SetWindowText(hwndDiffVar, "");
                    SetWindowText(hwndVal,"");
                    SetWindowText(hwndResult, "");
                    SetWindowText(hwndTree, "");
                    SetWindowText(hwndExpr1,"");
                    SetWindowText(hwndExpr2,"");
                    break;
                }
                case 5: { // Compound
                    try {
                        // 获取输入
                        char expr1Buf[256], expr2Buf[256], opBuf[2];
                        GetWindowText(hwndExpr1, expr1Buf, 256);
                        GetWindowText(hwndExpr2, expr2Buf, 256);
                        GetWindowText(hwndOpCombo, opBuf, 2);

                        // 输入验证
                        if (strlen(expr1Buf) == 0 || strlen(expr2Buf) == 0) {
                            MessageBox(hwnd, "Please input both expressions!", "Error", MB_OK | MB_ICONERROR);
                            break;
                        }

                        Expression expr1, expr2;
                        string result = "====== Compound Expression Result ======\n\n";
                        
                        try {
                            // 读取并显示第一个表达式
                            expr1.ReadExpr(expr1Buf);
                            result += "First expression: ";
                            {
                                OutputCapture capture1;
                                expr1.WriteExpr();
                                result += capture1.getOutput();
                                result += "\n\n";
                            }
                            
                            // 读取并显示第二个表达式
                            expr2.ReadExpr(expr2Buf);
                            result += "Second expression: ";
                            {
                                OutputCapture capture2;
                                expr2.WriteExpr();
                                result += capture2.getOutput();
                                result += "\n\n";
                            }
                            
                            // 显示运算符
                            result += "Operator: ";
                            result += opBuf[0];
                            result += "\n\n";
                            
                            // 创建复合表达式
                            Expression compound = Expression::CompoundExpr(opBuf[0], expr1, expr2);
                            
                            // 显示复合结果
                            result += "Compound Result:\n";
                            {
                                OutputCapture captureResult;
                                compound.WriteExpr();
                                result += captureResult.getOutput();
                                result += "\n\n";
                            }
                            
                            // 尝试计算值
                            try {
                                double value = compound.Value();
                                result += "Numeric Value = ";
                                result += to_string(value);
                                result += "\n";
                            } catch (const Expression::ExpressionException&) {
                                result += "Value: Cannot be calculated (contains variables)\n";
                            }

                            // 更新当前表达式
                            currentExpr = compound;
                            
                            // 显示树形结构
                            result += "\nTree Structure:\n";
                            {
                                OutputCapture captureTree;
                                compound.DisplayTree();
                                result += captureTree.getOutput();
                            }
                            
                            // 使用模态对话框显示结果
                            MessageBox(hwnd, result.c_str(), "Compound Expression Result", MB_OK); //| MB_ICONINFORMATION
                            
                            // 更新主窗口显示
                            {
                                OutputCapture finalCapture;
                                compound.WriteExpr();
                                string finalExpr = finalCapture.getOutput();
                                SetWindowText(hwndExpr, finalExpr.c_str());
                            }
                            
                            // 清空输入框
                            SetWindowText(hwndExpr1, "");
                            SetWindowText(hwndExpr2, "");
                            SetWindowText(hwndOpCombo, "");
                            
                        } catch (const Expression::ExpressionException& e) {
                            string errorMsg = "Expression Error: ";
                            errorMsg += e.what();
                            MessageBox(hwnd, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
                        }
                        
                    } catch (const exception& e) {
                        string errorMsg = "Unexpected error: ";
                        errorMsg += e.what();
                        MessageBox(hwnd, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
                    }
                    break;
                }
    
                case 6: { 
                    try {
                        //获取表达式
                        string beforeMerge;
                        {
                            OutputCapture beforeCapture;
                            currentExpr.WriteExpr();
                            beforeMerge = beforeCapture.getOutput();
                        }

                        currentExpr.MergeConst();

                        string afterMerge;
                        {
                            OutputCapture afterCapture;
                            currentExpr.WriteExpr();
                            afterMerge = afterCapture.getOutput();
                        }

                        // Capture the tree structure
                        OutputCapture treeCapture;
                        currentExpr.DisplayTree();
                        string treeStr = ProcessTreeOutput(treeCapture.getOutput());

                        // Prepare the result message
                        string result = "Before merging:\r\n";
                        result += beforeMerge;
                        result += "\r\nAfter merging:\r\n";
                        result += afterMerge;

                        // 更新
                        SetWindowText(hwndResult, result.c_str());
                        SetWindowText(hwndTree, treeStr.c_str());
                        SetWindowText(hwndExpr, afterMerge.c_str());

                    } catch (const Expression::ExpressionException& e) {
                        string errorMsg = "Error while merging constants: ";
                        errorMsg += e.what();
                        MessageBox(hwnd, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
                    }
                    break;
                }
            }
        }
            catch (const Expression::ExpressionException& e) {
                string errorMsg = "Expression Error: ";
                errorMsg += e.what();
                MessageBox(hwnd, errorMsg.c_str(), "Expression Error", MB_OK | MB_ICONERROR);
                SetWindowText(hwndResult, "");
                SetWindowText(hwndTree, "");
            }
            catch (const exception& e) {
                string errorMsg = "Error: ";
                errorMsg += e.what();
                MessageBox(hwnd, errorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
                SetWindowText(hwndResult, "");
                SetWindowText(hwndTree, "");
            }
            catch (...) {
                MessageBox(hwnd, "An unknown error occurred!", "Error", MB_OK | MB_ICONERROR);
                SetWindowText(hwndResult, "");
                SetWindowText(hwndTree, "");
            }
        }
        break;
}

        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow) {
    
    // 注册窗口类
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszClassName = "ExpressionCalculator";
    RegisterClassEx(&wc);

    // 创建窗口
    HWND hwnd = CreateWindow(
        "ExpressionCalculator", "Expression Calculator",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        420, 580,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}