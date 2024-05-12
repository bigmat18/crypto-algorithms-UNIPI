// #include "Generators.h"
// #include "HistoricalCiphers.h"
// #include "DES.h"
// #include "AES.h"
#include "ModularAlgebra.h"
#include "RSA.h"

int main(void) {

    // euclid_t e = Extended_Euclid(5, 132);
    // printf("%u - %u - %u\n", e.d, e.x, e.y);

    int msg = 97;
    int key_priv;
    int key_pub;
    Create_RSA_Key(5, 11, &key_priv, &key_pub);
    printf("%x, %x\n", key_pub, key_priv);

    printf("%d\n", msg);
    msg = RSA_Enc(msg, key_pub, sizeof(int) * 8);
    printf("%d\n", msg);
    msg = RSA_Dec(msg, key_priv, sizeof(int) * 8);
    printf("%d\n", msg);

    return 0;
}
