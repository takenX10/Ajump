#include<iostream>
#include<windows.h>
#include "print_functions.h"
using namespace std;

char findChar(int column, int line){
    char buf[1];
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, 1, coord, (LPDWORD) &num_read);
    return buf[0];
}

void moveCursor(int column, int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"ERROR! (function: movecursor)"<<endl;
    }
}

void hidecursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
