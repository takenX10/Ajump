# A-Jump, concept di gioco e caratteristiche.

## Introduzione

Come richiesto, si tratta di un platform il cui scorrimento della mappa avviene in maniera verticale, saltando da una piattaforma ad un'altra.

L'avanzamento nella mappa non è banale; è necessario che il giocatore stia attento alla piattaforma sulla quale avanzare: è possibile infatti incappare in 'strade senza uscita'.

Protagonista e nemici possono interagire fra loro in due modi:
- Contatto fisico diretto.
- Sparando: player e nemici possono provare a sbarazzarsi l'uno dell'altro attraverso colpi di arma da fuoco!

Protagonista e nemici sono dotati di health Points.
Questi differiscono per ogni tipo di nemico nonchè per il player.

L'obiettivo del gioco è dunque quello di salire il più possibile nella mappa. 
I nemici ultimi aumentaranno, quantitativamente, man mano che si avanza nel gioco.
Se gli health Points del player scendono a zero la partita termina.
Se il player entra in contatto diretto con uno qualunque dei nemici la partita termina.

Nel gioco sono presenti bonus e malus.

## Entità in movimento

`Player:` il player è controllato dal giocatore attraverso le frecce direzionali.
La barra spaziatrice lo farà sparare verso l'alto.
Rappresentato in gioco dal carattere  '`@`'

`Nemici:` coloro che ostacoleranno l'ascesa del nostro player; possono essere di 4 tipi. 


- **Soldato semplice:** un comune soldato avente vita e danno equilibrati; probabilmente il nemico più semplice da affrontare.
Rappresentato in gioco dal carattere  '`S`'

- **Tank:** come intuibile dal nome è dotato di una quantità di health Points fuori dal comune, difficile da sconfiggere ma meno temibile in quanto in grado di infliggere meno danno.
Rappresentato in gioco dal carattere  '`T`'

- **Artigliere:** un vero e proprio pericolo! Capace di infliggere un danno sproporzionato, l'artigliere è uno dei nemici più minacciosi. E' tuttavia sufficiente un bel respiro e del sangue freddo per sbarazzarsene, colpendolo una volta infatti morirà.
Rappresentato in gioco dal carattere  '`A`'
- **Boss:** senza dubbio il più temibile. Una quantità di health Points uguale a quella del *tank* e dei danni da fuoco paragonabili a quelli dell'*artigliere* fanno di lui il nemico più difficile da affrontare.
Rappresentato in gioco dal carattere  '`B`'



## Entità immobili: i bonus.

Di tanto in tanto spawnaeranno nella mappa dei particolari simboli; passandoci sopra si attiveranno rispettivi bonus o malus. 
Si tratta in totale di 4 simboli:

- **Bonus health points:** Questo bonus incrementa la salute del player.
Rappresentato in gioco dal carattere  '`H`'

- **Malus health points:** Questo malus decrementa sensibilmente la salute del player.
Rappresentato in gioco dal carattere  '`M`'

- **Bonus Bomb:** Questo bonus genera una grande esplosione che va ad eliminare tutti i nemici presenti nella mappa.
Rappresentato in gioco dal carattere  '`O`'

- **Bonus Proiettili speaciali:** Questo bonus assegna al player un numero predefinito di proiettili letali.
Un singolo proiettile è in grado di eliminare anche i nemici con più health points.
Rappresentato in gioco dal carattere  '`P`'



# A-Jump, divisione dei compiti.

Come richiesto, la scrittura del codice è stata suddisivisa dai 4 partecipanti al progetto come segue.

 - `Lorenzato Alex:` Generazione della mappa e creazione di funzioni che ne permettono la gestione.
  Generazione e movimento del player nella mappa.

 - `Frau Alessandro:` Creazione dell'entità nemico.
 Creazione dell'algoritmo che permette il movimento intelligente dei nemici.
 Creazione dell'algoritmo che permette lo spawn ed il movimento dei proiettili.
 Project manager.

 - `Apollonio Francesco:` Creazione delle diverse tipologie di nemici e loro peculiarità.
 Creazione dell'algoritmo che permette l'interazione tra proiettili e player / nemici.
Creazione dell'entità bonus, quindi algoritmo di spawn e gestione delle interazioni con player e nemici.

- `Benatti Alice:` Gestione dell'avvio del gioco, quindi menù iniziale.
Gestione della conclusione della partita, quindi salvataggio dei dati e stampa della classifica.


# Scelte implementative

`Lorenzato Alex`

- `Generazione mappa:` 
  - la prima idea era di usare una matrice, sostituita immediatamente da una lista per risolvere il problema dei limiti della mappa; in particolare una bilista dal momento che si lavora sempre sui piani adiacenti al giocatore quindi ad esempio è molto meno dispendioso scendere di qualche piano, perché non ci sarà bisogno di scorrere la  mappa dal ground floor.
  - Per tenere traccia dei piani e individuarli univocamente è stato associato un numero riga.
  - la dimensione delle piattaforme è stata decisa in modo tale da avere sempre almeno un punto di incontro tra 2 piani adiacenti
  
- `Movimento giocatore:` qui la scelta è stata semplice, la funzione _getch() fa da listener per i tasti, e alla pressione restituisce un intero, quindi lo switch è risultata da subito l'opzione più comoda.   

- `Stampa mappa:` all'inizio la funzione printMap stampava ad ogni "frame" tutti i piani per intero, ma a livello grafico c'erano dei problemi di visualizzazione in quanto scattava; così, grazie a delle funzioni implementate da Alessandro (move_cursor, find_char) è stato possibile leggere i caratteri direttamente da terminale e sostituire solo quelli diversi dal frame precedente (ad esempio, muovendosi in orizzontale, i piani non cambiano è non è necessario stamparli nuovamente), questo ha migliorato notevolmente la godibilità del gioco.
  
- `Note:` l'idea di mettere dei checkpoint sottoforma di piattaforme che coprono interamente il piano è stata sfruttata per ridurre l'eventualità di "punti ciechi".