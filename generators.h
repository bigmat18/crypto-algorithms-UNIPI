#include "Utils.h"

int* linear_generator(int a, int b, int m, int x, int n) {
    assert(a > 0 && b > 0 && m > 0 && x > 0 && n > 0);
    assert(Euclid(b, m) == 1);
    assert(m % 4 != 0 || (a - 1) % 4);

    int *primes = PrimeGenerator(m);
    while(*(++primes)!= '\0')
        assert((a - 1) % (*primes) == 0);

    int* result = (int*)malloc(sizeof(int) * n);
    result[0] = x;

    for(int i = 1; i < n; i++) 
        result[i] = ((a * result[i-1]) + b) % m;

    return result;
}

/**
 * p = big integer
 * q = big integer
 * x0 = seed
 * n = size of random numbers sequence
 * m = size of bit sequenze
 */
int* BBS_generator(long int p, long int q, int x0, int m) {
    // Pre condition to generate a sequenze of random value
    assert(p > 0 && q > 0 && x0 > 0 && m > 0);
    assert(IsPrime(2 * floorf((float)p / 4) + 1));
    assert(IsPrime(2 * floorf((float)q / 4) + 1));
    assert(p % 4 == 3);
    assert(q % 4 == 3);

    int n = p * q;
    assert(m <= n);
    int *result = (int*)malloc(m * sizeof(int));

    // f(x) = x^2 mod n è one-way se n è composto
    int x_i_less_1 = x0;
    for(int i = 1; i <= m; i++) {
        /**
         * x_i <- (x_{i-1})^2 mod n
         * b_i = 1 <==> x_{m-1} è dispari
        */
        int xi = (int)(powf(x_i_less_1, 2)) % n;
        result[m - i] = xi % 2 == 0 ? 0 : 1;
        x_i_less_1 = xi;
    }

    return result;
}

