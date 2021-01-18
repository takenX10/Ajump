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
#include<iostream>
using namespace std;

void StartScreen();

int main(){
   StartScreen();
    return 0;
}

void StartScreen(){
    char key;
    char title;
    cout << title;
    cout << "press enter to play";
    cout << "press C to view the leaderboard";
    cin << key;
    if (key == 10) goto "play";
    else if (key == 67 || key == 99) goto "classifica";
    else cout << "ERROR: u've digited wrong u.u";
}