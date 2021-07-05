#include "costanti.hpp"
#include "game_printer.h"
#include "Scoreboard.h"
#include "ExternalFunctions.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Bullet.h"
#include "bonus.h"

/*  Author:         Alice Benatti
    Parameters:     lista -> lista contenente gli elementi salvati nella scoreboard.
    Return value:   void
    Comments:       Scorre la lista e stampa gli elementi contenuti in essa.
*/
void print_top(Scoreboard lista){
    cout << "\n\nHere is the scoreboard of our BEST player!\nAre you a part of it?\n\n";
    string aster = "*";
        int i = 0;
        while(lista.head != NULL && i < 9){
        if (i%2==0) color(Black, Purple);
        else color(Black, Red);
        lista.get_position(i);
        string tab = "\t";       
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
        i++;
    }
 }

/*  Author:         Alice Benatti
    Parameters:     score -> punteggio ottenuto dal player che ha appena terminato la partita.
    Return value:   void
    Comments:       La funzione viene chiamata al termine della partita. 
                    Permette di salvare il punteggio nella leaderboard, aggiornarla, e visualizzarla.
                    L'utente può anche scegliere di non salvare il punteggio, uscendo così dal gioco.
*/
void game_over(int score){
    clearscreen();
    char key;
    char input[CHAR_VALUE];
    int id;
    bool check = false;
    int socreboard_lenght;
    Scoreboard LBoard = Scoreboard("Documents\\leaderboard.txt");
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
                cout << "Ur score has been saved"<< endl;
            }
            else if ((int)key == 'n' || (int)key == 'N') {
                check = true;
                cout << "\n\n       >> Okay! Press SPACE to exit the game" << endl;
                do{
                    key=getch();
                    if ((int)key == SPACE) exit(0);
                    
                    else cout << "ERROR: INSERT A CORRECT VALUE" << endl;  
                } while(true);
            }
            else{
                check = false;
                cout << "ERROR: INSERT A CORRECT VALUE" << endl; 
            }

        }while (check==false);
        print_top(LBoard);
        cout << "\n\n       >> press SPACE to exit the game "<< endl;
        do{
            key=getch();
            if ((int)key == SPACE) exit(0);
            else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
        } while(true);
    } while(true);
}

/*  Author:         Alice Benatti
    Parameters:     void 
    Return value:   void
    Comments:       La funzione permette l'avvio del gioco.
*/
void print_map(void){
    clearscreen();
    color(Black, White);
    Map  m = Map(MAP_HEIGHT, ROW_DIM);
    Player p = Player(&m, STARTING_X, STARTING_Y);
    BulletList proiettili = BulletList(&m, &p);
    EnemyList ent = EnemyList(&m, &p, &proiettili);
    Bonus bonus = Bonus(&m, &p, &ent, &proiettili);
    Game  g = Game(&m, &p, &proiettili, &ent, &bonus);

    hide_cursor(); // Rende il cursore invisibile

    thread print_map_thread(&Game::auto_print_map, &g);
    thread get_position(&Game::key_listener, &g);

    print_map_thread.join();
    g.set_end_game(true);
    game_over((m.get_total_height()-29)/2);
}

/*  Author:         Alice Benatti
    Parameters:     classifica -> lista contenente la classifica.
    Return value:   void
    Comments:       Pulisce lo schermo e chiama una funzione che stamperà la classifica.
*/
void leaderboard(Scoreboard classifica){
    char key; //valore del tasto che premerà l'utente
    clearscreen();
    print_top(classifica);
    color(Black, White);
    cout << "\n\n       >> press SPACE to return at home" << endl;
    do{
        key=getch();
        if ((int)key == SPACE) start_screen(classifica);
        else cout << "ERROR: INSERT A CORRECT VALUE" << endl;
    } while(true);
}

/*  Author:         Alice Benatti
    Parameters:     LBoard -> Scoreboard
    Return value:   void
    Comments:       Schermata iniziale del gioco. Permette la visualizzazione della classifica e di iniziare la partita.
*/
void start_screen(Scoreboard LBoard){
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
            print_map();
        } 
        else if (key== 'C' || key=='c') {
            check= true;
            leaderboard(LBoard);
        }
        else if (key==ESC){ check = true; clearscreen(); exit(0); }
        else cout << "\nERROR: INSERT A CORRECT VALUE" << endl;
    }
    while (check==false);
}