#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// Massimo comun divisore (MCD)
int Euclid(int a, int b) {
    assert(a >= b);
    if (b == 0) return a;
    else return Euclid(b, a % b);
}

// Primes numbers 
int* Prime(int num) {
    bool prime[num + 1];
    int count = num + 1;
    for (int i = 0; i <= num; i++)
        prime[i] = true;

    for (int i = 2; i * i <= num; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= num; j += i) {
                prime[j] = false;
                count--;
            }
        }
    }

    int* prime_num = (int*)malloc(count * sizeof(int));
    if (prime_num == NULL) exit(1);

    int index = 0;
    for (int i = 0; i <= num; i++) {
        if (prime[i]) {
            prime_num[index] = i;
            index++;
        }
    }
    return prime_num;
}