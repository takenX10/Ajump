
#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
class Player{
    private:
        int x;
        int y;
        int health_points;
        Map *ptr_mappa;
    public:
        // TODO: Mettere queste variabili private e implementare i getter e setter
        int damage; //Danno del Player
        int exec_bonus = -1; //Con questo paramentro comunico alla classe Bonus se ed eventualmente quale bonus eseguire nel momento in cui player ci passa sopra; -1 è default.
        bool should_shoot = false;

        /*  Author:         Alex Lorenzato
            Parameters:     mappa, posizione giocatore, punti vita iniziali
            Return value:   none
            Comments:       inizializzazione giocatore
        */
        Player(Map *m = NULL, int x = 0, int y = 1, int health_points = VITA_PLAYER);
        
        /*  Author:         Alex Lorenzato
            Parameters:     direzione definita dal tasto premuto 
            Return value:   true sse il movimento è permesso
            Comments:       controllo se il movimento è permesso
        */
        bool check_movement(int direction);
        
        /*  Author:         Alex Lorenzato (Parte logica), Francesco Apollonio (Parte legata ai bonus)
            Parameters:     direction -> direzione in cui deve avvenire il movimento
            Return value:   restituisce il valore di end_game
            Comments:       Si occupa di muovere il player, cambiargli le cordinate e settare il nuovo carattere nella mappa
        */
        bool move(int direction);
        
        /*  Author:         Alex Lorenzato 
            Parameters:     void
            Return value:   valore della cordinata x del player
            Comments:       restituisce il valore x della cordinata del player
        */
        int getX(void);
        
        /*  Author:         Alex Lorenzato 
            Parameters:     void
            Return value:   valore della cordinata y del player
            Comments:       restituisce il valore y della cordinata del player
        */
        int getY(void);

        /*  Author:         Alex Lorenzato 
            Parameters:     void
            Return value:   valore della vita del player
            Comments:       restituisce il valore della vita del player
        */
        int get_health(void);

        /*  Author:         Alex Lorenzato 
            Parameters:     value -> valore che viene aggiunto alla vita del player (per toglierne passare un valore negativo)
            Return value:   True se il player e' morto, False altrimenti
            Comments:       Cambia la vita del player del valore passato
        */
        bool change_health(int value);
};
#include "Player.cpp"
#endif