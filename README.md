# A-Jump


### Guidelines
- guadagni punti ogni volta che sali in alto (piu in alto del tuo massimo precedente)
- nemici sparano solo in basso
- se un nemico ti tocca muori
- se il nemico scende sotto il tuo livello muore
- tu spari solo in alto
- puoi salire e scendere quanto vuoi (non sotto il livello 0 in cui spawni)
- hai una vita
- i nemici possono andare giu, destra, sinistra e in diagonale
- tipi di nemici:
  - soldato semplice   (poca vita poco danno)
  - artigliere         (tanto danno poca vita)   
  - tank               (tanta vita poco danno)     
  - BOSS               (tanto danno e tanta vita)   
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


## Formato codice

- Ogni classe ha il suo file unico e il suo header
- Le classsi non hanno trattini bassi nei nomi
- Le classi iniziano con una maiuscola
- i cicli li scriviamo in questo formato:
```c++ 
  if(conditions){
    // do stuff...
  }else{
    // do stuff...
  }

  while(conditions){
    // do stuff...
  }

  for(i = 0; i<n; i++){
    // do stuff...
  }

  switch(i){
    case 1:
      // do stuff...
      break;
    case 2:
      // do stuff...
      break;
    default:
      // do stuff...
  }

```
- i nomi delle variabili tutti minuscoli con **trattini bassi.**
- **Ogni** funzione deve avere un commento di spiegazione in questo formato:
```c++
/*  Author:       ...
    Parameters:   ...
    Return value: ...
    Comments:     ...
*/
```

 - Il commento va messo sia nell'header che nel file cpp
 - I nomi delle variabili **in inglese**
 - Tutte le funzioni ausiliarie non legate alla classe vanno nel main o nel file `ExternalFunctions.cpp`
 - I nomi delle funzioni tutti in minuscolo con trattini bassi

