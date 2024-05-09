#include "utils.h"

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
    char* new_key = strdup(key);

    // Itero per ogni blocco di 64 bit
    for(; *msg != '\0'; msg+=8) {

    }

    free(new_key);
}


void DES_Dec(char* crt, char* key) {

}