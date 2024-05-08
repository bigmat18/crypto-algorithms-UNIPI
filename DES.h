#include "utils.h"

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

    // 64 / 8 = 16 bytes
    unsigned char *result = (unsigned char*)calloc(strlen((char*)msg), sizeof(unsigned char));
    for(int i = 0, j = 0; i<64; i++) {
        result[j] |= (msg[(int)floorf((permutations[i] - 1) / 8)] >> ((permutations[i] - 1) % 8)) & 0x01;
        result[j] <<= 1;

        if(i != 0 && i % 7 == 0) j++;
    }
    strcpy((char*)msg, (char*)result);
    free(result);
}

void T(void *key) {

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
    for(; msg != '\0'; msg+=8) {

    }

    free(new_key);
}


void DES_Dec(char* crt, char* key) {

}