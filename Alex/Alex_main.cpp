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

int main(void){
    ptr_Map map = new Map;                // creo puntatore mappa, salvo la testa
    Position *p = new Position;           // creo giocatore e inizializzo la sua posizione
    newPlayer(p);
    map = newMap(map);                    // creo i primi MAP_HEIGHT piani e li stampo
    thread print_map_thread(printMapCursor, map, p);
    thread get_position(movePlayer, map, p);
    hidecursor();                         // per rendere il cursore invisibile
    print_map_thread.join();
    get_position.join();    
    
    system("PAUSE");
}