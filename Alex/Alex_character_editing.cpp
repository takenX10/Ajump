#include <iostream>
#include <windows.h>
#include "Alex_character_editing.hpp"
using namespace std;

//merge in main


/*  
    INFO: legge caratteri gia presenti nel terminale
    PARAMETRI: riga e colonna del carattere da leggere
    RETURN: carattere letto    
*/
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

/*  
    INFO: sposta il cursore del terminale
    PARAMETRI: riga e colonna del carattere da leggere
    RETURN: void    
*/
void moveCursor(int column, int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"ERROR! (function: movecursor)"<<endl;
    }
}

/*  
    INFO: nasconde il cursore del terminale (quadratino bianco)
    PARAMETRI: nessuno
    RETURN: void
    ALTRO: va richiamata nel main    
*/
void hidecursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
