#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

//多项式节点定义
class PolyNode{
    public:
        double c;
        int e;
        PolyNode *next;
        PolyNode(double c,int e):c(c),e(e),next(NULL){}
};

//函数接口
PolyNode *ReadPoly();//输入并建立多项式
void printPoly(const PolyNode* poly);//以整数序列形式输出多项式
PolyNode *AddPoly(const PolyNode* a,const PolyNode* b);//两个多项式相加
PolyNode *SubPoly(const PolyNode *a, const PolyNode *b);//两个多项式相减
double getVal(const PolyNode *poly, int x);//计算多项式在x的值
PolyNode *cal_derived_function(const PolyNode *poly);//计算多项式的导函数
PolyNode *MulPoly(const PolyNode *a, const PolyNode *b);//两个多项式相乘
PolyNode *Sort(const PolyNode *poly);//处理顺序与重复问题
void deletePoly(PolyNode *poly);//删除多项式，释放空间

//函数实现
PolyNode *ReadPoly(){
    cout <<"input your poly(format: c1 e1 c2 e2 ... and q to quit)"<< endl;
    PolyNode *poly = new PolyNode(0.0, 0); // 头节点 ; poly->e is use to store the length of the list;
    PolyNode *curr = poly;
    double c;
    int e;

    while (true) {
        cin >> c; // 先读取系数
        if (cin.fail()) { // 检查输入是否有效
            cin.clear(); // 清除错误标志
            string input;
            cin >> input; // 读取为字符串
            if (input == "q") break; // 如果输入是 "q"，则退出
            cout << "Invalid input, please enter coefficients and exponents." << endl;
            continue; // 继续循环
        }

        cin >> e; // 再读取指数
        if (cin.fail()) { // 检查指数输入是否有效
            cin.clear(); // 清除错误标志
            string input;
            cin >> input; // 读取为字符串
            if (input == "q") break; // 如果输入是 "q"，则退出
            cout << "Invalid input, please enter coefficients and exponents." << endl;
            continue; // 继续循环
        }
        if(!c){
            continue;//去掉系数为0的节点（不存储）
        }
        PolyNode *tmp = new PolyNode(c, e);
        curr->next = tmp;
        curr = curr->next;
        poly->e++; // 更新多项式的长度
    }
    poly=Sort(poly);
    return poly;
}

//sorted version:
void printPoly(const PolyNode* poly){
    PolyNode *curr = poly->next;
    cout << poly->e << " ";
    while(curr){
        cout <<showpos<< curr->c << "x^" <<noshowpos<< curr->e ;
        curr = curr->next;
    }
    cout << endl;
}

PolyNode *AddPoly(const PolyNode* a,const PolyNode* b){
    PolyNode *poly=new PolyNode(0,0);
    PolyNode *curr = poly;
    PolyNode *curr1=a->next, *curr2 = b->next;
    int len = 0;
    while(curr1&&curr2){//a和b都未结束
        if(curr1->e<curr2->e){//a.e > b.e
            curr->next = new PolyNode(curr2->c, curr2->e);
            curr = curr->next;
            curr2 = curr2->next;
        }else if(curr1->e>curr2->e){//a.e < b.e
            curr->next = new PolyNode(curr1->c, curr1->e);
            curr = curr->next;
            curr1 = curr1->next;
        }else{//同阶指向其中一个节点并将系数相加
            if(curr1->c+curr2->c==0){//如果相加为0就消掉了
                curr1 = curr1->next;
                curr2 = curr2->next;
                continue;
            }else{
                curr->next = new PolyNode(curr1->c+curr2->c, curr1->e);
                curr = curr->next;
                curr1 = curr1->next;
                curr2 = curr2->next; // both go to the next one;
            }
            
        }
        len++;
    }

    if(curr1){
        curr->next = curr1;
    }
    if(curr2){
        curr->next = curr2;
    }
    poly->e = len;
    poly=Sort(poly);
    return poly;
}

PolyNode *SubPoly(const PolyNode *a,const  PolyNode *b){
    PolyNode *poly = new PolyNode(0, 0);
    PolyNode *curr = poly;
    PolyNode *curr1 = a->next, *curr2 = b->next;
    while(curr1&&curr2){
        if(curr1->e>curr2->e){ // a.e < b.e
            curr->next = new PolyNode(curr1->c, curr1->e);
            curr1 = curr1->next;
            curr = curr->next;
        }else if(curr1->e<curr2->e){
            curr->next = new PolyNode(-(curr2->c), curr2->e);
            curr2 = curr2->next;
            curr = curr->next;
        }else{
            if(curr1->c==curr2->c){
                curr1 = curr1->next;
                curr2 = curr2->next;
                continue;
            }
            curr->next = new PolyNode((curr1->c) - (curr2->c), curr1->e);
            curr1 = curr1->next;
            curr2 = curr2->next;
            curr = curr->next;
        }
        poly->e++;
    }

    if(curr1){
        curr->next = curr1;
    }
    if(curr2){
        while(curr2){
            curr->next = new PolyNode(-curr2->c, curr2->e);
            curr2 = curr2->next;
        }
        
        
    }
    poly=Sort(poly);
    return poly;
}//两个多项式相减

double getVal(const PolyNode *poly, int x){
    double ans=0;
    PolyNode* curr = poly->next;
    while(curr){
        ans += curr->c * pow(x, curr->e);
        curr = curr->next;
    }
    return ans;
}//计算多项式在x的值

PolyNode *cal_derived_function(const PolyNode *poly){
    PolyNode *curr = poly->next;
    PolyNode *derived_poly = new PolyNode(0, poly->e);
    PolyNode *curr2 = derived_poly;
    while(curr){
        if(curr->e==0){
            //curr2->next = new PolyNode(0, 0);
            derived_poly->e--;
        }else{
            curr2->next = new PolyNode(curr->c * curr->e, (curr->e) - 1);
        }
        curr2 = curr2->next;
        curr = curr->next;
    }
    derived_poly=(derived_poly);
    return derived_poly;

}//计算多项式的导函数

PolyNode *MulPoly(const PolyNode *a,const  PolyNode *b){
    PolyNode *poly = new PolyNode(0, 0);
    PolyNode *curr1 = a->next;

    while(curr1){
        PolyNode *curr2 = b->next;
        PolyNode *tmp = new PolyNode(0, 0);
        PolyNode *curr = tmp;
        while(curr2){
            double c = (curr1->c) * (curr2->c);
            int e = (curr1->e) + (curr2->e);
            if(c!=0){
                curr->next = new PolyNode(c,e);
                curr = curr->next;
            }
            curr2 = curr2->next;
            
            tmp->e+=1;
        }
        poly=AddPoly(poly, tmp);
        curr1 = curr1->next;
    }
    poly=Sort(poly);
    return poly;
}//两个多项式相乘

PolyNode *Sort(const PolyNode *poly){
    PolyNode *NewPoly = new PolyNode(0, 0);
    PolyNode *curr = poly->next;
    PolyNode *curr2 = NewPoly;
    vector<pair<double, int>> p;
    while(curr){
        p.push_back({curr->c, curr->e});
        curr = curr->next;
    }//store all
    sort(p.begin(), p.end(), [](pair<double,int>& a, pair<double,int>& b) { return a.second > b.second; });
    for (const auto& term : p) {
        if (term.first != 0) { // 只添加非零系数的项
            curr2->next = new PolyNode(term.first, term.second);
            curr2 = curr2->next;
        }
    }
    NewPoly->e = p.size();
    return NewPoly;
}

void deletePoly(PolyNode *poly) {
    PolyNode *curr = poly;
    while (curr != NULL) {
        PolyNode *temp = curr;
        curr = curr->next;
        delete temp;
    }
}