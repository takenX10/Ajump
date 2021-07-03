#include <cstring>
#include <fstream>
#include "screen_manager.h"
#include "costanti.hpp"
using namespace std;

Classifica::Classifica(char filename[]){
    strcpy(this->filename, filename);
    this->head = this->get_file();
}

bool is_file_empty(std::ifstream& pFile){
    return pFile.peek() == std::ifstream::traits_type::eof();
}

/*
    - apro il file Leaderboard.txt
    - prendo i valori e li salvo in lista
*/
plista Classifica::get_file(void){
    ifstream OpenFile;
    OpenFile.open(this->filename,ios::in);
    int c;
    plista head = NULL;
    plista aux;
    plista tmp = NULL;
    int pass;
    string stringa;
    int count = 1; // Inserisco un count affinchè non vengano letti più di 9 elementi. Per qualche motivo sennò si bugga in stoi.
    while (!is_file_empty(OpenFile) &&!OpenFile.eof() && count < 10){
        tmp = new lista_classifica;
        getline(OpenFile, stringa, '\n');
        if(strcmp(stringa.c_str(), "")){
            strcpy(tmp->nick, stringa.substr(stringa.find(' ',1)+1, stringa.find(' ', 3)-2).c_str());   
            tmp->score = stoi(stringa.substr(stringa.find(' ', 2)+1, stringa.find('\n')-1));

            if (head == NULL){
                head = new lista_classifica;
                head = tmp;
                aux = tmp;
                tmp = NULL;
            }
            else{
                aux->next = tmp;
                aux = aux->next;
                tmp = NULL;
            }
            count ++;
        }   

    }
    this->registered_scores = count;
    aux->next = NULL;
   //OpenFile.close();
    this->head = head;
    return head;
}
// TODO: Fixare le funzioni per la classifica nei casi limite
/* 
    aggiungo alla lista nel punto desiderato
    - salvo in lista new_val i nuovi valori
    - scorro la lista e trovo il punto di inserimento
    - creo tmp aggiungo in testa il nuovo elemento
    - allaccio le liste
*/
void Classifica::add_value(int score, char nick[]){
    plista tmp = this->head;
    plista new_val = new lista_classifica;
    new_val->score = score;
    strcpy(new_val->nick, nick);
    if (tmp == NULL){
        new_val->next = NULL;
        this->head = new_val;
    }else if (tmp->score < new_val->score ){
        this->head = new_val;
        new_val->next = tmp;
    }else{
        bool exit = false;
        while (tmp->next != NULL && exit == false){
            if (tmp->next->score <= new_val->score){
                new_val->next = tmp->next;
                tmp->next = new_val;
                exit = true;
            }
            tmp = tmp->next;
        }
        if (exit == false){
            tmp->next = new_val;
            new_val->next = NULL;
        }
    }
}

/*
    salvo nel file Leaderboard.txt la lista inserendo la posizione in classifica
*/

void Classifica::save_file(){
    plista tmp = this->head;
    ofstream myfile;
    myfile.open(this->filename);
    int i = 1;
    while (tmp != NULL){         
        myfile<<i<<" "<<tmp->nick<<" "<<tmp->score;
        if(tmp->next != NULL){
            myfile<<"\n";
        }
        myfile.flush();
        tmp = tmp->next;
        i++;
    }
    myfile.close();
}

int Classifica::get_scoreboard_lenght(){
    return this->registered_scores;
}

plista Classifica::get_position(int position){
    plista tmp = this->head;
    int i = 1;
    while(i < position && tmp != NULL){
        tmp = tmp->next;
        i++;
    }
    if(i != position){
        return NULL;
    }
    return tmp;
}

// ====== Schermata iniziale: titolo & menu' ======
void StartScreen(Classifica LBoard){
    clearscreen();
    char key; bool check= false;
    color(Black, Light_Yellow);
    printfile("Documents\\name.txt");
    color(Black, Bright_White);
    cout << "\n       >> press ENTER to play" << endl;
    cout << "           >> press C to view the leaderboard" << endl;
    cout << "              >> press ESC to exit" << endl;
    color(Black, Light_Green);
    do{
        key=getch();
        if (key==ENTER){
            check = true;
            PrintMap(LBoard);
        } 
        else if (key== 'C' || key=='c') {
            check= true;
            Leaderboard(LBoard, LBoard.get_scoreboard_lenght());
        }
        else if (key==ESC){ check = true; clearscreen(); exit(0); }
        else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
    }
    while (check==false);
}

// funzione di alex x fare partire il Gioco + navigabilità (se serve)
void PrintMap(Classifica LBoard){
    clearscreen();
    color(Black, White);
    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    Lista_proiettili proiettili = Lista_proiettili(&m, &p);
    Lista_nemici ent = Lista_nemici(&m, &p, &proiettili);
    Bonus bonus = Bonus(&m, &p, &ent, &proiettili);
    Gioco  g = Gioco(&m, &p, &proiettili, &ent, &bonus);

    hidecursor(); // per rendere il cursore invisibile

    thread print_map_thread(&Gioco::auto_print_map, g);
    thread get_position(&Gioco::keyListener, g);

    print_map_thread.join();
    GameOver((m.getTotalHeight()-29)/2); // TODO: Eliminare le funzioni legate all'obrobrio globale XP_PLAYER e getXP_PLAYER...
}

/* ====== Game Over ======
    - salvataggio nuovo punteggio in classifica
    - navigabilità 
*/
void GameOver(int score){
    clearscreen();
    char key;
    char input[CHAR_VALUE];
    int id;
    bool check = false;
    int socreboard_lenght;
    Classifica LBoard = Classifica("Documents\\leaderboard.txt");
    color(Red, Bright_White);
    char stringa[15];
    strcpy(stringa, "Documents\\gameover.txt");
    printfile(stringa);
    color(Black, White);
    cout << "\nDo u want to save ur game? (y/n)" << endl;

    do{
        do{
            cin>>key;
            if ((int)key == 'y' || (int)key == 'Y') {
                check = true;
                cout << "Insert ur nick: ";
                cin >> input;
                //apro il file e salvo i valori vecchi
                LBoard.get_file();
                LBoard.add_value(score, input);
                LBoard.save_file();
                socreboard_lenght = LBoard.get_scoreboard_lenght();
                cout << "Ur score has been saved"<< endl;
            }
            else if ((int)key == 'n' || (int)key == 'N') {
                check = true;
                cout << "\n\n       >> Okay! Press SPACE to exit the game" << endl;
                do{
                    key=getch();
                    if ((int)key == SPACE) exit(0); //StartScreen(LBoard);
                    
                    else cout << "ERROR: INSERT A CORRECT VALUE" << endl;  
                } while(true);
            }
            else{
                check = false;
                cout << "ERROR: INSERT A CORRECT VALUE" << endl; 
            }

        }while (check==false);
        cout << "\n\nHere is the scoreboard of our BEST player!\n Are you here? :P \n\n";
        printTop(LBoard, socreboard_lenght+1);
        //cout << "           >> press C to view the leaderboard" << endl;
        cout << "\n\n       >> press SPACE to exit the game "<< endl;
        do{
            key=getch();
            if ((int)key == SPACE) exit(0); //StartScreen(LBoard);
            else if ((int)key == 'c' || (int)key == 'C') Leaderboard(LBoard, socreboard_lenght+1); // +1 perchè sennò compare une elem in meno in leaderboard
            else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
        } while(true);
    } while(true);
}

/* ====== Classifica dei punteggi ======
    - lettura file Leaderboard.txt
    - stampa classifica di x posizioni
    - evidenzia eventuale nuovo salvataggio
*/
void Leaderboard(Classifica classifica, int scoreboard_lenght){
    char key; //valore del tasto premuto dall'utente
    clearscreen();
    cout << "GG Sei nella classifica :D\n" << endl;
   // classifica.get_file();
    // print classifica con get_position
    printTop(classifica, scoreboard_lenght);

    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) StartScreen(classifica);
        else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
    } while(true);
}

// stampa classifica di x posizioni
void printTop(Classifica lista, int scoreboard_lenght){ // TODO: fare in modo che la classifica si possa visualizzare anche se le persone sono meno di 5
    string aster = "*";
    for (int i = 0; i <= scoreboard_lenght-2; i++){ 
        if (i%2==0) color(Black, Purple);
        else color(Black, Red);
        lista.get_position(i);
        string tab = "\t";
        /* vedi con gli asterischi: 1*  Nome    Punteggio | 2**   Nome    Punteggio ...
        if (strlen(lista.head->nick)<=8) tab ="\t\t";
        if (aster == "*****") aster ="*";
        cout<< aster <<(i+1) <<") "<< lista.head->nick << tab << lista.head->score<< setw(5)<<"*"<<endl;
        aster+="*";*/ 
        
        color(Black, Purple);
        cout<<"[";
        color(Black,Bright_White);
        cout<<i+1;
        color(Black, Purple);
        cout<<"]"<<tab;
        color(Black,Light_Yellow);
        cout<<lista.head->nick<<tab;
        color(Black,Light_Aqua);
        cout<<lista.head->score<<endl;
        lista.head=lista.head->next;
    }
 }
 