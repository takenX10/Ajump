# A-Jump
### Map
```
------------    | Artigliere:
 A              |    - HP:    100
T     ___       |    - DANNO: 500 
   B            |-------------------
  S   ___       | Tank:
     A          |    - HP: ....             *
    A                              
                        
 ____
       
   _@


^^^^^^^^^^^^
```

### Guidelines
- Guadagni punti ogni volta che sali in alto (piu in alto del tuo massimo precedente)
- nemici sparano solo in basso
- se un nemico ti tocca muori
- se il nemico scende sotto il tuo livello muore
- tu spari solo in alto
- puoi salire e scendere quanto vuoi (non sotto il livello 0 in cui spawni)
- hai una vita
- i nemici possono andare giu, destra, sinistra e in diagonale
- non ci possono essere due nemici nella stessa riga
- tra una piattaforma e l'altra c'e' uno spazio vuoto
- il pg sta sempre nello spazio vuoto tra le piattaforme
- i nemici attraversano le piattaforme e ne sostituiscono il carattere
- ───── (196)
- ┴┴┴┴ (193)
- ╩╩╩╩ (202)
- tipi di nemici:
  - soldato semplice   (poca vita poco danno)
  - artigliere     (tanto danno poca vita)
  - tank         (tanta vita poco danno)
  - BOSS        (tanto danno e tanta vita)
- le stats dei nemici salgono ogni 30 gradini / un livello
- i nemici spawnano per probabilita'
- il boss ha una sua probabilita'
- ci puo essere max un boss nello schermo
- lista powerup:
  - cura
  - aumento danni
  - scudo assoluto
  - nuke
  - multiproiettile (temporizzato) (optional)
- schermata laterale con tutte le statistiche
- schermata di inizio (premi invio per iniziare ecc....)
- classifica
- schermata game over

### Other stuff
> esempio di proiettili che arrivano:

'
'
'@
┴┴─A─
'
┴────

> Come incrementano i punti

0.02
S = 90 - 5 (cap 5)
T = 5 + 2,5
A = 5 + 2,5

### Ruoli:
- uno che si occupa della mappa (input e il printare tutto) (8 e mezzo) @alex
- due che si occupano delle entita' e dove esse devono spawnare, e come esse devono interagire. (9 ++)@Apo @takenX10
- uno che si occupa del game design (aumento di livello, statistiche e percentuali), del main, game over e classifica (8) @ali-benny
- i bonus li implementa quello che ha meno roba da fare (ce ne accorgeremo sul momento)
