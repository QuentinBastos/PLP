#include <stdio.h>

int main(void)
{
    printf("Size of char: %zu byte(s)\n", sizeof(char));
    printf("Size of signed char: %zu byte(s)\n", sizeof(signed char));
    printf("Size of unsigned char: %zu byte(s)\n", sizeof(unsigned char));
    printf("Size of short: %zu byte(s)\n", sizeof(short));
    printf("Size of unsigned short: %zu byte(s)\n", sizeof(unsigned short));
    printf("Size of int: %zu byte(s)\n", sizeof(int));
    printf("Size of unsigned int: %zu byte(s)\n", sizeof(unsigned int));
    printf("Size of long int: %zu byte(s)\n", sizeof(long int));
    printf("Size of unsigned long int: %zu byte(s)\n", sizeof(unsigned long int));
    printf("Size of long long int: %zu byte(s)\n", sizeof(long long int));
    printf("Size of float: %zu byte(s)\n", sizeof(float));
    printf("Size of double: %zu byte(s)\n", sizeof(double));
    printf("Size of long double: %zu byte(s)\n", sizeof(long double));
    return 0;
}
