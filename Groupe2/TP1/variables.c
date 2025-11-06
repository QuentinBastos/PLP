#include <stdio.h>
#include <limits.h>

int main(void)
{
    signed char sc = -65;
    unsigned char uc = UCHAR_MAX;

    short s = -12345;
    unsigned short us = USHRT_MAX;

    int i = -123456789;
    unsigned int ui = UINT_MAX;

    long int l = -1234567890L;
    unsigned long int ul = ULONG_MAX;

    long long int ll = -123456789012345LL;
    unsigned long long int ull = ULLONG_MAX;

    float f = -3.14f;
    double d = -100.0;
    long double ld = -1000.0L;

    printf("signed char: %hhd (as char: %c)\n", sc, sc);
    printf("unsigned char: %hhu (as char: %c)\n", uc, (unsigned char)uc);

    printf("short: %hd\n", s);
    printf("unsigned short: %hu\n", us);

    printf("int: %d\n", i);
    printf("unsigned int: %u\n", ui);

    printf("long int: %ld\n", l);
    printf("unsigned long int: %lu\n", ul);

    printf("long long int: %lld\n", ll);
    printf("unsigned long long int: %llu\n", ull);

    printf("float: %.2f\n", f);
    printf("double: %.2f\n", d);
    printf("long double: %.2Lf\n", ld);

    return 0;
}
