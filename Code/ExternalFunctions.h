#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H
#include <fstream>
/*  Author:         Alessandro Frau / StackOverflow
    Parameters:     column -> colonna del carattere
                    line -> riga del carattere
    Return value:   Carattere presente nelle cordinate passate
    Comments:       Restituisce il carattere nella console alle cordinate passate
*/
char find_char(int column, int line);

/*  Author:         Alessandro Frau / StackOverflow
    Parameters:     column -> colonna in cui muovere il cursore
                    line -> riga in cui muovere il cursore
    Return value:   void
    Comments:       Muove il cursore della console nelle cordinate passate
*/
void move_cursor(int column, int line);

/*  Author:         Alessandro Frau / StackOverflow
    Parameters:     void
    Return value:   void
    Comments:       Nasconde il cursore dalla console
*/
void hide_cursor(void);

/*  Author:         Alessandro Frau
    Parameters:     pfile -> puntatore a file
    Return value:   Restituisce true se il file e' vuoto, false altrimenti
    Comments:       funzione che controlla se un file e' vuoto oppure no
*/
bool is_file_empty(std::ifstream& pFile);

/*  Author:         Alessandro Frau
    Parameters:     void
    Return value:   void
    Comments:       funzione che pulisce lo schermo della console
*/
void clearscreen(void);

/*  Author:         Alessandro Frau
    Parameters:     background -> colore dello sfondo
                    text -> colore del testo
    Return value:   void
    Comments:       Funzione che cambia il colore della console dal punto attuale in poi dei colori passati
*/
void color(const int background, const int text);

/*  Author:         Alessandro Frau
    Parameters:     filename -> nome del file
    Return value:   void
    Comments:       Funzione che printa nella console l'intero contenuto di un file
*/
void printfile(char filename[]);

#include "ExternalFunctions.cpp"
#endif