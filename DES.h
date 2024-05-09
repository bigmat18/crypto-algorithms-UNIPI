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

unsigned char* SC(unsigned char *key) {

}

void S(unsigned char* msg) {

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

    PI(msg);
    unsigned char *new_key = T(key);
    unsigned char *key_per_step;

    unsigned char *left_msg = (unsigned char *)malloc(sizeof(char) * 4);
    unsigned char *right_msg = (unsigned char *)malloc(sizeof(char) * 4);

    // Itero per ogni fase, nel caso del DES sono 16
    for (int i = 0; i < 16; i++) {
        key_per_step = new_key;
        new_key = SC(key_per_step);

        // utilizzo key_per_step
        CT(key_per_step);

        left_msg[0] = msg[0];
        left_msg[1] = msg[1];
        left_msg[2] = msg[2];
        left_msg[3] = msg[3];

        right_msg[4] = msg[4];
        right_msg[5] = msg[5];
        right_msg[6] = msg[6];
        right_msg[7] = msg[7];

        EP(right_msg);
        Xor(right_msg, key_per_step, 48);
        S(right_msg);
        P(right_msg);
        Xor(right_msg, left_msg, 32);

        msg[0] = msg[4];
        msg[1] = msg[5];
        msg[2] = msg[6];
        msg[3] = msg[6];

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

}