/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;


void find_multiple_char(int column, int line, char buf[], int size){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, size, coord, (LPDWORD) &num_read);
}

char findchar(int column, int line){
    char buf[1];
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, 1, coord, (LPDWORD) &num_read);
    return buf[0];
}

void movecursor(int column, int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"oh rabbia, un errore!"<<endl;
    }
}

int main(){
    cout<<"123456789"<<endl;
    cout<<"123456789"<<endl;
    cout<<"123456789"<<endl;
    cout<<"123456789"<<endl;
    cout<<findchar(1,1);
    system("PAUSE");
    movecursor(1, 1);
    cout<<"ao";
    movecursor(5, 1);
    cout<<"sa";
    getch();
    return 0;
}