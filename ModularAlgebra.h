#include "utils.h"

/**
 * Algoritmo per calcolare Z* di n, cioè
 * tutti i numeri positivi < di n tali per cui il numero i
 * sia primo con n (mcd(n, a) == 1)
*/
int* Z_sharp(int n, int size) {
    bool result[size];
    int count = 0; 

    /**
     * Tempo di esecuzione pari alla dimensioni di n
     * è esponenziale sul numero di bit (exp sulla dimnesione) che lo rappresentano
     * essendo che bisogna eseguire Euclid(n, i) per ogni i < n
    */
    for(int i = 0; i < size; i++) {
        if(Euclid(n, i) == 1) {
            result[i] == true;
            count++;
        } else {
            result[i] == false;
        }
    }

    int* numbers = (int*)malloc(sizeof(int) * count);
    for(int i = 0, j = 0; i < size; i++) {
        if(result[i]) {
            numbers[j] = i;
            j++;
        }
    }

    return numbers;
}

/**
 * Questa funzione corrisponde a |Z*| di n e si indica con phi(n)
*/
int EuleroFunction(int n, int size) {
    int* Z = Z_sharp(n, size);
    int counter = 0;

    // Calcolo carindatià di Z
    for(; *Z != '\0'; Z++)
        counter++;

    free(Z);
    return counter;
}
/**
 * TEOREMA:
 *  Sappiamo anche che phi(n) = (p-1)(q-1) se n è il prodotto di due numeri primi p, q.
 * 
 * TEOREMA: (di eulero)
 *  Sappiamo che per ogni n > 1 e per ogni intero primo con n si ha:
 *      a^{phi(n)} equiv 1 mod n
 * 
 *  Che equivale a dire per n primo:
 *      a^{n-1} equiv 1 mod n
 * 
 * DEFINIZIONE: a^{-1} mod n = a^{phi(n) - 1} mod n
 * 
 * Da qui vediamo come l'operazione per calcoalre l'inverso di un numero primo in modulo
 * richiede o di fattorizzare il numero (esprimere phi(n) = (p-1)(q-1)) o di calcoalre Z* che 
 * è comunque esponenziale sulla dimensione di n.
 * 
 * TEOREMA:
 *  L'equazione ax \eqiv b mod n ammette soluzione <==> mcd(a, n) divide b (b mod mcd(a,n) == 0).
 *  In questo caso si hanno esattamente mcd(a, n) soluzioni distinte.
 * 
 * Diventa ultra ganzo se mcd(a, n) = 1, visto che sicuramente divide b e ha solo una soluzione.
 * mcd(a, n) = 1 <==> a e n sono primi fra loro <==> a^-1 esiste 
 */


/**
 * Altro metodo per calclare l'inversa in modulo di un numero. 
 * Esso si basa su risolvere ax + bt = mcd(a, b)
*/
typedef struct {
    int d; // Equivale a mcd(a, b)
    int x; // x = a^{-1} mod b (usato per risolvere inverso in modulo)
    int y;
} euclid_t;

/**
 * L'algoritmo ha complessità logaritmica nel cavore di a e b, quindi polinomiale 
 * nella dimnesione dell'input.
*/
euclid_t Extended_Euclid(int a, int b) {
    if(b == 0) 
        return (euclid_t){a, 1, 0};
    else {
        euclid_t result = Extended_Euclid(b, a % b);
        return (euclid_t){result.d, result.y, result.x - floorf(a/b) * result.y};
    }
}
/**
 * Tramite il risulato si può risolvere l'equazione ax + by = mcd(a,b)
 * Visto che abbiamo tutti i paramentri (d = mcd(a, b), a e b si hanno in input, e poi abbiamo x e y)
*/

/**
 * Da qui possiamo risolvere l'inverso di un numero primo in modulo n andando ad
 * eseguire Extended_Euclid(a, n) e ritornando x visto che x = a^{-1} mod b
 * ax + ny = 1
 */
int InverseModule(int a, int n) {
    euclid_t result = Extended_Euclid(a, n);
    return result.x;
}


/**
 * DEFINIZIONE:
 *  Definiamo un generator un numero a \in Z* di n tale che 
 *      a^k mod n   per ogni 1 <= k <= phi(n)
 * genera tutti e soli gli elementi di Z* di n 
*/
bool IsGenerator(int a, int n) {
    // Andiamo a costriuire Z* di n ma per ottimizzare
    // le operazione lasciamo l'array che indica se il numero in pos i
    // appartiene o meno a Z*
    bool result[n];
    int count = 0;

    for(int i = 0; i < n; i++) {
        if(Euclid(n, i) == 1) {
            result[i] == true;
            count++;
        } else {
            result[i] == false;
        }
    }

    // Qui iteriamo per 1<= k <= phi(n) e vediamo se quel numero
    // è in Z*, in caso contrario vuol dire che viene generator un numero non in Z*
    // quindi si ritorna false

    // generated serve a tenere traccia di tutti i numeri trovati in result.
    int generated = 0;
    for(int k = 1; k <= count; k++) {
        if(!result[(int)pow(a, k) % n])
            return false;
        generated++;
    }

    // Si controlla se sono stati generati tutti i valori, confrontando con count
    return generated == count;
} 
/**
 * Per il teorema di eulero se a^{phi(n) - 1} mod n = 1 ==> 1 \in Z* di n è generatore per k = phi(n)
 * 
 * TEOREMA:
 *  Se il valore n è un numero primo Z* di n ha almeno un generatore
 * 
 * Inoltre sappaimo che per n primo si può dimostrare che il numero dei suoi generatori è phi(n-1)
*/