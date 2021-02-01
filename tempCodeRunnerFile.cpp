/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<windows.h>

using namespace std;


char findchar(int column, int line){
    char buf[1];
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, 1, coord, (LPDWORD) &num_read); // il terzo parametro è il numero di caratteri che leggo in un colpo solo
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
    system("PAUSE");
    return 0;
}