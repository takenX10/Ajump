#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include "screen_manager.h"
using namespace std;



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