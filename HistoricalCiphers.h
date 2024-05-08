#include "utils.h"

/**
 * Basic monoalfabetic sostitution ciphers 
 * Every char in string is replaced with the letter in its position + k
*/
void GeneralCesare(char* str, int k) {
    assert(k >= 1 && k <= 25);

    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            // pos(i) = (pos(i) + k) mod 26 
            *str = ((*str - 'a' + k) % 26) + 'a';

        // Alternative for upper case char
        } else if (*str >= 'A' && *str <= 'Z') {
            *str = ((*str - 'A' + k) % 26) + 'A';

        }
        str++;
    }
}

/**
 * Similar to Cesare but with extra value a.
 * 
 * DECIFRATURA
 * pos(x) = (a^{-1} * (pos(y) - b)) mod 26
*/
void MonoAlfabetic(char* str, int a, int b) {
    // Strong condition, if it's false, the ciphers is not one-to-one function
    // for this we have only 12 possibility for a (prime factor for 26 are 2 and 13 ==> we 
    // can choose any odd value between 1 and 25, excluding 13)
    assert(Euclid(a, 26) == 1);
    assert(b >= 0 && b <= 26);

    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            // pos(y) = (a * (pos(x) + b)) mod 26 
            *str = ((a * ((*str) - 'a' + b)) % 26) + 'a';

        // Alternative for upper case char
        } else if (*str >= 'A' && *str <= 'Z') {
            *str = ((a * ((*str) - 'A' + b)) % 26) + 'A';
        }
        str++;
    }
    // Se possibile key are 12 * 26 = 312 (too small value)
    // In alternative k is arbitrary permutation of letter => k = 26!
    // this is call CIFRARIO COMPLETO
}


void Augusto(void) {
    /**
     * Auguto write document in greek, next it put the letter sequence in correspondence with 
     * Illiade, it replace every letter with the number of distance between his letter from illiade letter in alfabet.
     * Ess:
     * Illiade: ade ciao
     * Document: come va
     * Distance: |pos(c) - pos(a)| = 2
     *           |pos(o) - pos(d)| = 11
     *           ...
     */
}

void Alberti(void) {
    /**
     * It's compose by two disk, the external has alfabetic letter + some number (for exemple from 1 to 5)
     * the internal has a sequence of letter in random position (all letters)
     *
     * Exemple:
     *  External: ABCDEFGHILMNOPQRSTUVZ12345
     *  Internal: SDTKBJOHRZCUNYEPXVFWAGQILM
     *
     * We use the numbers to change internal disk
     *
     * Example:
     *  m = NONFIDA2RTIDIEVE
     *  c = UNUJRKSQUYBMBSPS
     *             ^ key became A - Q
     *
     * An alternative is, when we found a number, after n letter, we change internal
     *
     * External: ABCDE F G HI LMNOP QRST UV Z 12345
     * Interal: EQHCW LMV P DNXAOGY IBZRJT SKUF
     * m = ILD2ELPFINO
     * c = PDCSWDOOIRJ
     *        ^ after 2 charater the key change
     */
}

/**
 * It's based on a table (26 x 26):
 * A B C D ....Y Z
 * B C D E ... Z A
 * C D E F ... A B
 * ...
 * Z A B C ... X Y
 * 
 * With in each row the alfabetic left shifted of i-1 position
 * 
 * We take a msg and a key:
 * MSG:  ILDELFINO
 * KEY:  ABRAABRAA
 * 
 * And ecrypt the message with new_pos = Matrix[Msg[i]][Ket[i]]
 * Msg chars are row and Key chars are columns
*/
void Vigenere(char* msg, char* key) {
    char* start_key = key;

    for(; *msg != '\0'; msg++) {
        // We calculate the encrypted letter 
        *msg = (((*msg - 'a') + (*key - 'a')) % 26) + 'a';

        // If the key are shorted than msg we restart from start of the key
        // ==> concatenete the key
        if(*(++key) == '\0')
            key = start_key;
    }
}

/**
 * ESEMPIO:
 * msg: CI VEDIA | MO TARDI
 * k = {1253764}
 * out: CI DVAIE | MO RTIDA
*/
void Trasposition(char *msg, int *key, int size) {
    // Questo assert nell'algoritmo originale non c'è
    // originariamente se il messaggio non era divisibile per size
    // si andava ad aggiungere alla fine dei caratteri jolly
    assert(strlen(msg) % size == 0);

    // Si divide il messagio in blocchi di dimensione sike
    for(; *msg != '\0'; msg += size) {
        char app[size];

        // per ogni blocco si esegue la permutazione
        // seguendo le regole scritte in key
        for(int i = 0; i < size; i++) {
            app[i] = *(msg + key[i]);
        }

        // copiatura dopo la fine delle permutazioni
        for(int i = 0; i < size; i++) {
            *(msg + i) = app[i];
        }
    }
}