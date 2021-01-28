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

/*  INFO: inizializzazione mappa: generazione firstRow e MAP_HEIGHT-1 righe aggiuntive; generazione Player
    PARAMETRI: puntatore a una mappa vuota; i parametri del Player sono fissi
    RETURN: puntatore alla riga numero 0 (testa della mappa)    */
ptr_Map newMap(ptr_Map map, Position p);

/*  INFO: creazione prima riga 
    PARAMETRI: puntatore a una mappa vuota
    RETURN: puntatore alla row numero 0     */
ptr_Map firstRow(ptr_Map firstRow);

/*  INFO: generazione nuova riga, in particolare la configurazione di piattaforme e spazi 
    PARAMETRI: puntatore all'ultima riga generata (ultimo nodo della lista) per evitare di dover scorrere ogni volta dal primo elemento
               all'ultimo, visto che il gioco è studiato per essere senza fine
    RETURN: puntatore alla riga generata dalla funzione (nuovo ultimo nodo della lista)    */
ptr_Map newRow(ptr_Map paramRow); 

/*  INFO: inizializzazione del giocatore (posizionamento alla row 2 e colonna 5)
    PARAMETRI: puntatore al giocatore e alla mappa
    RETURN: void    */
void newPlayer(Position &p, ptr_Map map);

/*  INFO: stampa di una riga 
    PARAMETRI: puntatore alla riga da stampare
    RETURN: void     */
void printRow(ptr_Map paramRow, Position p);

/*  INFO: stampa di una "schermata", ovvero di MAP_HEIGHT piani partendo dall' indice superiore
    PARAMETRI: puntatore alla TESTA della mappa (row numero 0), posizione giocatore
    RETURN: void    */
void printMap(ptr_Map map, Position p);


void controlPlayer();

Position keyControl(int keyPressed, Position &p, ptr_Map map);

/************************************************************************** MAIN ***************************************************************************/
/************************************************************************** MAIN ***************************************************************************/

int main()
{
    ptr_Map map = new Map; // creo puntatore mappa, salvo la testa
    ptr_Map mapHead = map;
    Position p;         // creo giocatore e inizializzo la sua posizione
    newPlayer(p, map);
    map = newMap(map, p);   // creo i primi MAP_HEIGHT piani e li stampo
    printMap(mapHead, p);
    
    int key = 0;
    int glo=0;
    ptr_Map tmpp = mapHead;
    while(true) 
    {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
       Sleep(500);
        keyControl(key, p, map); 
        printMap(mapHead, p);

        tmpp = mapHead;
        glo++;
        while(tmpp->next != NULL){ tmpp = tmpp->next; } cout << "Riga max:" << tmpp->numRow << " glo " << glo;
    }

    system("PAUSE");
    return 0;
}

/************************************************************************** MAIN ***************************************************************************/
/************************************************************************** MAIN ***************************************************************************/

void printRow(ptr_Map paramRow, Position p)
{
    cout << (char) 177 << " ";
    for(int i=0; i<ROW_DIM; i++) 
    { 
        if(paramRow->numRow == p.y && i == p.x) // riga in cui c'è icona giocatore
        {
            cout << '@';
        }
        else
        {
            cout << paramRow->row[i]; 
        }
    }
    cout << (char) 177 << " ";
    cout << " " <<paramRow->numRow;
}

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

ptr_Map newRow(ptr_Map paramRow)
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

ptr_Map newMap(ptr_Map map, Position p)
{
    map = firstRow(map); // generazione prima riga
    ptr_Map tmp = map;  
    for(int i=0; i<MAP_HEIGHT; i++){ map = newRow(map); } // generazione righe successive

    return tmp;
}

void printMap(ptr_Map map, Position p)
{
    clearscreen();
    // stampa righe da x a y   
    // endl dopo ogni riga
    int tmpy=p.y;
    if(p.y < 6){ tmpy = 5;}
    while(map->numRow != (tmpy-6+MAP_HEIGHT) ){ map = map->next; } // punto alla riga indexTop
    for(int i=0; i<MAP_HEIGHT; i++) // stampo le MAP_HEIGHT righe
    {
            printRow(map, p);
            cout << endl;
            map = map->prev;
    }
}

void newPlayer(Position &p, ptr_Map map)
{
    ptr_Map tmp = map->prev;
    p.y = 0;
    p.x = 5;
}

void controlPlayer()
{
    char a;
    int b=0;
    while(true)
    {
        if(kbhit())
        {
            b=b+1;
            //moveTo(b,b);
        }
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

Position keyControl(int keyPressed, Position &p, ptr_Map map)
{
    while(map->next != NULL) { map = map->next; }
    if( (p.x == 0 && keyPressed == 75) || (p.x == ROW_DIM-2 && keyPressed == 77) || (p.y == 0 && keyPressed == 80) ) { keyPressed = 40; }

    switch(keyPressed)
    {
        case(32): // spazio

        break;

        case(72): // su
            p.y += 2;
            if(p.y > map->numRow - MAP_HEIGHT + 4) // se l'icona giocatore supera una certa altezza, viene creata una nuova riga 
            {                                  // 
                map = newRow(map);
                map = newRow(map);
            }
            
        break;
        
        case(80): // giu
            p.y -= 2;
        break;
        
        case(77): // dx
            p.x += 1;
        break;

        case(75): // sx
            p.x -= 1;
        break;
    }
    return p;
}