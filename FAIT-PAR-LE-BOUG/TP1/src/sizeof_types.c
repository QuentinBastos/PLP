#include <stdio.h>

int main()
{
    // Declaration des variables
    char my_char;
    signed char my_sc;
    unsigned char my_uc;
    short my_short;
    signed short my_ss;
    unsigned short my_us;
    int my_int;
    signed int my_si;
    unsigned int my_ui;
    long int my_li;
    signed long int my_sli;
    unsigned long int my_uli;
    long long int my_lli;
    float my_float;
    double my_double;
    long double my_ld;

    // Affichage des tailles des types de données
    printf("Size of char : %lu octets\n", sizeof(my_char));
    printf("Size of signed char : %lu octets\n", sizeof(my_sc));
    printf("Size of unsigned char : %lu octets\n", sizeof(my_uc));
    printf("Size of short : %lu octets\n", sizeof(my_short));
    printf("Size of signed short : %lu octets\n", sizeof(my_ss));
    printf("Size of unsigned short : %lu octets\n", sizeof(my_us));
    printf("Size of int : %lu octets\n", sizeof(my_int));
    printf("Size of signed int : %lu octets\n", sizeof(my_si));
    printf("Size of unsigned int : %lu octets\n", sizeof(my_ui));
    printf("Size of long int : %lu octets\n", sizeof(my_li));
    printf("Size of signed long int : %lu octets\n", sizeof(my_sli));
    printf("Size of unsigned long int : %lu octets\n", sizeof(my_uli));
    printf("Size of long long int : %lu octets\n", sizeof(my_lli));
    printf("Size of float : %lu octets\n", sizeof(my_float));
    printf("Size of double : %lu octets\n", sizeof(my_double));
    printf("Size of long double : %lu octets\n", sizeof(my_ld));

    return 0;
}