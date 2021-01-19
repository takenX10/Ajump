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
#include <conio.h>
#include <windows.h>
using namespace std;

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
    textcolor(3);
                                        
    gotoxy(10, 11);
    cout << "A jump" << endl;
    cout << "press ENTER to play" << endl;
    cout << "press C to view the leaderboard" << endl;
    key=getchar();
    
    if ((int)key==10) PrintMap(); // funzione Alex -> inizia a giocare
    else if ((int)key == 67 || (int)key ==99) Leaderboard();
    else  cout << "ERROR: INSERISCI UN VALORE ACCETTATO u.u" << endl;
}

// funzione di alex x fare partire il Gioco
int PrintMap(){
    cout << "Sei in PrintMap u.u" << endl;
    return 0;
}

// ====== Classifica dei punteggi ======
int Leaderboard(){
    clrscr();
    cout << "GG Sei nella classifica :D" << endl;

    return 0;
}

