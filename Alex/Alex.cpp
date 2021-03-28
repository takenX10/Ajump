/*
@ Author: Alex Lorenzato
*/


#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "Alex_character_editing.hpp"
#include "../Main/main.cpp"
#include "Alex_constants.hpp"

using namespace std;
using namespace constants;
// INFO GENERALI

// le funzioni hanno una notazione del tipo nomeFunzione, i parametri hano una notazione del tipo nome_parametro
// (char) 196  ->  simbolo usato per le piattaforme

// NOTE DA TENERE A MENTE DURANTE LO SVILUPPO

// per salire o scendere di livello nelle piattaforme ho fatto un controllo in cui devo avere (char) 196 perché la condizione di potermi muovere
// sia verificata, perciò se c'è un nemico/bonus/proiettile che sostituisce il carattere potrei non essere in grado di muovermi in quanto la piattaforma
// è "coperta" e non ho (char) 196 ma un altro carattere
// questo problema sarà riscontrato nella funzione checkPlatformProximity e contrassegno con <!> il punto in cui eventualmente andranno fatte modifiche
// probabile che lo stesso problema salterà fuori su checkMovementPossibility, quando controllo se posso muovermi a dx/sx diuna piattaforma
// in quanto il controllo viene fatto con (char) 196 perciò solo se c'è il carattere di una piattaforma mi lascerà muovermi
// ma se ci fosse ad esempio un bonus in mezzo a una piattaforma, non mi lascerebbe prenderlo


struct Map{
    char row[ROW_DIM];
    long int num_row;    // identificatore univoco riga
    Map* prev;
    Map* next;
};
typedef Map* ptr_Map;

struct Position{
    int x, y; 
};

/*
Il programma comunque funziona, ma per una questione di ordine e compatibilita e leggibilita
avrei inanzi tutto fatto una classe Map (scrivo codice a meta, solo per passare il concetto di quello che serve)
class Map{
    private:
        Map mappa;
        ...
    public:
        Map(){
            qua nel costruttore fai una sorta di new_map 
            ...
        }
        void new_line(){
            ...
        }
        void print_map(from_line, to_line){
            ...
        }

};
poi avrei creato una classe player che prende la classe map come parametro
class Player{
    private:
        map mappa;
        ...
    public: 
        Player(map parametro_mappa, ...){
            this.mappa = parametro_mappa;
            ....
        }
        bool can_go(direction){
            ....
        }
        // questa funzione sposta il player nella mappa
        bool move_player(position){
            ....
        }
};
ovviamente servono un paio di funzioni ausiliarie che pero' lasci escluse dalle classi in modo da creare 
delle strutture ordinate e facilmente trasferibili ed utilizzabili in altre parti del codice
*/

/*  
    INFO: stampa di una riga generica
    PARAMETRI: puntatore alla riga da stampare
    RETURN: void     
*/
void printRow(ptr_Map param_row, Position *p){
    cout << MURO << " ";
    for(int i=0; i<ROW_DIM; i++) { 
        if(param_row->num_row == p->y && i == p->x){ // riga in cui è presente il giocatore
            cout << '@';
        }else { 
            cout << param_row->row[i]; 
        }
    }
    cout << MURO << " ";  // "muro"
    cout << " " <<param_row->num_row; // id riga
}

/*  
    INFO: generazione di una riga (aggiunta di un nodo alla lista)
    PARAMETRI: puntatore all'ultima riga generata (ultimo nodo della lista) [per evitare di scorrere tutta la lista ogni volta]
    RETURN: puntatore alla riga generata dalla funzione (nuovo ultimo nodo della lista)    
*/
ptr_Map newRow(ptr_Map param_row){
    ptr_Map new_row = new Map;               // "collego" la nuova riga all'ultima riga generata
    param_row->next = new_row;
    new_row->num_row = param_row->num_row+1;
    new_row->prev = param_row; 
    new_row->next = NULL;
    
    if(new_row->num_row % 2 != 0){ // caso riga in cui NON vanno inserite piattaforme
        for(int i=0; i<ROW_DIM-1; i++) { new_row->row[i] = ' '; }
    }else{
        if(new_row->num_row % CHECKPOINT_ROW == 0){
            for(int i=0; i<ROW_DIM; i++) {     // piano "checkpoint" con piattaforma a larghezza max
                new_row->row[i] = PIATTAFORMA;
            }
        }else{
            /* avrei scelto un approccio piu estendibile, nella forma di
            for(i = 0, i < NUM_PIATTAFORME; i++){
                dim[i] = ...;
                space[i] = ...;
            }
            fai_cose(dim, space);
            */
            int dim_1 = rand() % (ROW_DIM/4) +1; // dimensioni piattaforme
            int dim_2 = rand() % (ROW_DIM/4) +2;
            int dim_3 = rand() % (ROW_DIM/4) +2;
            int space_1 = rand() % 6 +1;         // spazi tra le piattaforme
            int space_2 = rand() % 3 +1;
            int space_3 = rand() % 2 +1;
            int i=0;
            // riempimento riga
            for(i=0; i<space_1; i++){ new_row->row[i] = ' '; }
            for(i=i; i<space_1 + dim_1; i++){ new_row->row[i] = PIATTAFORMA; }
            for(i=i; i<space_1 + dim_1 + space_2; i++){ new_row->row[i] = ' '; }
            for(i=i; i<space_1 + dim_1 + space_2 + dim_2; i++){ new_row->row[i] = PIATTAFORMA; }
            for(i=i; i<space_1 + dim_1 + space_2 + dim_2 + space_3; i++){ new_row->row[i] = ' '; }
            for(i=i; i<space_1 + dim_1 + space_2 + dim_2 + space_3 + dim_3; i++){ new_row->row[i] =PIATTAFORMA; }
            for(i=i; i<ROW_DIM-1; i++){ new_row->row[i] = ' '; }
        }
    }
    new_row->row[ROW_DIM-1] = '\0'; 

    return new_row;  // ritorna l'ultima riga della mappa
}

/*  
    INFO: creazione prima riga 
    PARAMETRI: puntatore a una mappa vuota
    RETURN: puntatore alla row numero 0     
*/
ptr_Map firstRow(ptr_Map first_row){   
    first_row->next = NULL; 
    first_row->num_row = 0;

    for(int i=0; i<ROW_DIM-1; i++) { 
        first_row->row[i] = PIATTAFORMA; 
    }
    first_row->row[ROW_DIM-1] = '\0';
    return first_row;
}

/*  
    INFO: inizializzazione mappa: generazione firstRow e MAP_HEIGHT-1 righe aggiuntive; generazione Player
    PARAMETRI: puntatore a una mappa vuota
    RETURN: puntatore alla riga numero 0 (testa della mappa)   
*/
ptr_Map newMap(ptr_Map map){
    ptr_Map tmp = map;  // uso tmp perché map verrà aggiornato e non punterà più alla riga 0
    map = firstRow(map);
    for(int i=0; i<MAP_HEIGHT; i++){ map = newRow(map); }
    return tmp;
}

/*  
    INFO: stampa di una "schermata", ovvero di MAP_HEIGHT piani (versione che utilizza cursore del terminale)
    PARAMETRI: puntatore alla testa della mappa (row numero 0), posizione giocatore
    RETURN: void    
*/
void printMapCursor(ptr_Map map_head, Position *p){
    ptr_Map map;
    while(true){
        Sleep(REFRESH_RATE);
        map = map_head;
        int tmp_player_y = p->y;
        // questo va messo come costante ma non lo cambio per ora
        // perche' non voglio fare danni ad altre parti del codice
        // non so quanto questo valore influisca sul resto
        if(p->y < 6){// gestione icona giocatore, dev'essere in una pos. relativa al bottom = 5
            tmp_player_y = 5;
        } 
        // stessa cosa detta nel commento precedente vale nella prossima riga con il -6
        while(map->num_row != (MAP_HEIGHT + tmp_player_y - 6) ) {// punto alla riga indexTop 
            map = map->next; 
        }
        for(int i=0; i<MAP_HEIGHT; i++){
            for(int j=0; j<ROW_DIM; j++){
                if(p->y == map->num_row && p->x == j){
                    moveCursor(j,i);
                    cout << "@";
                }else{
                    if(findChar(j,i) != map->row[j]){
                        moveCursor(j,i);
                        cout << map->row[j];
                    }
                }
            }
            // non riesco a capire cosa sia questo carattere
            // comunque va aggiunto alla lista delle costanti
            // non lo faccio personalmente perche' non sapendo cosa sia
            // non saprei neanche che nome dare alla costante
            cout << (char) 177 << " " << map->num_row;
            map = map->prev;
        }
    }
}

/*  
    INFO: posizionamento iniziale del giocatore 
    PARAMETRI: puntatore al giocatore
    RETURN: void    
*/
void newPlayer(Position *p){
    p->y = 1;
    p->x = 5;
}

// le prossime due funzioni potrebbero essere facilmente unite in un
// bool posso_spostarmi(direction) 

/*  
    INFO: verifica che sia possibile il movimento verticale
    PARAMETRI: tasto premuto, puntatore al giocatore, mappa
    RETURN: true se il movimento è permesso    
*/
bool checkPlatformProximity(int key_pressed, Position *p, ptr_Map map){
    bool flag = false;
    // movimento SU
    if(key_pressed == SOPRA){     // il caso di row = 0 ha bisogno di una distinzione speciale in quanto la distanza
                              // giocatore-piattaforma è = 1 invece che = 2 come nel resto della mappa
        while(map->num_row != p->y +1){ map = map->next; }     // punto a 2 righe sopra al giocatore, dov'è lo strato successivo di piattaforme
        // <!> //per cosa e' questo commento? non riesco a capirlo
        if(map->row[p->x] == PIATTAFORMA) { flag = true; }      // se c'è una piattaforma allora ho l'ok per il movimento
    }
    // movimento GIU
    if(key_pressed == SOTTO) {
        if(p->y != 1) {
            while(map->num_row != p->y -3){ map = map->next; }     // punto a 2 righe sotto al giocatore, dov'è lo strato successivo di piattaforme
            // <!>
            if(map->row[p->x] == PIATTAFORMA || map->num_row == 1) { flag = true; }       // se c'è una piattaforma (oppure il row 1) allora ho l'ok per il movimento
        }
    }
    return flag;
}

// forse le due funzioni successive le avrei compattate e scritte in modo diverso
// infatti se noti fai praticamente due volte lo stesso switch case

/*  
    INFO: controlla se mi trovo in una situazione in cui il movimento non è permesso
    PARAMETRI: tasto premuto, mappa e posizione giocatore
    RETURN: ritorna il tasto premuto se il movimento è permesso, altrimenti un valore non significativo che non porterà ad alcuna azione     
    ALTRO: // su -> 72, giu -> 80, dx -> 77, sx -> 75    
*/
int checkMovementPossibility(int key_pressed, Position *p, ptr_Map map){
    // non andare oltre ai bordi dx e sx della mappa
    if( (p->x == ROW_DIM-2 && key_pressed == DESTRA) || (p->x == 0 && key_pressed == SINISTRA) ) { 
        key_pressed = -1;   // e' buona programmazione usare valori negativi per indicare codici di errore
                            // l'idea di mettere un valore random era buona ma -1
                            // e' diciamo piu universalmente riconosciuto
    }                      
    // spostamento orizzontale negato se sono a un'estremità DESTRA di una piattaforma
    else if(key_pressed == DESTRA){
        if(p->y != 0){  // faccio il controllo solo se sono a un row != 0 perchése sono al piano terra il movimento è permesso  
            while(map->num_row != p->y -1){   // mi posiziono alla riga sottostante al giocatore, dove ci sono le piattaforme su cui "cammina"
                map = map->next;
            }
            // <!>
            if(map->row[p->x +1] != PIATTAFORMA){
                key_pressed = -1;
            }
        }
    }else if(key_pressed == SINISTRA){ // spostamento orizzontale negato se sono a un'estremità SINISTRA di una piattaforma
        // forse e' piu sicuro ">" al posto di "!=" ? probably mi sto facendo pippe io sto leggendo codice da un po' sorry xD
        if(p->y != 0){  // controllo solo se sono a un row != 0 perché al piano terra il movimento è permesso
            while(map->num_row != p->y -1){   // mi posiziono alla riga sottostante al giocatore, dove ci sono le piattaforme su cui "cammina"
                map = map->next;
            }
            // <!>
            if(map->row[p->x -1] != PIATTAFORMA){
                key_pressed = -1;
            }
        }
    }
    // controllo sul movimento verticale in direzione GIU'(dev'esserci una piattaforma sotto al giocatore)
    else if( (p->y == 0 && key_pressed == SOTTO) || ( !checkPlatformProximity(key_pressed, p, map) && key_pressed == SOTTO)){
        key_pressed = -1;          
    }else if( ( !checkPlatformProximity(key_pressed, p, map) && key_pressed == SOPRA) ){ 
    // controllo sul movimento verticale in direzione SU (dev'esserci una piattaforma sopra al giocatore)
        key_pressed = -1;          
    } 
    return key_pressed;
}

/*  
    INFO: gestisce le azioni triggerate dai tasti premuti
    PARAMETRI: tasto premuto, mappa e posizione giocatore
    RETURN: void    
    ALTRO: // su -> 72, giu -> 80, dx -> 77, sx -> 75    
*/
void keyControl(int key_pressed, Position *p, ptr_Map map){
    switch(key_pressed = checkMovementPossibility(key_pressed, p, map)){
        // e il codice di errore (che prima era 40 e ora e' -1)? magari era meglio metterci un cout<<"errore"
        case(SPAZIO): // spazio
        break;
        case(SOPRA): // su
            p->y += 2;
            while(map->next != NULL) { map = map->next; } 
            if(p->y > map->num_row - MAP_HEIGHT + 4) // se l'icona giocatore supera una certa altezza, viene creata una nuova riga 
            {                                   
                map = newRow(map);
                map = newRow(map);
            }
        break;
        case(SOTTO): // giu
            p->y -= 2;
        break;
        case(DESTRA): // dx
            p->x += 1;
        break;
        case(SINISTRA): // sx
            p->x -= 1;
        break;
    }
}

/*  INFO: eseguita da un thread, gestisce il movimento del giocatore
    PARAMETRI: mappa e giocatore
    RETURN: void    */
void movePlayer(ptr_Map mappa, Position *player){
    int key;
    while(true) {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        keyControl(key, player, mappa);
    }
}









