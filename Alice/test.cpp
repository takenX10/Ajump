/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
    ofstream fp;
    fp.open("testfile.txt");
    string i;
    if(fp.is_open()){
        fp<<"banana33";
    }
    fp.close();
    return 0;
}