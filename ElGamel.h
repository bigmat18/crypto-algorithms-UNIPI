#include "Utils.h"
#include "ModularAlgebra.h"

void ElGamal_Key(int* p, int* g, int* y, int* x) {
    assert(IsGenerator(*g, *p));

    *x = Random(2, *p - 2);
    *y = (int)pow(*g, *x) % *p;

    /**
     * Key[pub] = <g, y>
     * Key[priv] = <x>
    */
}

/**
 * Questo algoritmo si bassa sulla difficoltà di calcolare il logaritmo discreto
 * che rende la chiave privata x sicura, anche se y e g sono pubblici
*/
int* ElGamal_Enc(int* msg, int p, int g, int y) {
    // in caso contrario possiamo dividere msg usando una cifratura a blocchi
    assert(*msg < p);

    // r è casuale ==> d è causale e non forinisce info su m
    // per estrarre r occorre risolvere problema log discreto
    int r = Random(2, p-2);
    int c = (int)pow(g, r) % p;
    int d = (*msg * (int)pow(y, r)) % p;

    int* crt = (int*)malloc(2 * sizeof(int));
    crt[0] = c;
    crt[1] = d;

    return crt;
}

int ElGamel_Dec(int* crt, int x, int p) {
    return crt[1] * (int)pow(crt[0], -x) % p;
    /**
     * Questo perché:
     *  d * c^{-x} % p = m * y^r * c^{-x} mod p 
     *                 = m * y^r * (g^r)^{-x} mod p
     *                 = m * (g^x)^r * g^{-rx} mod p
     *                 = m mod p = m    (con m < p)
    */
}