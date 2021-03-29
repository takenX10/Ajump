#include<iostream>
#include "Alex_character_editing.hpp"
#include "Alex.cpp"
#include "Alex_constants.hpp"
using namespace std;

/*
compilare con F5
ctrl+shift+P  ->      "C_Cpp.default.includePath": ["C:\\Program Files (x86)\\mingw-w64\\i686-8.1.0-posix-dwarf-rt_v6-rev0\\mingw32\\i686-w64-mingw32\\include"],
externalConsole: true
*/

// io per compilare ho fatto cosi:
// aperto il terminale nella cartella /AJump/Alex/
// g++ Alex_main.cpp Alex_character_editing.cpp -o Alex_main
// poi ho eseguito l'eseguibile Alex_main.exe a mano dalla cartella
// (non c'e' bisogno di compilare i file header)
// Sono riuscito ad eseguire tutto alla fine delle modifiche senza alcun tipo di problema

class Gioco{
    private:
        Mappa mappa_gioco;
        Player p;

    public:
        Gioco(Mappa m, Player p){
            this->mappa_gioco = m;
            this->p = p;
        }
        void printMap(){
            while(true){
                Sleep(REFRESH_RATE);
                this->mappa_gioco.printMap(this->p.getY() + this->mappa_gioco.getHeight() - OFFSET + (OFFSET > this->p.getY() ? OFFSET - this->p.getY() : 0) );
            }
        }
        
        /*  
        INFO: eseguita da un thread, gestisce il movimento del giocatore
            PARAMETRI: mappa e giocatore
            RETURN: void    
        */
        void keyListener(){
            int key;
            while(true) {
                key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
                this->p.move(key);
            }
        }
};



int main(void){

    Mappa  m = Mappa(MAP_HEIGHT, ROW_DIM);
    Player p = Player(STARTING_X, STARTING_Y, &m);
    Gioco  g = Gioco(m, p);
    
    hidecursor();                         // per rendere il cursore invisibile

    thread print_map_thread(&Gioco::printMap, g);
    thread get_position(&Gioco::keyListener, g);

    print_map_thread.join();
    get_position.join();    
    
    system("PAUSE");
}