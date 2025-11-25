#include <stdio.h>

int main() {
    // Déclaration des variables
    char c = 'A';
    signed char sc = -128;
    unsigned char uc = 255;
    short s = -32768;
    unsigned short us = 65535;
    int i = -2147483647;
    unsigned int ui = 4294967295U;
    long int li = -2147483648L;
    unsigned long int uli = 4294967295UL;
    long long int lli = -9223372036854775807LL;
    unsigned long long int ulli = 18446744073709551615ULL;
    float f = 3.14f;
    double d = 3.141592653589793;
    long double ld = 3.141592653589793238L;

    // Affichage des variables
    printf("char: %c\n", c);
    printf("signed char: %d\n", sc);
    printf("unsigned char: %u\n", uc);
    printf("short: %d\n", s);
    printf("unsigned short: %u\n", us);
    printf("int: %d\n", i);
    printf("unsigned int: %u\n", ui);
    printf("long int: %ld\n", li);
    printf("unsigned long int: %lu\n", uli);
    printf("long long int: %lld\n", lli);
    printf("unsigned long long int: %llu\n", ulli);
    printf("float: %f\n", f);
    printf("double: %lf\n", d);
    printf("long double: %Lf\n", ld);

    return 0;
}
