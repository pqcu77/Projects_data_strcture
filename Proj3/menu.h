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
//     cout<<"             -        1.��һ��ǰ׺���ʽ���в���         -"<<endl;
//     cout<<"             -        2.������ǰ׺���ʽ���и���         -"<<endl;
//     cout<<"             -        PS:����0�˳�������                -"<<endl;
//     cout<<"             -------------------------------------------"<<endl;
//     cout << "�������Ӧ�ı����ѡ������Ҫ�Ĺ���!" << endl;
//     cin >> choice;
//     Expression expr1, expr2,expr3;
//     string e1, e2;
//     int choice2;
//     char c;
//     int val;
    
//     switch(choice){
//         case 1:
//             cout<<"�����빦����ȷ��ǰ׺���ʽ��"<<endl;
//             cin >> e1;
//             expr1.ReadExpr(e1);

            
            
//             while(1){
//                 cout<<"             -------------------------------------------"<<endl;
//                 cout << "           -        ����������Ҫѡ��Ĺ��ܣ�           -" << endl;
//                 cout<<"             -------------------------------------------"<<endl;
//                 cout<<"             -        1.�����׺���ʽ                  -"<<endl;
//                 cout<<"             -        2.�Ա��ʽ�е�ĳ���������и�ֵ     -"<<endl;
//                 cout<<"             -        3.���㷨���ʽ������ֵ             -"<<endl;
//                 cout<<"             -        4.�Ա��ʽ�е�ĳ������x��ƫ������   -"<<endl;
//                 cout<<"             -        5.�Ա��ʽ�еĳ�������кϲ�       -"<<endl;
//                 cout<<"             -        PS:����0�˳�������                -"<<endl;
//                 cout<<"             -------------------------------------------"<<endl;
//                 cin >> choice2;
//                 switch (choice2)
//                 {   
                    
//                     case 1:
//                         expr1.WriteExpr();
//                         break;
//                     case 2:
//                         cout << "��������Ҫ���и�ֵ�ı����ַ�:" << endl;
//                         cin >> c;
//                         cout << "���������������ֵ:" << endl;
//                         cin >> val;
//                         expr1.Assign(c, val);
//                         cout << "��ֵ�ɹ�!" << endl;
//                         break;
//                     case 3:
//                         cout << "���ʽ��ֵ��:";
//                         cout<<expr1.Value()<<endl;
//                         break;
//                     case 4:
//                         cout << "����������Ҫ��ƫ���ı���:" << endl;
//                         cin >> c;
//                         expr2=expr1.Diff(c);
//                         cout << "��ƫ���Ľ��:" << endl;
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
//             cout << "������ǰ׺���ʽ1:" << endl;
//             cin >> e1;
//             expr1.ReadExpr(e1);
//             cout << "������ǰ׺���ʽ2:" << endl;
//             cin >> e2;
//             expr2.ReadExpr(e2);

//             cout << "���������ʽ���и���" << endl;
//             cout << "����������Ҫ���еĲ���(��+,-,*,/,^)" << endl;
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
    cout << "             -        1.��һ��ǰ׺���ʽ���в���         -" << endl;
    cout << "             -        2.������ǰ׺���ʽ���и���         -" << endl;
    cout << "             -        PS:����0�˳�������                -" << endl;
    cout << "             -------------------------------------------" << endl;
    cout << "�������Ӧ�ı����ѡ������Ҫ�Ĺ���!" << endl;
    cin >> choice;

    if (choice == 0) return 0;

    Expression expr1, expr2;
    string e1, e2;
    int choice2;
    char c;
    int val;

    switch (choice) {
        case 1:
            cout << "�����빦����ȷ��ǰ׺���ʽ��" << endl;
            cin >> e1;
            expr1.ReadExpr(e1);

            while (true) {
                cout << "             -------------------------------------------" << endl;
                cout << "           -        ����������Ҫѡ��Ĺ��ܣ�             -" << endl;
                cout << "             -------------------------------------------" << endl;
                cout << "             -        1.�����׺���ʽ                  -" << endl;
                cout << "             -        2.�Ա��ʽ�е�ĳ���������и�ֵ     -" << endl;
                cout << "             -        3.���㷨���ʽ������ֵ             -" << endl;
                cout << "             -        4.�Ա��ʽ�е�ĳ������x��ƫ������   -" << endl;
                cout << "             -        5.�Ա��ʽ�еĳ�������кϲ�       -" << endl;
                cout << "             -        6.չʾ������                      -" << endl;
                cout << "             -        PS:����0�˳�������                -" << endl;
                cout << "             -------------------------------------------" << endl;
                cin >> choice2;

                switch (choice2) {
                    case 1:
                        expr1.WriteExpr();
                        break;
                    case 2:
                        cout << "��������Ҫ���и�ֵ�ı����ַ�:" << endl;
                        cin >> c;
                        cout << "���������������ֵ:" << endl;
                        cin >> val;
                        expr1.Assign(c, val);
                        cout << "��ֵ�ɹ�!" << endl;
                        break;
                    case 3:
                        cout << "���ʽ��ֵ��:";
                        cout << expr1.Value() << endl;
                        break;
                    case 4:
                        cout << "����������Ҫ��ƫ���ı���:" << endl;
                        cin >> c;
                        expr2 = expr1.Diff(c);
                        cout << "��ƫ���Ľ��:" << endl;
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
                        cout << "��Ч��ѡ�����������롣" << endl;
                        break;
                }
            }
            break;

        case 2:
            cout << "������ǰ׺���ʽ1:" << endl;
            cin >> e1;
            expr1.ReadExpr(e1);
            cout << "������ǰ׺���ʽ2:" << endl;
            cin >> e2;
            expr2.ReadExpr(e2);

            cout << "���������ʽ���и���" << endl;
            cout << "����������Ҫ���еĲ���(��+,-,*,/,^)" << endl;
            cin >> c;
            expr1 = expr1.CompoundExpr(c, expr1, expr2);
            expr1.WriteExpr();
            expr1.DisplayTree();
            break;

        case 0:
            return 0;
        
        default:
            cout << "��Ч��ѡ�����������롣" << endl;
            break;
    }

    return 1;
}