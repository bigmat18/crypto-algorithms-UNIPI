#include "generators.h"

int main(void) {
    int n = 10;
    int seme = 0;
    int *result = linear_generator(211, 10, 3, seme, n);
    for(int i = 0; i < n; i++) {
        fprintf(stderr, "%d\n", result[i]);
    }

    return 0;
}
