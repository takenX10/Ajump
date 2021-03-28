/*
@ Author: Alex Lorenzato
*/

/*
compilare con F5
ctrl+shift+P  ->      "C_Cpp.default.includePath": ["C:\\Program Files (x86)\\mingw-w64\\i686-8.1.0-posix-dwarf-rt_v6-rev0\\mingw32\\i686-w64-mingw32\\include"],
externalConsole: true
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
#include "main.cpp"
using namespace std;

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

/***************************************************************** STRUTTURA *******************************************************************/
/***************************************************************** STRUTTURA *******************************************************************/

#define ROW_DIM 40
#define MAP_HEIGHT 30
#define REFRESH_RATE 30     // durata della sleep tra un print e l'altro
#define CHECKPOINT_ROW 50   // frequenza con cui si trova il piano con piattaforma a larghezza ROW_DIM

struct Map
{
    char row[ROW_DIM];
    long int num_row;    // identificatore univoco riga
    Map* prev;
    Map* next;
};
typedef Map* ptr_Map;

struct Position
{
    int x, y; 
};

/******************************************************************* METODI ********************************************************************/
/******************************************************************* METODI ********************************************************************/

//                                                                             [[ funzioni relative al cursore del terminale ]]
/*  INFO: legge caratteri dal terminale
    PARAMETRI: riga e colonna del carattere da leggere
    RETURN: carattere letto    */
char findChar(int column, int line)
{
    char buf[1];
    COORD coord;
    coord.X = column;
    coord.Y = line;
    DWORD num_read;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutputCharacter(hConsole, (LPTSTR) buf, 1, coord, (LPDWORD) &num_read);
    return buf[0];
}

/*  INFO: sposta il cursore del terminale
    PARAMETRI: riga e colonna del carattere da leggere
    RETURN: void    */
void moveCursor(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){
        cout<<"ERROR! (function: movecursor)"<<endl;
    }
}

/*  INFO: nasconde il cursore del terminale (quadratino bianco)
    PARAMETRI: nessuno
    RETURN: void
    ALTRO: va richiamata nel main    */
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


//                                                                             [[ funzioni relative alle singole righe della mappa ]]

/*  INFO: stampa di una riga generica
    PARAMETRI: puntatore alla riga da stampare
    RETURN: void     */
void printRow(ptr_Map param_row, Position *p)
{
    cout << (char) 177 << " ";   // "muro"
    for(int i=0; i<ROW_DIM; i++) 
    { 
        if(param_row->num_row == p->y && i == p->x) // riga in cui è presente il giocatore
        {
            cout << '@';
        }
        else { cout << param_row->row[i]; }
    }
    cout << (char) 177 << " ";  // "muro"
    cout << " " <<param_row->num_row; // id riga
}

/*  INFO: generazione di una riga (aggiunta di un nodo alla lista)
    PARAMETRI: puntatore all'ultima riga generata (ultimo nodo della lista) [per evitare di scorrere tutta la lista ogni volta]
    RETURN: puntatore alla riga generata dalla funzione (nuovo ultimo nodo della lista)    */
ptr_Map newRow(ptr_Map param_row)
{
    ptr_Map new_row = new Map;               // "collego" la nuova riga all'ultima riga generata
    param_row->next = new_row;
    new_row->num_row = param_row->num_row+1;
    new_row->prev = param_row; 
    new_row->next = NULL;
    
    if(new_row->num_row % 2 != 0) // caso riga in cui NON vanno inserite piattaforme
    {
        for(int i=0; i<ROW_DIM-1; i++) { new_row->row[i] = ' '; }
    }
    else{
        if(new_row->num_row % CHECKPOINT_ROW == 0){
            for(int i=0; i<ROW_DIM; i++) {     // piano "checkpoint" con piattaforma a larghezza max
                new_row->row[i] = (char) 196;
            }
        }
        else
        {
            int dim_1 = rand() % (ROW_DIM/4) +1; // dimensioni piattaforme
            int dim_2 = rand() % (ROW_DIM/4) +2;
            int dim_3 = rand() % (ROW_DIM/4) +2;
            int space_1 = rand() % 6 +1;         // spazi tra le piattaforme
            int space_2 = rand() % 3 +1;
            int space_3 = rand() % 2 +1;
            int i=0;
            // riempimento riga
            for(i=0; i<space_1; i++){ new_row->row[i] = ' '; }
            for(i=i; i<space_1 + dim_1; i++){ new_row->row[i] = (char) 196; }
            for(i=i; i<space_1 + dim_1 + space_2; i++){ new_row->row[i] = ' '; }
            for(i=i; i<space_1 + dim_1 + space_2 + dim_2; i++){ new_row->row[i] = (char) 196; }
            for(i=i; i<space_1 + dim_1 + space_2 + dim_2 + space_3; i++){ new_row->row[i] = ' '; }
            for(i=i; i<space_1 + dim_1 + space_2 + dim_2 + space_3 + dim_3; i++){ new_row->row[i] = (char) 196; }
            for(i=i; i<ROW_DIM-1; i++){ new_row->row[i] = ' '; }
        }
    }
    new_row->row[ROW_DIM-1] = '\0';

    return new_row;  // ritorna l'ultima riga della mappa
}

/*  INFO: creazione prima riga 
    PARAMETRI: puntatore a una mappa vuota
    RETURN: puntatore alla row numero 0     */
ptr_Map firstRow(ptr_Map first_row)
{   
    first_row->next = NULL; 
    first_row->num_row = 0;

    for(int i=0; i<ROW_DIM-1; i++) 
    { 
        first_row->row[i] = (char) 196; 
    }
    first_row->row[ROW_DIM-1] = '\0';

    return first_row;
}


//                                                                             [[ funzioni relative alla mappa ]]

/*  INFO: inizializzazione mappa: generazione firstRow e MAP_HEIGHT-1 righe aggiuntive; generazione Player
    PARAMETRI: puntatore a una mappa vuota
    RETURN: puntatore alla riga numero 0 (testa della mappa)    */
ptr_Map newMap(ptr_Map map)
{
    ptr_Map tmp = map;  // uso tmp perché map verrà aggiornato e non punterà più alla riga 0
    map = firstRow(map);
    for(int i=0; i<MAP_HEIGHT; i++){ map = newRow(map); }
    return tmp;
}

/*  INFO: stampa di una "schermata", ovvero di MAP_HEIGHT piani (versione che utilizza cursore del terminale)
    PARAMETRI: puntatore alla testa della mappa (row numero 0), posizione giocatore
    RETURN: void    */
void printMapCursor(ptr_Map map_head, Position *p)
{
    ptr_Map map;
    while(true)
    {
        Sleep(REFRESH_RATE);
        map = map_head;
        int tmp_player_y = p->y;
        
        if(p->y < 6) // gestione icona giocatore, dev'essere in una pos. relativa al bottom = 5
        { 
            tmp_player_y = 5;
        } 
        while(map->num_row != (MAP_HEIGHT + tmp_player_y - 6) ) // punto alla riga indexTop
        { 
            map = map->next; 
        }

        for(int i=0; i<MAP_HEIGHT; i++) 
        {
            for(int j=0; j<ROW_DIM; j++)
            {
                if(p->y == map->num_row && p->x == j)
                {
                    moveCursor(j,i);
                    cout << "@";
                }
                else
                {
                    if(findChar(j,i) != map->row[j])
                    {
                        moveCursor(j,i);
                        cout << map->row[j];
                    }
                }
            }
            cout << (char) 177 << " " << map->num_row;
            map = map->prev;
        }
    }
}


//                                                                             [[ funzioni relative al movimento del giocatore ]]

/*  INFO: posizionamento iniziale del giocatore 
    PARAMETRI: puntatore al giocatore
    RETURN: void    */
void newPlayer(Position *p)
{
    p->y = 1;
    p->x = 5;
}

/*  INFO: verifica che sia possibile il movimento verticale
    PARAMETRI: tasto premuto, puntatore al giocatore, mappa
    RETURN: true se il movimento è permesso    */
bool checkPlatformProximity(int key_pressed, Position *p, ptr_Map map)
{
    bool flag = false;
    // movimento SU
    if(key_pressed == 72)     // il caso di row = 0 ha bisogno di una distinzione speciale in quanto la distanza
    {                         // giocatore-piattaforma è = 1 invece che = 2 come nel resto della mappa
        while(map->num_row != p->y +1){ map = map->next; }     // punto a 2 righe sopra al giocatore, dov'è lo strato successivo di piattaforme
        // <!>
        if(map->row[p->x] == (char) 196) { flag = true; }      // se c'è una piattaforma allora ho l'ok per il movimento
    }
    // movimento GIU
    if(key_pressed == 80)     
    {
        if(p->y != 1)
        {
            while(map->num_row != p->y -3){ map = map->next; }     // punto a 2 righe sotto al giocatore, dov'è lo strato successivo di piattaforme
            // <!>
            if(map->row[p->x] == (char) 196 || map->num_row == 1) { flag = true; }       // se c'è una piattaforma (oppure il row 1) allora ho l'ok per il movimento
        }
    }
    return flag;
}

/*  INFO: controlla se mi trovo in una situazione in cui il movimento non è permesso
    PARAMETRI: tasto premuto, mappa e posizione giocatore
    RETURN: ritorna il tasto premuto se il movimento è permesso, altrimenti un valore non significativo che non porterà ad alcuna azione     
    ALTRO: // su -> 72, giu -> 80, dx -> 77, sx -> 75    */
int checkMovementPossibility(int key_pressed, Position *p, ptr_Map map)
{
    // non andare oltre ai bordi dx e sx della mappa
    if( (p->x == ROW_DIM-2 && key_pressed == 77) || (p->x == 0 && key_pressed == 75) ) 
    { 
        key_pressed = 40;               // 40 valore casuale per cui la pressione del tasto non produce alcun risultato
    }
    // spostamento orizzontale negato se sono a un'estremità DESTRA di una piattaforma
    else if(key_pressed == 77)
    {
        if(p->y != 0)  // faccio il controllo solo se sono a un row != 0 perchése sono al piano terra il movimento è permesso
        {  
            while(map->num_row != p->y -1)   // mi posiziono alla riga sottostante al giocatore, dove ci sono le piattaforme su cui "cammina"
            {
                map = map->next;
            }
            // <!>
            if(map->row[p->x +1] != (char) 196)
            {
                key_pressed = 40;
            }
        }
    }
    // spostamento orizzontale negato se sono a un'estremità SINISTRA di una piattaforma
    else if(key_pressed == 75)
    {
        if(p->y != 0)  // controllo solo se sono a un row != 0 perché al piano terra il movimento è permesso
        {  
            while(map->num_row != p->y -1)   // mi posiziono alla riga sottostante al giocatore, dove ci sono le piattaforme su cui "cammina"
            {
                map = map->next;
            }
            // <!>
            if(map->row[p->x -1] != (char) 196)
            {
                key_pressed = 40;
            }
        }
    }
    // controllo sul movimento verticale in direzione GIU'(dev'esserci una piattaforma sotto al giocatore)
    else if( (p->y == 0 && key_pressed == 80) || ( !checkPlatformProximity(key_pressed, p, map) && key_pressed == 80))
    {
        key_pressed = 40;          
    } 
    // controllo sul movimento verticale in direzione SU (dev'esserci una piattaforma sopra al giocatore)
    else if( ( !checkPlatformProximity(key_pressed, p, map) && key_pressed == 72) )
    {
        key_pressed = 40;          
    } 

    return key_pressed;
}

/*  INFO: gestisce le azioni triggerate dai tasti premuti
    PARAMETRI: tasto premuto, mappa e posizione giocatore
    RETURN: void    
    ALTRO: // su -> 72, giu -> 80, dx -> 77, sx -> 75    */
void keyControl(int key_pressed, Position *p, ptr_Map map)
{
    switch(key_pressed = checkMovementPossibility(key_pressed, p, map))
    {
        case(32): // spazio

        break;

        case(72): // su
            p->y += 2;
            while(map->next != NULL) { map = map->next; } 
            if(p->y > map->num_row - MAP_HEIGHT + 4) // se l'icona giocatore supera una certa altezza, viene creata una nuova riga 
            {                                   
                map = newRow(map);
                map = newRow(map);
            }
        break;
        
        case(80): // giu
            p->y -= 2;
        break;
        
        case(77): // dx
            p->x += 1;
        break;

        case(75): // sx
            p->x -= 1;
        break;
    }
}

/*  INFO: eseguita da un thread, gestisce il movimento del giocatore
    PARAMETRI: mappa e giocatore
    RETURN: void    */
void movePlayer(ptr_Map mappa, Position *player)
{
    int key;
    while(true) 
    {
        key = _getch();      // ricevo input da tastiera, modifico posizione giocatore, e stampo mappa con la posiz aggiornata
        keyControl(key, player, mappa);
    }
}


/******************************************************************** MAIN *********************************************************************/
/******************************************************************** MAIN *********************************************************************/

int main()
{
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
    return 0;
}









