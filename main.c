#include "Generators.h"
#include "HistoricalCiphers.h"
#include "DES.h"
#include "AES.h"

int main(void) {
    // int n = 10;
    // int seme = 0;
    // int *result = linear_generator(211, 10, 3, seme, n);
    // for(int i = 0; i < n; i++) {
    //     fprintf(stderr, "%d\n", result[i]);
    // }
    // char *msg = strdup("ildelfino");
    // char *key = strdup("abraabraa");

    // printf("%s", str);
    // GeneralCesare(str, 3);
    // printf("%s", str);

    // printf("%s\n", msg);
    // Vigenere(msg, key);
    // printf("%s", msg);

    // int trasp[] = {0, 1, 3, 2};
    // char* msg = strdup("abcdefgh");

    // printf("%s\n", msg);
    // Trasposition(msg, trasp, 4);
    // printf("%s", msg);

    // unsigned char *msg = (unsigned char*)strdup("abcdefgh");
    // int size = strlen((char*)msg);

    // for (int i = 0; i < size; i++)
    //     printf("%d ", msg[i]);
    // printf("\n");

    // PI(msg);

    // for (int i = 0; i < size; i++)
    //     printf("%d ", msg[i]);
    // printf("\n");

    // PF(msg);

    // for (int i = 0; i < size; i++)
    //     printf("%d ", msg[i]);
    // printf("\n");

    unsigned char* key = (unsigned char*)strdup("\xF1\xFF\xFF\xFF\xFF\xFF\xFF\x00");
    for (int i = 0; i < 8; i++)
        printf("%d ", key[i]);
    printf("\n");
    key = T(key);
    for(int i = 0; i < 7; i++)
        printf("%d ", key[i]);

    return 0;
}
