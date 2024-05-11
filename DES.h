#include "Utils.h"

void Permutation(unsigned char* msg, int* permutations, unsigned int size) {
    // len(msg) * 8 (lunghezza in bit) == size
    // size multiplo di 8 (n bytes)
    assert(size % 8 == 0);

    unsigned char *result = (unsigned char*)calloc(size / 8, sizeof(unsigned char));

    for(unsigned int i = 0, j = 0; i < size; i++) {
        result[j] >>= 1;
        volatile unsigned char p1 = (int)floorf((permutations[i] - 1) / 8);
        volatile unsigned char p2 = msg[p1];
        volatile unsigned char p3 = (permutations[i] - 1) % 8;
        volatile unsigned char p4 = 7 - p3;
        volatile unsigned char p5 = p2 << p4;
        result[j] |= p5 & 0x80;

        if((i+1) % 8 == 0) j++;
    }

    for (unsigned int i = 0; i < size / 8; i++) {
        msg[i] = result[i];
    }
    free(result);
}

void Xor(unsigned char* dest, unsigned char* src, int size) {
    assert(size % 8 == 0);

    for(int i = 0; i < size / 8; i++) {
        dest[i] ^= src[i];
    }
}

void PI(unsigned char* msg) {
    int permutations[] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };
    Permutation(msg, permutations, 64);
}

void PF(unsigned char* crt) {
    int permutations[] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    };
    Permutation(crt, permutations, 64);
}

void CT(unsigned char* key) {
    int permutations[] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };

    Permutation(key, permutations, 48);
}

void EP(unsigned char* msg) {
    int permutations[] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    };

    Permutation(msg, permutations, 48);
}

unsigned char* SC(unsigned char *key, unsigned int step, unsigned int size) {
    assert(size % 8 == 0);
    unsigned char* new_key = (unsigned char*)calloc(size / 8, sizeof(unsigned char));

    unsigned int half = size / 2;
    volatile unsigned char value;

    for(unsigned int i = 0; i < half; i++) {
        new_key[i / 8] <<= 1;
        unsigned char index = ((i + step) % half) / 8;
        unsigned char bit = ((i + step) % half) % 8;
        
        value = (key[index] >> (7 - bit));

        new_key[i / 8] |= value & 0x01;
        // printf("value: %d, bit: %d --> value: %d, bit: %d\n", index, bit, i / 8, i % 8);
    }
    for(unsigned int i = half; i < size; i++) {
        new_key[i / 8] <<= 1;
        unsigned char index = ((i + step) % size) / 8 >= (half / 8) ? ((i + step) % size) / 8 : (((i + step) % size) / 8) + (half / 8);
        unsigned char bit = ((i + step) % size) / 8 >= (half / 8) ? ((i + step) % size) % 8 : (((i + step) % size) % 8) + (half % 8);

        value = (key[index] >> (7 - bit)) & 0x01;

        new_key[i / 8] |= value;
        // printf("value: %d, bit: %d --> value: %d, bit: %d\n", index, bit, i / 8, i % 8);
    }

    for(unsigned int i = 0; i < size / 8; i++) {
        key[i] = new_key[i];
    }
    
    return new_key;
}

void S(unsigned char* msg) {
    int S[] = {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    };

    unsigned char* result = (unsigned char*)calloc(48 / 8, sizeof(unsigned char));

    int index_msg = 0;
    for(int i = 0; i < 6; i++) {
        unsigned char value = 0;

        for(int i = index_msg; i < index_msg + 6; i++) {
            // Creazione blocco di 6 bit che viene salvato in value
        }
        index_msg += 6;

        // x = bit_1, bit_6  ==> righa
        // y = bit_2, b_2, b_4, b_5 ==> colonna

        // si utilizzano questi bit per accedere a S[x][y]
        // il valore si prende (valore a 4 bit) e si contatena a result per 
        // costrurie il msg
    }

    for(int i = 0; i < 6; i++)
        msg[i] = result[i];

    free(result);
}

void P(unsigned char* msg) {
    int permutations[] = {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
    };

    Permutation(msg, permutations, 32);
}

unsigned char* T(unsigned char *key) {
    unsigned char *new_key = (unsigned char*)calloc(7, sizeof(unsigned char));
    int new_key_index = 0;

    unsigned char app = 0;
    for(int i = 0, j = 0; i < 64; i++) {
        if(i % 8 == 0)
            continue;

        app <<= 1;
        volatile unsigned char p1 = key[i / 8];
        volatile unsigned char p2 = 7 - (i % 8);
        volatile unsigned char p3 = p1 >> p2;
        volatile unsigned char p4 = p3 & 0x01;
        
        app |= p4; 
        j++;

        if(j == 8) {
            j = 0;
            new_key[new_key_index] = app;
            new_key_index++;
            app = 0;
        }
    }

    int permutations[] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 52, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };

    Permutation(new_key, permutations, 56);

    return new_key;
}

void DES_Enc(char* msg, char* key) {
    // Assumiamo che il messaggio possa essere scomposto
    // in blocchi da 64 bit (8 byte) quindi che siano messaggi
    // da con caratteri multipli di 8
    // In caso contrario va aggiunto un padding finale con dei caratteri speciali
    assert(strlen(msg) % 8 == 0);
    assert(strlen(key) % 8 == 0);

    // Creo una chiave di appoggio per far in modo di non modificare la chiave
    // originaria durante le operazioni

    // msg = 64 bit
    PI((unsigned char*)msg);
    // msg = 64 bit

    // key = 64 bit
    unsigned char *new_key = T((unsigned char*)key);
    // new_key = 56 bit (togliamo i bit di parità)

    unsigned char *key_per_step;

    unsigned char *left_msg = (unsigned char *)malloc(sizeof(char) * 5);
    unsigned char *right_msg = (unsigned char *)malloc(sizeof(char) * 5);

    // Itero per ogni fase, nel caso del DES sono 16
    for (int i = 0; i < 16; i++) {
        key_per_step = new_key;

        // key = 56 bit
        if(i == 1 || i == 2 || i == 9 || i == 16)
            new_key = SC(key_per_step, 1, 58);
        else
            new_key = SC(key_per_step, 2, 58);
        // key = 56 bit ma shiftata di n = 1 o 2

        // utilizzo key_per_step
        // key_per_step = 56 bit
        CT(key_per_step);
        // key_per_step = 48 bit (gli vengono eseguita una compressione e trasposizione)

        // divisione in messaggio left e right
        left_msg[0] = msg[0];
        left_msg[1] = msg[1];
        left_msg[2] = msg[2];
        left_msg[3] = msg[3];

        right_msg[4] = msg[4];
        right_msg[5] = msg[5];
        right_msg[6] = msg[6];
        right_msg[7] = msg[7];
        // la divisione fa avere due variabili => left_msg e right_msg = 32 bit

        // right_msg = 32 bit
        EP(right_msg);
        // right_msg = 48 bit


        Xor(right_msg, key_per_step, 48);

        // Eseguo la funzione S-box, funzione non lineare
        // cruciale per il funzionamento dell'algoritmo

        // Essa prende metà msg espando, permutato e messo in xor a 48 bit
        S(right_msg);
        // lo trasforma e restituisce una versione a 32

        // il nuovo messaggio viene permutato nuovamente
        P(right_msg);

        // viene messo a xor con la parte sinista
        Xor(right_msg, left_msg, 32);

        // Viene ricomposto il messagio mettendo la vecchia parte
        // destra del messaggio (quella avuta originariamente) 
        // a sinistra
        msg[0] = msg[4];
        msg[1] = msg[5];
        msg[2] = msg[6];
        msg[3] = msg[6];

        // mentre a destra viene effettivamente rimesso
        // la parte di destra dopo tutte le operazione eseguite
        msg[4] = right_msg[0];
        msg[5] = right_msg[1];
        msg[6] = right_msg[2];
        msg[7] = right_msg[3];

        free(key_per_step);
    }

    free(new_key);
    free(left_msg);
    free(right_msg);
}


void DES_Dec(char* crt, char* key) {
    /**
     * La decifrazione consiste nel ripetere il processo invertendo l'ordine delle chiavi.
     * Quindi prima si utilizza la chiave K[16] (quella ricavata dall'ultima operazione di shit ciclico)
    */
}

/**
 * TIPO DI ATTACCHI
 * - Sfruttare la relazione Cdes(m, k) = c implica Cdes(m', k') = c' dove la ' indica la complementazione bit a bit (AND)
 *   abbiamo che le uniche funzioni che inlfuenzano l'AND sono lo xor e S-bot, la prima ripropone uguale uscita se entrabi vengono 
 *   complementati, quindi  l'ingresso nell'S-box è indientico per entrambi le coppie. In questo modo dimezziamo le possibili chiavi
 *   e passiamo da 2^56 a 2^55
 * 
 * - Attacco CHOSEN-PLAIN-TEXT
 * 
 * - Attacco CRITTOANALISI DIFFERENZIALE
 * 
 * - Attacco CRITTOANALISI LINEARE
*/

/**
 * Si può potenzialre il DES in due modi
 * - 1: andando a utilizzare per ogni fase una chiave diversa (chiavi indipendeti), espandendo lo spazio
 *      di chiavi da 56 bit a 768 bit. Che anche nel caso di crittografia differenziale abbiamo 2^61 possibili chiavi
 *      Ovviamente ha un costo elevato produrre tutte queste seguneze casuali.
 * - 2: Concatenare il des in un 2TDES o 3TDES nel seguente modo:
 *          c = Cdes(Ddes(Cdes(m, k_1), k_2), k_1)
 *          m = Ddes(Cdes(Ddes(m, k_1), k_2), k_1)
 *      Sfruttando la proprietà per cui Cdes(Cdes(m, k1), k2) != Cdes(m, k3)
*/