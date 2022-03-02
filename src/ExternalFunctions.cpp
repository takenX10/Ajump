#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
#include <fstream>
#include "ExternalFunctions.h"
using namespace std;

/*  Author:         Alessandro Frau / StackOverflow
    Parameters:     column -> colonna del carattere
                    line -> riga del carattere
    Return value:   Carattere presente nelle cordinate passate
    Comments:       Restituisce il carattere nella console alle cordinate passate
*/
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

/*  Author:         Alessandro Frau / StackOverflow
    Parameters:     column -> colonna in cui muovere il cursore
                    line -> riga in cui muovere il cursore
    Return value:   void
    Comments:       Muove il cursore della console nelle cordinate passate
*/
void move_cursor(int column, int line){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"ERROR! (function: movecursor)"<<endl;
    }
}

/*  Author:         Alessandro Frau / StackOverflow
    Parameters:     void
    Return value:   void
    Comments:       Nasconde il cursore dalla console
*/
void hide_cursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

/*  Author:         Alessandro Frau
    Parameters:     pfile -> puntatore a file
    Return value:   Restituisce true se il file e' vuoto, false altrimenti
    Comments:       funzione che controlla se un file e' vuoto oppure no
*/
bool is_file_empty(std::ifstream& pFile){
    return pFile.peek() == std::ifstream::traits_type::eof();
}

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   void
    Comments:       funzione che pulisce lo schermo della console
*/
void clearscreen(void){
    if(system("cls")){
        system("clear");
    }
}

/*  Author:         Alessandro Frau
    Parameters:     background -> colore dello sfondo
                    text -> colore del testo
    Return value:   void
    Comments:       Funzione che cambia il colore della console dal punto attuale in poi dei colori passati
*/
void color(const int background, const int text){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + 16 * background);
}

/*  Author:         Alessandro Frau
    Parameters:     filename -> nome del file
    Return value:   void
    Comments:       Funzione che printa nella console l'intero contenuto di un file
*/
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