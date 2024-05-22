#include "Utils.h"
#include "ModularAlgebra.h"

/**
 * VANTAGGI: dei metodi a chiave pubblica
 *  - Se gli utenti sono n lo spazio di chiavi si restringe da n(n - 1)/2 a 2n
 *  - Inoltre non è richiesto nessuno scambio di chiavi.
 * 
 * SVANTAGGI: dei metodi a chiave pubblica
 *  - Sistema esposto ad attacchi CHOSEN PLAIN-TEXT nel seguente modo:
 *    Un utente può prendere k messaggi m1, m2, ...mk cifrarli con la chiave pubblic
 *    ed ottenere c1, c2, ..., ck. A questo punto siando sul canale di comunicazione 
 *    se trova un crittogramma c' che coincide con uno di quelli in suo possesso il 
 *    il messaggio è automaticamente decifrato se invece c' != c_i ha comunque info utili
 * - Sistemi molto più lenti. Due/tre ordini di grandezza superiore
 */

void Create_RSA_Key(int p, int q, unsigned long int* key_priv, unsigned long int* key_pub) {
    // p e q devono essere primi
    assert(IsPrime(p));
    assert(IsPrime(q));

    /**
     * Inoltre molto importante che siano numeri "molto grandi" (almeno 1024 bit)
     * per resistere agli attacchi brutte force
    */
   
    /**
     * Bisogna anche che (p-1) e (q-1) devono contentere un fattore primo grande
     * (altrienti n si fattorizza velocemente)
    */

    /**
     * Altro vincono importante è non usare p e q troppo vicini
     * tra loro perché n ~ p^2 ~ q^2 quindi anche sqrt(n) sarà vicino di 
     * conseguneza per trovare p e q sappiamo che non bisogna allotanarsi troppo da sqrt(n)
     * 
     * il mcd(p-1, q-1) deve essere piccolo. Per che ciò avvenga (p-1)/2 e (q-1)/2
     * devono essere co-primi.
     */
    assert(Euclid((p - 1) / 2, (q - 1) / 2) == 1);

    unsigned long int n = p * q;
    unsigned long int phi = (p - 1) * (q - 1); //per legge di eulero
    
    // Questo intero deve essere minore di phi(n) e primo con esso
    unsigned long int e = 7; // = ...
    assert(e < phi);
    assert(Euclid(phi, e) == 1);

    /**
     * Se un assert in uno di questi for loop fallisce la cifratura non induce 
     * alcuna trasfromazione del messaggio in chiaro m^e mod n = m
    */
    for(unsigned long int k = 0; k < p - 1; k++) {
        if((p-1) % k == 0)
            assert((unsigned int)((phi + k) / k) != e);
    }
    for(unsigned long int k = 0; k < q - 1; k++) {
        if((q-1) % k == 0)
            assert((unsigned int)((phi + k) / k) != e);
    } 

    /**
     * ATTACCHI CON ESPONENTI BASSI
     * Immaginiamo che e utinti abbiano scelto lo stesso valore di e, se viene
     * ricevuto lo stesso messaggio m abbiamo che:
     *  c1 = m^e mod n1
     *  c2 = m^e mod n2
     *  ...
     *  ce = m^e mod ne
     * 
     * Sia m < ni per ogni 1 <= i <= e e siano n1, n2, ..., ne primi tra loro
     * Per il teorema cinese del resto esiste un unico m' < n con n = n1 * n2 * ... * ne
     * che soddisfa l'equazione
     *      m' \equiv m^e mod n
     * dato che m^e < n la congrunza si può riscrivere con m' = m^e, una volta calcolato m'
     * si può ricavare m mediante l'estrazione della radice e-esima che si esegue facilmente 
     * visto che non interviene l'operazione in modulo.
    */

    /**
     * Questo valore è importante che venga scelto sufficentemnte grande, 
     * in caso contrario si potrebbe verificare ogni possibile valore di d 
     * finchè la decifrazione non da un messaggio significativo. 
    */

    unsigned long int d = InverseModule(e, phi); // Calcoliamo e^-1 mod phi con eulicde esteso

    key_pub[0] = e;
    key_pub[1] = n;

    *key_priv = d;
}

/**
 * La crittografia funziona perché, dato un crittogramma c per ricavare m senza conoscere
 * la chiave privare bisognerebbere risolvere: m = sqrt(c, e) mod n. Che sappiamo essere 
 * un problema computazionalmente difficile
 * 
 * Inoltre il calcolo di phi(n) (che potrebbe essere utilizzato per risolvere senza conoscere p, q)
 * è ugualemnte difficile alla fattorizazione
*/
unsigned long int RSA_Enc(unsigned long int msg, unsigned long int e, unsigned long int n) {
    return (unsigned long int)pow(msg, e) % n;
}

unsigned long int RSA_Dec(unsigned long int crt, unsigned long int d, unsigned long int n) {
    return (unsigned long int)pow(crt, d) % n;
}

/**
 * DIMOSTRAZIONE: (sicurezza)
 *  Per prima cosa vediamo che se mcd(e, phi(n)) = 1 ==> x^e mod n sia permutazione di Z_n
 *  cio garantisce l'invertibltià del processo poichè per m1 != m2 <==> C(m1, k[pub]) != C(m2, k[pub])
 * 
 * DIMOSTRAZIONE: (correttezza)
 *  Dimostriamo che D(C(m, k[pub]), k[priv]) = m, ovvero (m^e mod n)^d mod n = m.
 *  Per proprietài calcolo possiamo riscrivere come m^{ed} mod n = m
 *      1. p e q non dividono n
 *         => m e n sono co-primo (Mcd(m, n) = 1)
 *         a) per teorema di ulero n^{phi(n)} === 1 mod n
 *         b) ed === 1 mod phi(n) [dalla def di inverso]
 *            ed = 1 + r*phi(n)
 *            ...
 *      2. p o q dividono n
 *         ...
*/