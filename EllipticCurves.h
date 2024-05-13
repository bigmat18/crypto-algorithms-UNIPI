#include "Utils.h"

/**
 * DEF:
 * Una CURVA ELLETTICA si campo K è definita come
 * E = {(x, y) \in K^2  |  y^2 + axy + by = x^3 + cx^2 + dx + e}
 * dove a, b, c, d, e \in K
 *
 * DEF:
 * La caratteristica di un campo è definita come il numero k più
 * piccolo tale che sommando k volte l'elemento neutro moliplicativo (il numero 1)
 * si ottiene l'elemento neutro additivo (indicato con 0)
 *
 * Se la caratteristica del campo è diversa da 2 e da 3, l'equazione si riscrive come:
 *  y^2 = x^3 + ax + b      con a, b \in K
 *
 * DEF:
 * Si definisce una curva ellettica su reali come:
 * E(a, b) = {(x, y) \in R^2  |  y^2 = x^3 + ax + b}
 *
 * Inoltre deve essere verificato che: 4a^3 + 27b^2 != 0
 * In caso contrario potrebbero esserc cuspidi o nodi dove non
 * sarebbe definita una tangete univoca
 *
 * Ongi punto P = (x, y) si riflette su un punto -P = (x, -y)
 *
 * PROPRIETA:
 * Ogni retta intereca una curva ellittica in al pù tre punti
 *
 * DEF:
 * Quindi se prendiamo una retta tangente interseta la curva in tre puinti
 * e possiamo dire che:
 *      P + Q + R = 0
 * questa operazione si chiamma somma di punti
 *
 * 1. P != +-Q ==> S = P + Q
 *      xs = lam^2 - xp - xq
 *      ys = -yp + lam(xp - xs)
 *      lam = (yq - yp)/(xq - xp)
 *
 * 2. Q = P ==> S = P + Q = 2P
 *      xs = lam^2 - xp - xq
 *      ys = -yp + lam(xp - xs)
 *      lam = (3xp^2 + a)/2yp
 *
 *      se yp = p ==> S = 2P = 0
 *
 * 3. Q = -P ==> S = P + Q = P + (-P) = 0
*/

/**
 * DEF:
 * Definiamo le curve ellitiche su campi finiti come:
 * Ep(a,b) = {(x, y) \in Z^2_p  |  y^2 mod p = x^3 + ax + b mod p} U {0}
 * con a,b  in Zp e p>3
 *
 * Questa tipologia di curve ellittiche crea una nuvola di punti
 * La curva prima Ep(a,b) risoluta simmentrica alla reta y = p/2
 *
 * DEF:
 * Inverso di P e uguale a (x, -y mod p) = (x, p - y)
 *
 * Se 4a^3 + 27b^2 != 0 abbiamo che la cura forma un gruppo abelliano finito rispetto
 * all'operazione addizione
 *
 *
 * DEF:
 * L'ordine di una curva ellittica è al più di 2p + 1 punti, il punto 
 * all’infinito e le coppie di punti che soddisfano l’equazione vista
 * 
 * TEOREMA: (Hasse)
 * L'ordine N di una vurca ellittica Ep(a, b) verifica la disuguaglianza 
 * |N- (p+1)| <= 2sqrt(p)
 * 
 * DEF:
 * Curve ellittiche binarie sono curve le cui variabili assumono valore nel campo GF(2^m)
 */

typedef struct {
    unsigned long int p;
    unsigned long int a;
    unsigned long int b;
    unsigned long int n; //ordine curva
} eliptic_curve_t;

typedef struct {
    unsigned long int x;
    unsigned long int y;
} point_t;

/**
 * FUNZIONE ONE-WAY
 * y = g^k mod p
 * Q = kP = P + P + ... + P
 * 
 * Usiamo il metodo del raddoppio ripetuto (sempre complessità logaritmica)
 * Si calcola in succession 2P, 4P, ... 2^t P usando le formue viste sopra
 * 
 * In fine si calcola Q = kP come soppa sei 2^i P
 * Esempio:
 * Q = 13 P = (8 + 4 + 1)P ...
 * 
 * 
 * LOGARITMO DISCRETO CURVE ELLITTICHE
 * Dati due punti P e Q trovare, se esiste, il più piccolo intero k tale che Q = kP
 * Se cappa è definito si chiama logaritmo in base P del punto Q
 * 
 * Trovare questo valore risulta computazionalmente difficle
*/

int RepeatedDoubling(int n, point_t point) {
    return; // TODO
}

/**
 * DH con curve ellittiche
 * - Si condivide fra utente A e B una curva ellittica, un punto B di ordine n dove nè
 *   il più piccolo intero positivo t.c. nB = 0
 * - A seleziona nA < n come chiave private e calcola Pa = nA * B e spedisce Pa a B in chiaro
 * - B seleziona nB < n come chiave private e calcola Pb = nb * B e spedisce Pb a A in chiaro
 * - A riceve Pb e calcola k[sessione]  =  nA * Pb  =  nA * nB * B
 * - B riceve Pa e calcola k[sessione]  =  nB * Pa  =  nB * nA * B
 * 
 * A questo punto hanno entrambi la stessa chiave di sessione che viene trasformata in
 * un effettiva chiave convertendolo in intero k = k[session]_x mod 256
 * 
 * Come RSA è vulnerabile a man-in-the-middle se non c'è certificcato
 */

/**
 * ElGamel su curve ellittiche:
 * 
 * Creazione chiavi:
 *  - numero primo p
 *  - curva ellittica prima Ep(a,b)
*/

void ElGamal_Create_Key(int p, int B, eliptic_curve_t curve, int* key_pub, int* key_priv) {
    unsigned long int n = Random(1, curve.n);
    *key_pub = n * B; // Da calcolare con quadrature ripetute
    *key_priv = n;
}

/**
 * Algoritmo di Kobliz
 * Dato m < p trovare Pm in Ep(a, b)
 * 
 * Questo algoritmo serve per trasformare un messsaggio m in un punto
 * di una curva prima o binaria
 * 
 * Si prova ad utilizzare m come ascissa, questa cosa da che la probabilità di trovare
 * un punto della curva è pari alla probabilità che m^3 + am + b (mod p) sia residuo quadratico (quindi circa 1/2)
*/

point_t Kobliz(unsigned long int m, int h, eliptic_curve_t curve) {
    assert((m + 1) * h < curve.p);

    for(int i = 0; i < curve.p; i++) {
        int x = m * h + 1;
        int y = (int)(pow(x, 3) + curve.a * x + curve.b) % curve.p;
        if(y) {
            return (point_t){x, y};
        }
    }

    return; // Fallimento
}

/**
 * CIFRATURA:
*/

/**
 * DECIFRATRUA:
 */

