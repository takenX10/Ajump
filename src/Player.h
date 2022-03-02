
#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
class Player{
    private:
        int x;
        int y;
        int health_points;
        Map *ptr_mappa;
        int damage; //Danno del Player
        int exec_bonus = -1; //Con questo paramentro comunico alla classe Bonus se ed eventualmente quale bonus eseguire nel momento in cui player ci passa sopra; -1 è default.
        bool should_shoot = false; //permette la comunicazione tra la funzione che fa partire lo sparo e quella che decide se sparare.

    public:

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

        /*  Author:         Francesco Apollonio
            Parameters:     void
            Return value:   int value -> il danno causato da proietitli "standard" del player
            Comments:       setta il danno del proiettile del player
        */

        int get_damage_player(void);

        /*  Author:         Francesco Apollonio
            Parameters:     void
            Return value:   int -> valore che indica se, ed eventualmente quale, bonus è necessario eseguire sul player.
            Comments:       -1 è il valore di default (nessun bonus da eseguire)
        */
       
        int get_exec_bonus(void);

        /*  Author:         Francesco Apollonio
            Parameters:     int value -> valore da settare per il parametro "exec_bonus".
            Return value:   void
            Comments:       //
        */

        void set_exec_bonus(int value);

        /*  Author:         Alessandro Frau
            Parameters:     void
            Return value:   bool -> valore del parametro "should_shoot"
            Comments:       il valore "should_shoot" permette la comunicazione tra la funzione che fa partire lo sparo e quella che decide se sparare.
        */

        bool get_should_shoot(void);

        /*  Author:         Alessandro Frau
            Parameters:     bool value -> parametro che verrà assegnato a "should_shoot"
            Return value:   void
            Comments:       il valore "should_shoot" permette la comunicazione tra la funzione che fa partire lo sparo e quella che decide se sparare.
        */

        void set_should_shoot(bool value);
};
#include "Player.cpp"
#endif