/*
@ Author: Alessandro Frau

*/
#include<iostream>
#include<cstring>
#include<conio.h>
#include<windows.h>
#include<thread>
#include<chrono>
#include "main.cpp"
using namespace std;

#define ROW_DIM 25
#define MAP_HEIGHT 30
#define REFRESH_RATE 30     // durata della sleep tra un print e l'altro UwU

struct Map
{
    char row[ROW_DIM];
    long int num_row;    // identificatore univoco riga
    Map* prev;
    Map* next;
};

typedef Map* ptr_Map;

struct Position
{
    int x, y; // coordinata orizzontale
};


void newPlayer(Position *p){
    p->y = 0;
    p->x = 5;
}

ptr_Map firstRow(ptr_Map firstRow){   
    firstRow->next = NULL;  // riempio il first row, e ci metto un NULL come next
    firstRow->num_row = 0;

    char stringRow[ROW_DIM];
    for(int i=0; i<ROW_DIM-1; i++) { stringRow[i] = '_'; }
    stringRow[ROW_DIM-1] = '\0';
    strcpy(firstRow->row, stringRow); 

    return firstRow;
}

ptr_Map newRow(ptr_Map paramRow){
    ptr_Map newRow = new Map;
    newRow->num_row = paramRow->num_row+1;
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

    if(paramRow->num_row % 2 == 0) // caso riga "piena"
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

ptr_Map newMap(ptr_Map map){
    map = firstRow(map); // generazione prima riga
    ptr_Map tmp = map;
    for(int i=0; i<MAP_HEIGHT; i++){ 
        tmp = newRow(tmp); 
    } // generazione righe successive
    return map;
}

void keyControl(int keyPressed, Position *p, ptr_Map map){
    while(map->next != NULL) { map = map->next; }
    if( (p->x == 0 && keyPressed == 75) || (p->x == ROW_DIM-2 && keyPressed == 77) || (p->y == 0 && keyPressed == 80) ) { keyPressed = 40; }

    switch(keyPressed)
    {
        case(32): // spazio

        break;

        case(72): // su
            p->y += 2;
            if(p->y > map->num_row - MAP_HEIGHT + 4) // se l'icona giocatore supera una certa altezza, viene creata una nuova riga 
            {                                  // 
                map = newRow(map);
                map = newRow(map);
            }
            
        break;
        
        case(80): // giu
            p->y -= 2;
        break;
        
        case(77): // dx
            p->x += 1;
        break;

        case(75): // sx
            p->x -= 1;
        break;
    }
}

void printRow(ptr_Map paramRow, Position *p){
    cout << (char) 177 << " ";
    for(int i=0; i<ROW_DIM; i++) 
    { 
        if(paramRow->num_row == p->y && i == p->x) // riga in cui c'è icona giocatore
        {
            cout << '@';
        }
        else
        {
            cout << paramRow->row[i]; 
        }
    }
    cout << (char) 177 << " ";
    cout << " " <<paramRow->num_row;
}

void printMap(ptr_Map mapHead, Position *p){
    ptr_Map map;
    while(true){
        map = mapHead;
        Sleep(REFRESH_RATE);
        clearscreen();
        // stampa righe da x a y   
        // endl dopo ogni riga
        int tmpy=p->y;
        if(p->y < 6){ tmpy = 5;}
        while(map->num_row != (tmpy-6+MAP_HEIGHT) ){ map = map->next; } // punto alla riga indexTop
        for(int i=0; i<MAP_HEIGHT; i++) // stampo le MAP_HEIGHT righe
        {
                printRow(map, p);
                cout << endl;
                map = map->prev;
        }
    }
}

void sposta_player(ptr_Map mappa, Position *player){
    int key;
    while(true) {
        key = (int) getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        keyControl(key, player, mappa);
    }
}

int main(){
    ptr_Map map = new Map; // creo puntatore mappa, salvo la testa
    Position *p = new Position;         // creo giocatore e inizializzo la sua posizione
    newPlayer(p);
    map = newMap(map);   // creo i primi MAP_HEIGHT piani e li stampo
    thread print_map_thread(printMap, map, p);
    thread get_position(sposta_player, map, p);
    
    print_map_thread.join();
    get_position.join();
    return 0;
}