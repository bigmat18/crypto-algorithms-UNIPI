// #include "Generators.h"
// #include "HistoricalCiphers.h"
// #include "DES.h"
// #include "AES.h"
#include "ModularAlgebra.h"
#include "RSA.h"

int main(void) {
    // unsigned long int e = InverseModule(7, 40);
    // printf("%lu\n", e);

    // unsigned long int msg = 97;
    // unsigned long int key_pub[2];
    // unsigned long int key_priv;
    // Create_RSA_Key(5, 11, &key_priv, &key_pub);
    // printf("%lu - %lu - %lu\n", key_pub[0], key_pub[1], key_priv);

    // printf("%lu\n", msg);
    // msg = RSA_Enc(msg, key_pub[0], key_pub[1]);
    // printf("%lu\n", msg);
    // msg = RSA_Dec(msg, key_priv, key_pub[1]);
    // printf("%lu\n", msg);

    int a = InverseModule(11, 12);
    printf("%d", a);
    return 0;
}
