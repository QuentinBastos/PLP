#include <stdio.h>

int main(void)
{
    unsigned long long n;
    if (printf("Enter a non-negative integer: ") < 0) return 1;
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n == 0) {
        puts("0");
        return 0;
    }

    char bits[64];
    int idx = 0;
    while (n > 0) {
        bits[idx++] = (n % 2) ? '1' : '0';
        n /= 2;
    }

    for (int i = idx - 1; i >= 0; --i) {
        putchar(bits[i]);
    }
    putchar('\n');

    return 0;
}
