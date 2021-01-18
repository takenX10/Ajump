/* conio.h
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
#include<cstring>
using namespace std;

void StartScreen();
int Leaderboard();
int PrintMap();

int main(){
    StartScreen();
    return 0;
}

void StartScreen(){
    char key;
        
    cout << "Ajump" << endl;                                         
    cout << "press SPACE to play" << endl;
    cout << "press C to view the leaderboard" << endl;
    cin >> key;
    
    if ((int)key==10) PrintMap();
    else if ((int)key == 67 || (int)key ==99) Leaderboard();
    else  cout << "ERROR: hai scritto male u.u" << endl;
}

int PrintMap(){
    cout << "Sei in PrintMap u.u" << endl;
    return 0;
}

int Leaderboard(){
    cout << "GG Sei nella classifica :D" << endl;
    return 0;
}

