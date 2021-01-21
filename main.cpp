/*
@ Authors: Alessandro Frau, Francesco Apollonio, Alice Benatti, Alex Lorenzato

*/
#include <iostream>
#include <cstring>
#include <conio.h>
using namespace std;

//lista colori:
#define Blue 1
#define Green 2
#define Aqua 3
#define Red 4
#define Purple 5
#define Yellow 6
#define White 7
#define Gray 8
#define Light_Blue 9
#define Black 0
#define Light_Green 10
#define Light_Aqua 11
#define Light_Red 12
#define Light_Purple 13
#define Light_Yellow 14
#define Bright_White 15

//pulisce lo schermo
// questa funzione e' molto lezza, grulla, orripilante, proprio brutta
// non rifatela per nessuno motivo !!!!
void clearscreen(void){
    if(system("cls")){
        system("clear");
    }
}


void color(const int background, const int text){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + 16 * background);
}

void printfile(char filename[]){
    FILE *fp;
    char c;
    fp = fopen(filename, "r");
    while(!feof(fp)){
        fscanf(fp, "%c", &c);
        if(!feof(fp)){
            cout<<c;
        }
    }
    fclose(fp);
}