/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<windows.h>
using namespace std;

int main(){
    for(int i = 1; i<256;i++){
        cout<<i<<":\t"<<(char)i<<endl;
    }
    system("PAUSE");
    return 0;
}