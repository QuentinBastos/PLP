#include <stdio.h>

int main(void)
{
    int a = 16;
    int b = 3;

    printf("Modulo operator:\n");
    printf("%d %% %d = %d\n", a, b, a % b);
    printf("\n");

    printf("Addition operator:\n");
    printf("%d + %d = %d\n", a, b, a + b);
    printf("\n");

    printf("Subtraction operator:\n");
    printf("%d - %d = %d\n", a, b, a - b);
    printf("\n");

    printf("Division operator:\n");
    printf("%d / %d = %d\n", a, b, a / b);
    printf("\n");

    printf("Comparison operator:\n");
    printf("%d > %d = %d\n", a, b, a > b);
    printf("\n");

    printf("Equality operator:\n");
    printf("%d == %d = %d\n", a, b, a == b);
    printf("\n");
    return 0;
}
