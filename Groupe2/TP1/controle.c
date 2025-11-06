#include <stdio.h>

int main(void)
{
    printf("Divisible by 4 but not by 6:\n");
    for (int i = 1; i <= 1000; i++) {
        if (i % 4 != 0)
            continue;
        if (i % 6 == 0)
            continue;
        printf("%d ", i);
    }
    printf("\n\n");

    printf("Even and divisible by 8:\n");
    int i = 1;
    while (i <= 1000) {
        if (i % 2 != 0) {
            i++;
            continue;
        }
        if (i % 8 == 0) {
            printf("%d ", i);
        } else {
        }
        if (i == 1000)
            break;
        i++;
    }
    printf("\n\n");

    printf("Divisible by 5 or 7 but not by 10:\n");
    i = 1;
    do {
        int div5 = i % 5 == 0;
        int div7 = i % 7 == 0;
        int div10 = i % 10 == 0;
        if ((div5 || div7) && !div10) {
            printf("%d ", i);
        } else {
        }
        i++;
    } while (i <= 1000);
    printf("\n");

    return 0;
}
