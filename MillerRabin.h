#include "utils.h"

/**
 * Theorem Miller and Rabin: If N is composed, the integers numbers between 2 and
 * N-1 that satisfy both predicates is < N/4
*/

// Mcd(N, y) == 1
bool P1(int N, int y) {
    return Euclid(N, y) == 1;
}

// (y^z mod N) == 1 or (exists i, 0 <= i <= w - 1, s.t. y^{2^i * z} mod N == -1)
bool P2(int N, int y, int z, int w) {
    if((int)pow(y, z) % N == 1) return true;
    
    for(int i = 0; i < w; i++) {
        if((int)pow(y, pow(2, i) * z) % N == -1) 
            return true;
    }
    return false;
}

bool Check(int N, int y) {
    // z and w are chosen arbitrarily
    int z; // = ...;
    assert(z % 2 != 0);
    int w; // = ...;
    assert(w >= 0);

    // Importat condition
    assert(N - 1 == (pow(2, w) * z));
    assert(y >= 2 && y <= N - 1);

    return P1(N, y) || P2(N, y, z, w);
}

bool MillerRabin(int N) {
    // N must be odd, otherwise its composed
    assert(N % 2 != 0);
    int k; // = ...;
    for(int i = 1; i <= k; i++) {
        // Choose a random value between 2 and N-1
        // We use C starard method rand()
        int y = Random(2, N-1);
        if(Check(N, y)) return false;
    }
    return true;
}

/**
 * COMPLEXITY:
 * - Check depends from P1 and P2:
 *  - P1: is polynomial using Euclid algoritms
 *  - P2: Calculate a series of y^z, y^{2z}, ..., y^{(2w-1)z} = y^{(N-1)/2} is critical.
 *        To execute this operation in polynomil time we use a exp series z = 2^w1 + 2^w2 + ... + 2^wt
 *        with w1 < ... < wt, we use the binary rappresentation. In this way we calculate y^z using this method
 *        and then, let's square it w-1 times.
 * ==> the complexity dependts only from k, and for one iteration we have <=1/4 probability of fail
 * ==> (1/4)^k it's the possible error of algoritm.
*/

int PrimeMR(int n) {
    int N; // = 1S1 with S is a sequence  of n-2 bit generate from a pseudo-random generator.
    while (MillerRabin(N)) {
        N += 2;
    }
    return N;
}