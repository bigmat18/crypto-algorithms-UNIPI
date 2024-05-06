#include "utils.h"

int* linear_generator(int a, int b, int m, int x, int n) {
    assert(Euclid(b, m) == 1);
    assert(m % 4 != 0 || (a - 1) % 4);
    int* primes = Prime(m);
    while(*(++primes)!= '\0')
        assert((a - 1) % (*primes) == 0);

    int* result = (int*)malloc(sizeof(int) * n);
    result[0] = x;

    for(int i = 1; i < n; i++) 
        result[i] = ((a * result[i-1]) + b) % m;

    return result;
}

int BBJ_generator() {
    return 0;
}

int main(void) {
    // printf("%d", Euclid(10, 5));
    // int* primes = Prime(50);
    // while(*(++primes )!= '\0')
    //     fprintf(stderr, "%d - ", *(primes));

    int n = 10;
    int seme = 0;
    int *result = linear_generator(211, 10, 3, seme, n);
    for(int i = 0; i < n; i++) {
        fprintf(stderr, "%d\n", result[i]);
    }

    return 0;
}
