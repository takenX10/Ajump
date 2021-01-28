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
#include <fstream>

using namespace std;

#define ENTER 13
#define SPACE 32
#define ESC 27
#define CHAR 30
#define UNDERSCORE 95
#define maxSaved 100

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
lista SortFiles();
void BubbleSort(int a[], int lenght);
void Swap(int& x, int& j);
void SaveOnFileWITHOUTid(lista Classifica);
void SaveOnFile(lista lista);
void Leaderboard();
int PrintMap(); //da cancellare quasi



int main(){
    lista LBoard= new Classifica;
    color(Black, White);
    GameOver(LBoard, 898283);
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
                break;
            }
            case ENTER: PrintMap(); break;
            case 67:  Leaderboard();break;
            case 99: Leaderboard(); break;
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
   // printfile("gameover.txt");
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        key=getch();
        if ((int)key == 'y' || (int)key == 'Y') {
            cout << "Insert ur nick: ";
            cin >> input;
                
            strcpy(LBoard->nick, input);
            LBoard->score=score;
            SaveOnFileWITHOUTid(LBoard);
            cout << "Ur score is saved :D" << endl; 
            
            LBoard = SortFiles();
            cout << "SortFiles è stato eseguito" << endl;
            SaveOnFile(LBoard); // Salvo la lista ordinata in modo da stamparla giusta :D
        //    printfile("leaderboard.txt");
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

lista SortFiles(){
    lista Lista = new Classifica;
    char ch;
    int counter=0;
    int score[maxSaved];
    char nickScore[maxSaved];

    ifstream OpenFile("leaderboard.txt", ios::in);
    lista SortedList = new Classifica;
    
    // prendo i valori salvati di sempre e li inserisco in una lista
    while (!OpenFile.eof()){
        OpenFile.get(ch);
        if (ch=='\n'){
            counter=0;
            Lista=Lista->next;
        }
        else if (isspace(ch)!=0){
            if (counter == 0) strcat(Lista->nick, &ch);
            if (counter == 1) Lista->score+= ch;
        }
        else counter++;
    }
    OpenFile.close(); // chiudo il file 
    lista tmp = Lista;
    int i=0; // = elementi nella lista classifica
    while (Lista->next!=NULL){
        score[i]=tmp->score;
        cout << "sono nel salvataggio di score per la volta " << i << endl;
        i++;
        tmp = tmp->next;
    }
    BubbleSort(score, i);
    // mi salvo quanti salvataggi ho = quanti elementi ho in lista
    FILE * nsaved = fopen("nsaved.txt", "out");
    fprintf(nsaved, "%d", i);
    fclose(nsaved);

    // creo la lista ordinata 
    while (Lista->next!=NULL){
        for (int j=0; j<i; j++){
            SortedList->score = score[j];
            while (Lista->score!=score[j]){Lista = Lista->next; }
            strcpy(SortedList->nick, Lista->nick);
            SortedList->id = j;
        }
    }
    return SortedList;
}

void BubbleSort(int a[], int lenght){
    int i, j;
    for (i=0; i<lenght; i++){
        for (j=0; j<lenght-1-i; j++){
            if (a[j]>a[j+1]) Swap(a[j], a[j+1]);
        }
    }
}
void Swap(int& x, int& j){
    int tmp = x;
    x = j;
    j  = tmp;
}
void SaveOnFileWITHOUTid(lista Classifica){
    FILE * myfile = fopen("leaderboard.txt", "a");

    fprintf(myfile, "%s_%d_\n", Classifica->nick, Classifica->score);
    fclose(myfile);
}
void SaveOnFile(lista Classifica){
    FILE * myfile = fopen("leader-out.txt", "a");
    while (Classifica->next != NULL)
        fprintf(myfile, "%d_%s_%d_\n", Classifica->id, Classifica->nick, Classifica->score);
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
