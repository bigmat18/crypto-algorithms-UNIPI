#include "Utils.h"

/**
 * Sono protocolli dove, presi due utenti P (provider) e V (verify), l'utente P dimostra a V di sapere una
 * determinata informazione senza comunicare questa informazioni.
 * 
 * Prendendo l'esempio della spiaggia, dove V vuole verificare che P sappia contare quanti granelli
 * ci sono in una spiaggia decisa da lui abbiamo che: prima V sceglie un valore k di iterazioni,
 * la domanda che viene posta a P e se i granelli sono pari b=1 o dispari b=0 ad ogni iterazione:
*/
bool ZeroKnowledge(int k) {
    int b_previus; // = CalculateSead()
    for(int i = 1; i <= k; i++) {
        // 1. V chiede di voltarsi a P per non vedere cosa fa

        // 2. V Prende un numero random fra 0 e 1
        int e = Random(0, 1);
        if(e == 0) {
            // V Rimuove un granello di sabbia
        } else {
            // V non fa nulla
        }

        // 3. V dice a P di ricalcolare il numero di granelli
        int b; // = CalculateSead()
        if((e == 0 && b != b_previus) ||
           (e == 1 && b == b_previus)) {
            // Vuol dire che la risposta di P è coerente con quella precedente
            // si continua ad iterare
            continue;
        } else {
            // Risponsta non corretta, P è un impostore
            return false;
        }
    }
    return true;
}

/**
 * Se le k iterazioni vanno a buon fine V stabilisce che P ha probabilità (1 - (1/2)^k)
 * che sia un impotore (o meno asseconda della risposta data)
*/

// Flat-Shamir
void FlatShamir_Setup(int p, int q) {
    assert(IsPrime(p));
    assert(IsPrime(q));

    int n = p * q;
    int s = Random(0, n - 1); // s < n
    int t = (int)pow(s, 2) % n; // s^2 mod n

    // <t, n> chiave pubblica
    // <p, q, s> chiave privata
}

// k = numero iterazioni scelta da V
bool FlatShamir(int k, int n, int t, int s) {
    for(int i = 0; i < k; i++) {
        // 1. P
            int r = Random(0, n-1); // r < n
            int u = (int)pow(r, 2) % n;
            // invia u a V
        
        // 2. V
            int e = Random(0, 1);
            // invia e a P

        // 3. P
            int z = r * (int)pow(s, e) % n;
            // invia z a V

        // 4. V
            int x = (int)pow(z, 2) % n;
            if(x == (u * (int)pow(t, e) % n)) 
                // Si passa all'iterazione dopo
                continue;
            else
                // Si stoppa senza identificare P
                return false;

        /**
         * Abbiamo che: (Completezza)
         * e = 0 
         * ==> z = r
         * ==> x = r^2      (t^0 == 1)
         * ==> r^2 == r^2   (t^0 == 1 e u == r^2)
         * 
         * e = 1
         * ==> z = r * s
         * ==> x = r^2 * s^2
         * ==> r^2 * s*2 == r^2 * s^2    (t = s^2)
        */
    }
    return true;
}

/**
 * Correttezza:
 * Se P fosse disonesto potrebbe prendere il valore di e 
 * ed al passo 1 generare
 * u = r^2      con e = 0
 * u = r^2 / t  con e = 1
 * 
 * Ovviamente questo è possibile solo se le previsioni di P su e sono sempre
 * corrette, ma questa cosa non è vera visto che per la randomicita di e le previsioni
 * di e saranno corrette solo 1/2
*/