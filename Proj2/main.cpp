#include <iostream>
#include <string>
#include"menu.h"

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