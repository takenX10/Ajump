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
#include <string>
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
        int score[CHAR];
        int savedScore;
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
  //  printfile("name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER to play" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "              >> press ESC to exit" << endl;
    color(Black, Light_Green);
    do{
        key=getch();
        if (key==ENTER)PrintMap();
        else if (key== 'C' || key=='c') Leaderboard();
        else if (key==ESC){ clearscreen(); exit(0); }
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
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
    bool check = false;
    
    color(Red, Bright_White);
  //  printfile("gameover.txt");
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        do {
            key=getch();
            if ((int)key == 'y' || (int)key == 'Y') {
                check = true;
                cout << "Insert ur nick: ";
                cin >> input;
                    
                strcpy(LBoard->nick, input);
                LBoard->savedScore = score;
                SaveOnFileWITHOUTid(LBoard);
                cout << "Ur score is saved :D" << endl; 
                delete(LBoard);
                LBoard = SortFiles();
                cout << "SortFiles e' stato eseguito" << endl;
                SaveOnFile(LBoard);
                cout<< "SaveOnFile e' stato eseguito" << endl;
                // Salvo la lista ordinata in modo da stamparla giusta :D
            }
            else if ((int)key == 'n' || (int)key == 'N') {
                check = true;
                cout << "\n\n       >> press SPACE to return at home" << endl;
                do{
                    key=getch();
                    if ((int)key == SPACE) StartScreen();
                    else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;  
                } while(true);
            }
            else{
                check = false;
                cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl; 
            }
        }while (check==false);
        cout << "           >> press C to view the leaderboard" << endl;
        cout << "\n\n       >> press SPACE to return at home" << endl;
        do{
            key=getch();
            if ((int)key == SPACE) StartScreen();
            else if ((int)key == 'c' || (int)key == 'C') Leaderboard();
            else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
        } while(true);
    } while(true);
}

lista SortFiles(){
    lista Lista = new Classifica;
    char ch;
    int counter=0, i=0, k=0;
    int score[maxSaved];
    char nickScore[maxSaved];

    ifstream OpenFile("leaderboard.txt", ios::in);
    lista SortedList = new Classifica;
    
    // prendo i valori salvati di sempre e li inserisco in una lista
    while (!OpenFile.eof()){
        OpenFile.get(ch);
        if (ch=='\n' && counter==2){
            counter=0;
            Lista=Lista->next;
        }
        else if (ch!=UNDERSCORE){
            if (counter == 0){
                Lista->nick[i]=ch;  
                i++;
            } 
            if (counter == 1){
                Lista->score[k]=ch;  
                k++;
            } 
        }
        else counter++;
        OpenFile.ignore(ch);
    }
    OpenFile.close(); // chiudo il file 
    lista tmp = Lista;
    int element=0; // = elementi nella lista classifica
    string stringa; 
    while (Lista->next!=NULL){
        for(int p=0; p<=k; p++){
            stringa+=tmp->score[p];
        }
        tmp->savedScore = stoi(stringa, nullptr, 10);
        score[element]=stoi(stringa,nullptr,10);
        cout << "sono nel salvataggio di score per la volta " << i << endl;
        element++;
        tmp = tmp->next;
    }
    Lista = tmp;
    BubbleSort(score, i);
    // mi salvo quanti salvataggi ho = quanti elementi ho in lista
    FILE * nsaved = fopen("nsaved.txt", "out");
    fprintf(nsaved, "%d", element);
    fclose(nsaved);

    // creo la lista ordinata 
    lista head = new Classifica; head->next->next=NULL;
    while (head->next!=NULL){
        for (int j=0; j<element; j++){
            SortedList->savedScore = score[j];
            while (Lista->savedScore != score[j]){
                Lista = Lista->next;
            }
            strcpy(SortedList->nick, Lista->nick);
            SortedList->id = j;
            Lista = head;
        }
        head = head->next;
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
    fprintf(myfile, "%s_%d_\n", Classifica->nick, Classifica->savedScore);
    fclose(myfile);
}
void SaveOnFile(lista Classifica){
    FILE * myfile = fopen("leader-out.txt", "w");
    while (Classifica->next != NULL){ 
        fprintf(myfile, "%d_%s_%d_\n", Classifica->id, Classifica->nick, Classifica->savedScore);
        Classifica = Classifica->next;
    }
    fclose(myfile);
}

// ====== Classifica dei punteggi ======
void Leaderboard(){
    char key;
    clearscreen();
    cout << "GG Sei nella classifica :D\n" << endl;
 //   printfile("leader-out.txt");
    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen();
        else cout << "ERROR: INSERT A CORRECT VALUE u.u" << endl;
    } while(true);
}
