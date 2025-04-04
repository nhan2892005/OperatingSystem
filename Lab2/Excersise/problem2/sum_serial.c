#include <stdio.h>
#include <stdlib.h>
unsigned long long calculate_sum(unsigned long long n) {
    unsigned long long sum = 0;
    for (unsigned long long i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    unsigned long long n = strtoull(argv[1], NULL, 10);
    unsigned long long sum = calculate_sum(n);

    printf("%llu\n", sum);
    return 0;
}
