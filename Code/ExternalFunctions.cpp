#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
#include <fstream>
#include "ExternalFunctions.h"
using namespace std;

char find_char(int column, int line){
    char buf[1];
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, 1, coord, (LPDWORD) &num_read);
    return buf[0];
}

void move_cursor(int column, int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"ERROR! (function: movecursor)"<<endl;
    }
}

void hide_cursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

bool is_file_empty(std::ifstream& pFile){
    return pFile.peek() == std::ifstream::traits_type::eof();
}

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