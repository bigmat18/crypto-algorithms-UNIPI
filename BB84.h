#include "Utils.h"

/**
 * Lo scambio di chiavi avviene tramite fotoni polarizzati
 * -   |    /    \
 * v   h  +45   -45
 * 
 * v e h = base di polarizzazione +
 * +45 e -45 = base di plarizzazione x
*/

/**
 * Bit di fotone invato da A
 * basi     0   0    1   1
 *  di   +  |   |-   -   |-
 *  B    x  /\   /   /\  \
*/

// CANALE QUANTISTICO
// n = lunghezza seq. di bit
void BB84_Quantistic_Channel(int n) {
    int Sa[n];
    int Sb[n];

    for(int i = 0; i < n; i++) {
        // 1. A sceglie una base di codifica per Sa[i]
        //    la base sarà + o - 
        Sa[i] = Random(0, 1);

        // 2. A invia la base a B

        // 3. B sceglie una base a caso per intepretare
        //    il fotono ricevuto e genera Sb[i]
        Sb[i]; // = fotone ricevuto | base generata (+ o -) (guardare tabella)
    }
}


/**
 * In aggiunta in un canale standard si stabilisce una soglia
 * minima di errore chiata QBER, se si verificano più errori
 * di quelli staibiliti da questa soglia vuol dire che o c'è un
 * utente che sta ascoltato o troppo rumore
 * 
 * Inoltre per evitare che, un utente mal intenzionato E vada a modificare
 * solo una piccola quntità di bit durante la comunicazone per non essere
 * interrotto da QBER ma comunque avere delle info che poi può usare in combinazione
 * con i messaggi successivi, andiamo ad aggiungere una funzione hash, in
 * questo modo anche se ha una piccola informazione E non può estenderla con i msg successivi
*/

void BB84_Standard_Channel(int n, int QBER) {
    /**
     * 1. Estraggo Sa' e Sb' corrisonenti alle basi comuni
     * 2. Estraggo da Sa' e Sb' due sottosequenze in posizioni concordate --> Sa'' e Sb''
     * 3. Si scambiano Sa'' e Sb''
    */
   int num_bit_diversi; // = Sa'' - Sb''
   if(num_bit_diversi > QBER) {
        return;
   } else{
        /**
         * 4. Altrimenti calcolo
         *    A = Sa' \ Sa''   e   B = Sb' \ Sb''
         * 
         *    decodificando le seq risultnati con un codice a correzzione
         *    di erore --> ottengo Sc
        */

       // 5. calcolo la chiave
       int k; // = h(Sc)
   }
}
