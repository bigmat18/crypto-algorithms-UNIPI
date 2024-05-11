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

void Create_RSA_Key(int p, int q, int* key_priv, int* key_pub) {
    assert(IsPrime(p));
    assert(IsPrime(q));

    int n = p * q;
    int phi = (p - 1) * (q - 1); //per legge di eulero
    
    // Questo intero deve essere minore di phi(n) e primo con esso
    int e; // = ...
    assert(e < phi);
    assert(Euclid(e, phi) == 1);

    int d = InverseModule(e, phi); // Calcoliamo e^-1 mod phi con eulicde esteso

    key_pub[0] = e;
    key_pub[1] = n;

    *key_priv = d;
}

int RSA_Enc(int msg, int key_pub) {

}

int RSA_Dec(int ctr, int* key_priv) {

}