#include <stdio.h>

int main() {
    int T, i;
    unsigned long long fib[61], N;

    fib[0] = 0;
    fib[1] = 1;
    for(i = 2; i <= 60; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    scanf("%d", &T);
    while(T--) {
        scanf("%llu", &N);
        printf("Fib(%llu) = %llu\n", N, fib[N]);
    }

    return 0;
}