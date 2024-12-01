#include <iostream>
#include"menu.h"
using namespace std;

int main(){
    while(1){
        system("clear");
        int flat=menu();
        if(flat==0){
            break;
        }
    }
    return 0;
}