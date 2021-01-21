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
#include <cstdio>
#include <stdio.h>

using namespace std;

#define ENTER 13
#define SPACE 32
#define ESC 27
#define CHAR 30

class Classifica{
    public:
        int id;
        char nick[CHAR];
        int score;
        Classifica *next;
};
typedef Classifica* lista;

void StartScreen();
void GameOver(lista lista, int punti);
void SortFiles();
void SaveOnFile(lista lista);
void Leaderboard();
int PrintMap(); //da cancellare quasi



int main(){
    lista LBoard= new Classifica;
    color(Black, White);
    GameOver(LBoard, 13000);
   // StartScreen();
    return 0;
}

// ====== Schermata iniziale: titolo & menù ======
void StartScreen(){
    clearscreen();
    char key;
    color(Black, Yellow);
   // printfile("name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER to play" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "              >> press ESC to exit" << endl;
    color(Black, Light_Green);
    do{
        key=getch();
        switch(key){
            case ESC:{ 
                clearscreen();
                exit(0);
            }
            case ENTER: PrintMap();
            case 67:  Leaderboard();
            case 99: Leaderboard();
        }
        cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    }
    while (true);
}

// funzione di alex x fare partire il Gioco
int PrintMap(){
    clearscreen();
    char key;
    cout << "Sei in PrintMap u.u" << endl;
    color(Black, White);
    cout << "\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen();
        else if ((int)key==ESC) clearscreen();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
    return 0;
}

// ====== Game Over ======
void GameOver(lista LBoard, int score){
    clearscreen();
    char key;
    char input[CHAR];
    int id;
    
    color(Red, Bright_White);
    printfile("gameover.txt");
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        key=getch();
        if ((int)key == 'y' || (int)key == 'Y') {
            cout << "Insert ur nick: ";
            cin >> input;
            if (LBoard!=NULL){
                while (LBoard->next != NULL){
                    LBoard=LBoard->next;
                    id++;
                } 
            }
            else id=1;
            LBoard->id=id;       
            strcpy(LBoard->nick, input);
            LBoard->score=score;
            cout << "Ur score is saved :D" << endl;
            SaveOnFile(LBoard);
            //cout << "SaveOnFile è stato eseguito " << endl;

        }
        else if ((int)key == 'n' || (int)key == 'N') {
            cout << "\n\n       >> press SPACE to return at home" << endl;
            do{
                key=getch();
                if ((int)key == SPACE) StartScreen();
                else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;  
            } while(true);
        }
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl; 
    } while(true);
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen();
        else if ((int)key == 'c' || (int)key == 'C') Leaderboard();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
}

void SortFiles(lista Lista){
    
    

}

void SaveOnFile(lista Classifica){
    FILE * myfile = fopen("leaderboard.txt", "a");

    fprintf(myfile, "%d  %s  %d \n", Classifica->id, Classifica->nick, Classifica->score);
    fclose(myfile);
}

// ====== Classifica dei punteggi ======
void Leaderboard(){
    char key;
    clearscreen();
    cout << "GG Sei nella classifica :D\n" << endl;
    printfile("leaderboard.txt");
    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
}
