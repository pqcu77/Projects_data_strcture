#include<iostream>
#include"Expression2.h"
using namespace std;

// int menu(){
//     int choice;
//     cout<<"             -------------------------------------------"<<endl;
//     cout<<"             -                                         -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout<<"             -             Welcome  To  Use            -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout<<"             -                                         -"<<endl;
//     cout<<"             -                                         -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout<<"             -                Calculator               -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout<<"             -                                         -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout<<"             -        1.对一个前缀表达式进行操作         -"<<endl;
//     cout<<"             -        2.对两个前缀表达式进行复合         -"<<endl;
//     cout<<"             -        PS:输入0退出计算器                -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout << "请输入对应的编号来选择你需要的功能!" << endl;
//     cin >> choice;
//     Expression expr1, expr2,expr3;
//     string e1, e2;
//     int choice2;
//     char c;
//     int val;
    
//     switch(choice){
//         case 1:
//             cout<<"请输入功能正确的前缀表达式："<<endl;
//             cin >> e1;
//             expr1.ReadExpr(e1);

            
            
//             while(1){
//                 cout<<"             -------------------------------------------"<<endl;
//                 cout << "           -        请输入你想要选择的功能：           -" << endl;
//                 cout<<"             -------------------------------------------"<<endl;
//                 cout<<"             -        1.输出中缀表达式                  -"<<endl;
//                 cout<<"             -        2.对表达式中的某个变量进行赋值     -"<<endl;
//                 cout<<"             -        3.对算法表达式进行求值             -"<<endl;
//                 cout<<"             -        4.对表达式中的某个变量x作偏导运算   -"<<endl;
//                 cout<<"             -        5.对表达式中的常数项进行合并       -"<<endl;
//                 cout<<"             -        PS:输入0退出计算器                -"<<endl;
//                 cout<<"             -------------------------------------------"<<endl;
//                 cin >> choice2;
//                 switch (choice2)
//                 {   
                    
//                     case 1:
//                         expr1.WriteExpr();
//                         break;
//                     case 2:
//                         cout << "请输入你要进行赋值的变量字符:" << endl;
//                         cin >> c;
//                         cout << "请输入这个变量的值:" << endl;
//                         cin >> val;
//                         expr1.Assign(c, val);
//                         cout << "赋值成功!" << endl;
//                         break;
//                     case 3:
//                         cout << "表达式的值是:";
//                         cout<<expr1.Value()<<endl;
//                         break;
//                     case 4:
//                         cout << "请输入你想要求偏导的变量:" << endl;
//                         cin >> c;
//                         expr2=expr1.Diff(c);
//                         cout << "求偏导的结果:" << endl;
//                         expr2.WriteExpr();
//                         expr2.DisplayTree();
//                         break;
//                     case 5:
//                         expr1.MergeConst();
//                         expr1.WriteExpr();
//                         //expr1.DisplayTree();
//                         break;
//                     default:
//                         return 0;
//                         break;
//                     }
                    
//             }
//         break;
//         case 2:
//             cout << "请输入前缀表达式1:" << endl;
//             cin >> e1;
//             expr1.ReadExpr(e1);
//             cout << "请输入前缀表达式2:" << endl;
//             cin >> e2;
//             expr2.ReadExpr(e2);

//             cout << "对两个表达式进行复合" << endl;
//             cout << "请输入你想要进行的操作(如+,-,*,/,^)" << endl;
//             cin >> c;
//             expr3 = expr1.CompoundExpr(c,expr1, expr2);
//             expr3.WriteExpr();
//             expr3.DisplayTree();
//             break;
//         case 0:
//             return 0;
//             break;
//     }
//     return 1;
// }

int menu() {
    int choice;
    cout << "             -------------------------------------------" << endl;
    cout << "             -                                         -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "             -             Welcome  To  Use            -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "             -                                         -" << endl;
    cout << "             -                                         -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "             -                Calculator               -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "             -                                         -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "             -        1.对一个前缀表达式进行操作         -" << endl;
    cout << "             -        2.对两个前缀表达式进行复合         -" << endl;
    cout << "             -        PS:输入0退出计算器                -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "请输入对应的编号来选择你需要的功能!" << endl;
    cin >> choice;

    if (choice == 0) return 0;

    Expression expr1, expr2;
    string e1, e2;
    int choice2;
    char c;
    int val;

    switch (choice) {
        case 1:
            cout << "请输入功能正确的前缀表达式：" << endl;
            cin >> e1;
            expr1.ReadExpr(e1);

            while (true) {
                cout << "             -------------------------------------------" << endl;
                cout << "           -        请输入你想要选择的功能：             -" << endl;
                cout << "             -------------------------------------------" << endl;
                cout << "             -        1.输出中缀表达式                  -" << endl;
                cout << "             -        2.对表达式中的某个变量进行赋值     -" << endl;
                cout << "             -        3.对算法表达式进行求值             -" << endl;
                cout << "             -        4.对表达式中的某个变量x作偏导运算   -" << endl;
                cout << "             -        5.对表达式中的常数项进行合并       -" << endl;
                cout << "             -        6.展示二叉树                      -" << endl;
                cout << "             -        PS:输入0退出计算器                -" << endl;
                cout << "             -------------------------------------------" << endl;
                cin >> choice2;

                switch (choice2) {
                    case 1:
                        expr1.WriteExpr();
                        break;
                    case 2:
                        cout << "请输入你要进行赋值的变量字符:" << endl;
                        cin >> c;
                        cout << "请输入这个变量的值:" << endl;
                        cin >> val;
                        expr1.Assign(c, val);
                        cout << "赋值成功!" << endl;
                        break;
                    case 3:
                        cout << "表达式的值是:";
                        cout << expr1.Value() << endl;
                        break;
                    case 4:
                        cout << "请输入你想要求偏导的变量:" << endl;
                        cin >> c;
                        expr2 = expr1.Diff(c);
                        cout << "求偏导的结果:" << endl;
                        expr2.WriteExpr();
                        expr2.DisplayTree();
                        break;
                    case 5:
                        expr1.MergeConst();
                        expr1.WriteExpr();
                        expr1.DisplayTree();
                        break;
                    case 6:
                        expr1.DisplayTree();
                    case 0:
                        return 1;
                    default:
                        cout << "无效的选择，请重新输入。" << endl;
                        break;
                }
            }
            break;

        case 2:
            cout << "请输入前缀表达式1:" << endl;
            cin >> e1;
            expr1.ReadExpr(e1);
            cout << "请输入前缀表达式2:" << endl;
            cin >> e2;
            expr2.ReadExpr(e2);

            cout << "对两个表达式进行复合" << endl;
            cout << "请输入你想要进行的操作(如+,-,*,/,^)" << endl;
            cin >> c;
            expr1 = expr1.CompoundExpr(c, expr1, expr2);
            expr1.WriteExpr();
            expr1.DisplayTree();
            break;

        case 0:
            return 0;
        
        default:
            cout << "无效的选择，请重新输入。" << endl;
            break;
    }

    return 1;
}