#include "utils.h"

/**
 * il ONE-TIME-PAD è un cifrario perfetto definito come segue:
 * 
 * Msg: spazio dei messaggi possibili
 * Critto: spazio dei crittogrammi
 * Key: spazio delle chiavi
 * 
 * M: variabile aleatoria che assume valore in Msg (descrive il comportamento del mittente)
 * C: variabile aleatoria che assume valore in Critto (descrive la comunicazione sul canale)
 * 
 * DEFINIZIONE:
 *  Un cifrario è perfetto se per ogni m \in Msg e per ogni c \in Critto vale la realzione
 *  Pr(M = m | C = c) = Pr(M = m)
*/

/**
 * IPOTESI 1: tutti i messaggi hanno la stessa lunghezza
 * IPOTESI 2: tutte le sequenze di n bit sono messaggi possibili
 *
 * THEOREM: s ipotesi 1 e ipotesi 2 sono vere, e la chiave è scelta randomicamente
 *          il one-time-pad è perfetto e impiega un numero minimo di chiavi.
 *
 * DIMOSTRAZIONE:
 *      Pr(M = m | C = c) = Pr(M = m, C = c) / Pr(C = c)
 *
 *      fissato m, chiavi diverse danno origine a crittogrammi diversi
 *      2^n chiavi ==> 2^n crittogrammi diversi
 *
 *      ogni chiave può essere generata con probabilità 1/2^n
 *      ==> P(C = c) = 1/2^n \forall c \in Critto
 *
 *      Pr(M = m | C = c) = Pr(M = m, C = c) / Pr(C = c)
 *                        = Pr(M = m) Pr(C = c) / Pr(C = c)
 *                        = Pr(M = m)
 */
void OneTimePadEnc(int* msg, int* key, int size) {
    for(int i = 0; i < size; i++)
        msg[i] = msg[i] ^ key[i];
}

void OneTimePadDec(int* crt, int* key, int size) {
    for (int i = 0; i < size; i++)
        crt[i] = crt[i] ^ key[i];
}

/**
 * Per evitare che il crittogramma non venga descriptato senza l'uso della chiave
 * è essenziale utilizzare sempre sequenze di bit randomiche nuove, in caso contrario
 * si potrebbe avere una situazione di questo tipo:
 *
 * Dati: m', m'' di lunghezza n e un unica chiave k abbiamo che
 *  c'_i = m'_i xor k_i      c''_i = m''_i xor k_i
 *  ==> k_i = m'_i xor c'_i      k_i = m''_i xor c''_i
 *  ==> m'_i xor c'_i = m''_i xor c''_i
 *  ==> m'_i xor m''_i = c'_i xor c''_i
 */

/**
 * Se andiamo ad abbandonare l'IPOTESI 2 abbiamo che la validità del teorema
 * rimane per quanto riguarda la perfezione del cifrario, ma il numero di chiavi
 * può non essere minimo
 * 
 * Prendiamo:
 *  |MSG| = alpha^n
 *  |KEY| = 2^t
 * 
 * Abbiamo che 2^t >= alpha^n
 *             t >= log_2 alpha^n
 *             t >= n * log_2 alpha 
 * Nell'alfabeto inglese alpha = 1.1
 * ==> t >= 0.12 * n
*/

/**
 * Vogliamo che alpha^n sia molto maggiore di 2^n in modo che, utilizzando chiavi diversi,
 * messaggi diversi possono portare a crittogrammi uguali, in caso si minore questo non potrebbe 
 * essere possibile, o almeno sarebbe poco probabile. Detto questo diciamo che
 * alpha^n * 2^t >> 2^n
 * 
 * 2^t >> 2^n / alpha^n
 * t >> log_2 2^n/alpha^n = n - log_2 alpha^n = n - n * 0.012 = 0.88n
 * 
 * Questa cosa fa si che con la stessa chiave applicata sul crittogrammi in decifrazione possiamo ottenere
 * molteplici messaggi validi, ma non sappiamo quale sia giusto. Questo protegge da attaccho esauriente sulle chiavi
*/