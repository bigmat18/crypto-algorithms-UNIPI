#include "Utils.h"

/**
 * INVERTIRE FATTORIZZAZIONE:
 *  Calcolare il prodotto n fra due interi p e q è facile, scoprire i due interi
 *  (univocamente possibile solo se p e q sono primi) è esponenziale
*/
int* Fattorization(int n) {
    // Problema NP arduo
}

/**
 * RADICE IN MODULO:
 *  Abbiamo visto che per calcoalre la potenza y = x^z mod s con x, z, s interi
 *  è polinomiale andando a procedere nel seguente modo:
 *  z = 2^w1 + 2^w2 + ... + 2^wt cioò si utilizza la rappresentazione in binario.
 *  Da qui si scrive y^{2^j} per j = 1, 2, ..., w ottenendo ciascuna di esse come quadrato
 *  delle precedenti.
 * 
 * Esempio:
 *  z = 45 = 1 + 4 + 8 + 32
 *  y^2 = y * y, y^4 = y^2 * y^2, .... y^32 = y^16 + y^16
 *  ed infine si calcola y^45 = y * y^4 * y^8 * y^32 e si fa il modulo
*/

int PowInModule(int x, int z, int s) {
    // Da fare...
}

/**
 * La difficolà arriva se bisogna invertire la funzione:
 * x = sqrt(y, z) mod s
 * 
 * Conoscendo però zv \eqiv 1 mod phi(n) e x è primo con s abbiamo che:
 *  y^v mod s = x^{zv} mod s 
 *            = x^{1+k*phi(n)} mod s
 *            = x mod s
 * Quindi polinomiale 
*/

/**
 * CALCOLO LOGARITMO DISCRETO:
 *  Possimao calcolare anche y = x^z mod s rispetto a z. Il problema 
 *  operando il modulo è computazionalmente difficile.
 *  
 *  Se s è primo esiste una soluzione per ogni y <==> x è un generatore di Z* di s
 */