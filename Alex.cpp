/*
@ Author: Alex Lorenzato
*/

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include "main.cpp"
using namespace std;

// dimensioni mappa giocabile
#define ROW_DIM 25
#define MAP_HEIGHT 30

struct Map
{
    char row[ROW_DIM];
    long int numRow;    // identificatore univoco riga
    Map* prev;
    Map* next;
};
typedef Map* ptr_Map;

struct Position
{
    int x, y; // coordinata orizzontale
};


/* 
INFO: stampa di una riga 
PARAMETRI: puntatore alla riga da stampare
RETURN: void
*/
void printRow(ptr_Map paramRow)
{
    cout << (char) 177 << " ";
    for(int i=0; i<ROW_DIM; i++) { cout << paramRow->row[i]; }
    cout << (char) 177 << " ";
    cout << " " <<paramRow->numRow;
}

/* 
INFO: creazione prima riga 
PARAMETRI: puntatore a una mappa vuota
RETURN: puntatore alla row numero 0 
*/
ptr_Map firstRow(ptr_Map firstRow)
{   
    firstRow->next = NULL;  // riempio il first row, e ci metto un NULL come next
    firstRow->numRow = 0;

    char stringRow[ROW_DIM];
    for(int i=0; i<ROW_DIM-1; i++) { stringRow[i] = '_'; }
    stringRow[ROW_DIM-1] = '\0';
    strcpy(firstRow->row, stringRow); 

    return firstRow;
}

/*
INFO: generazione nuova riga, in particolare la configurazione di piattaforme e spazi 
PARAMETRI: puntatore all'ultima riga generata (ultimo nodo della lista) per evitare di dover scorrere ogni volta dal primo elemento
           all'ultimo, visto che il gioco è studiato per essere senza fine
RETURN: puntatore alla riga generata dalla funzione (nuovo ultimo nodo della lista)
*/
ptr_Map newRow(ptr_Map paramRow) // paramRow è l'ultimo nodo della lista
{
    ptr_Map newRow = new Map;
    newRow->numRow = paramRow->numRow+1;
    newRow->prev = paramRow;
    newRow->next = NULL;
    paramRow->next = newRow;

    /*
            int a = rand() % 6 + 2;                     // piattaforma 1 -> 2-7 spazi
            int b = rand() % 6 + 2;                     // piattaforma 2 -> 2-7 spazi
            int c = rand() % 6 + 2;                     // piattaforma 3 -> 2-7 spazi
            int sumRandom = a+b+c;                      // totale spazi occupati da piattaforme nella riga
            int spaces = ROW_DIM - sumRandom;           // spazi rimanenti
            int numSpaces = rand() % 4 + 1;             // quanti spazi vuoti (spazi vuoti = serie di spazi consecutivi) ci saranno in una riga
            int index = 0;                              // indice che mi dice fino a che colonna ho stampato
            if(numSpaces == 4)
            {
                for(int i=0; i<; i++) { cout << (char) 196; }
                
            }
                for(int i=0; i<a; i++) { cout << (char) 196; }
            // |-- ---- -----       |            |   ----    --       -- |
            // stringRow[i] = (char) 196;*/
    char stringRow[ROW_DIM];

    if(paramRow->numRow % 2 == 0) // caso riga "piena"
    {
        /*for(int i=0; i<ROW_DIM-1; i++)
        {
            stringRow[i] = '-'; 
        }*/
        int a = rand() % 12 +1; // piattaforma di 1-12 spazi
        int b = ROW_DIM/2 - a +1;
        int r1 = rand() % 7;
        int r2 = rand() % 7;
        int i=0;
        //cout << "a: "<< a << " b: " << b << " r1: " << r1 << " r2: " << r2 << endl; 
        for(i=0; i<r1; i++){ stringRow[i] = ' ';}
        for(i=i; i<r1+a; i++){stringRow[i] = (char) 196;}
        for(i=i; i<r1+a+r2; i++){ stringRow[i] = ' ';}
        for(i=i; i<r1+a+r2+b; i++){stringRow[i] = (char) 196;}
        for(i=i; i<ROW_DIM-1; i++){ stringRow[i] = ' ';}
    }
    else
    {
        for(int i=0; i<ROW_DIM-1; i++)
        {
            stringRow[i] = ' '; 
        }
    }
    
    stringRow[ROW_DIM-1] = '\0';
    strcpy(newRow->row, stringRow); 

    return newRow;  // ritorna l'ultima riga della mappa
}

/* 
INFO: inizializzazione mappa: generazione firstRow e MAP_HEIGHT-1 righe aggiuntive; generazione Player
PARAMETRI: puntatore a una mappa vuota; i parametri del Player sono fissi
RETURN: puntatore alla riga numero 0 (testa della mappa)
*/
ptr_Map newMap(ptr_Map map, Position p)
{
    // generazione righe
    map = firstRow(map);
    ptr_Map tmp = map;
    for(int i=0; i<MAP_HEIGHT-1; i++){ map = newRow(map); }
    // stampa Player
    map = tmp;
    map = map->next->next;
    map->row[p.x] = '@';
    return tmp;
}

/*
INFO: stampa di una "schermata", ovvero di MAP_HEIGHT piani dati da indice inferiore e superiore
PARAMETRI: puntatore alla TESTA della mappa (row numero 0)
RETURN: void
*/
void printMap(ptr_Map map, int indexBot, int indexTop)
{
    // clear screen
    // stampa righe da x a y   
    // endl dopo ogni riga
    while(map->numRow != indexTop-1){ map = map->next; }
    for(int i=0; i<30; i++)
    {
        printRow(map);
        cout << endl;
        map = map->prev;
    }
}

/*
INFO: inizializzazione del giocatore (posizionamento alla row 2 e colonna 5)
PARAMETRI: puntatore al giocatore e alla mappa
RETURN: void
*/
void newPlayer(Position &p, ptr_Map map)
{
    ptr_Map tmp = map->prev;
    p.y = 2;
    p.x = 0;
    while(p.x < 5){ p.x = p.x + 1; } //tmp->row[p.x] != (char) 196
}

void controlPlayer()
{
    char a;
    int b;
    while(true)
    {
        Sleep(5);
        if(kbhit())
        {
            while(kbhit())
            {
                a = getch();
            }
        cout << a;  
        }
        else{
            cout << "no";
        }
    }
}

void moveTo(Position p)
{
    clearscreen();
    for(int i=0; i<p.x; i++)
    {
        cout << " ";
    }
    cout << "@";
}

/************************************************************************** MAIN ***************************************************************************/
/************************************************************************** MAIN ***************************************************************************/

int main()
{
    /*ptr_Map map = new Map;
    ptr_Map mapHead = map;
    Position p;
    newPlayer(p, map);
    map = newMap(map, p);
    printMap(mapHead, 0, 30);*/
    controlPlayer();
    system("PAUSE");
    return 0;
}

/*
//definizione dei tasti premuti (le lettere considerate sono quelle minuscole)
#define SPACE 32
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
[21:18] LuigiBrosNin >[T☆S☆G]<: void Cursore(bool visible)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infoCursore;
    GetConsoleCursorInfo(output, &infoCursore);
    infoCursore.bVisible = visible;
    SetConsoleCursorInfo(output, &infoCursore);
}
[21:18] LuigiBrosNin >[T☆S☆G]<: char tastoPremuto = _getch();
[21:19] LuigiBrosNin >[T☆S☆G]<: switch (tastoPremuto)
        {
            //movimento a sx
        case KEY_A:
        case 'A':
        case ARROW_LEFT:
[21:22] LuigiBrosNin >[T☆S☆G]<: system("cls");
void Setup(Player p, plat l[]) {
    Clear();
    //prima riga
    cout << (char)201;
    for (int i = 1; i < width; i++)
    {
        cout << (char)205;
    }
    cout << (char)187<<endl;
    //righe centrali + player + piattaforma
    for (int i = 1; i < height ; i++)
    {
        for (int j = 0; j < width+1 ; j++)
        {
            if ((i == p.getY()) && (j == p.getX())) {
                cout << "@";
            }
            else {
                if ((j == 0) || (j == width))
                {
                    cout << (char)186;
                }
                else if (l[i].x[j]=='') cout << "";
                else if (l[i].x[j] == ' ') cout << " ";
                else
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    //riga finale
    cout << (char)200;
    for (int i = 1; i < width; i++)
    {
        cout << (char)205;
    }
    cout << (char)188;
    */