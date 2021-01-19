/* 
@ Author: Alice Benatti

- uno che si occupa del game design (
    aumento di livello, statistiche e percentuali), 
    del main, 
    game over e classifica (8)
- i bonus li implementa quello che ha meno roba da fare (ce ne accorgeremo sul momento)

- schermata di inizio (premi invio per iniziare ecc....)
- classifica
- schermata game over
*/
#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include "main.cpp"
#include <fstream>

using namespace std;

#define INVIO 13

void StartScreen();
int Leaderboard();
int PrintMap();


int main(){
    StartScreen();
    
    return 0;
}

// ====== Schermata iniziale: titolo & menù ======
void StartScreen(){
    char key;
    color(Black, Yellow);
    printfile("name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER to play" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    color(Black, Light_Green);
    key=getch();
    if ((int)key==INVIO) PrintMap(); // funzione Alex -> inizia a giocare
    else if ((int)key == 'c' || (int)key == 'C') Leaderboard();
    else  cout << "ERROR: INSERISCI UN VALORE ACCETTATO u.u" << endl;
}

// funzione di alex x fare partire il Gioco
int PrintMap(){
    cout << "Sei in PrintMap u.u" << endl;
    return 0;
}
// ====== Classifica dei punteggi ======c

int Leaderboard(){
    clearscreen();
    cout << "GG Sei nella classifica :D\n" << endl;
    printfile("leaderboard.txt");
    
    getch();
    return 0;
}

