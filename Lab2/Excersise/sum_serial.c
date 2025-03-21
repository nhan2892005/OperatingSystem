#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    long long n = atoll(argv[1]);
    long long sum = 0;
    for (long long i = 1; i <= n; i++) {
        sum += i;
    }
    printf("Serial sum(1..%lld) = %lld\n", n, sum);
    return 0;
}
