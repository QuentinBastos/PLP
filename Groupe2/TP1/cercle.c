#include <stdio.h>

int main(void)
{
    double myNum;
    printf("Saisir le rayon (float ou double): \n");

    if (scanf("%lf", &myNum) != 1)
    {
        fprintf(stderr, "Erreur de saisie\n");
        return 1;
    }

    printf("Rayon lu : %f\n", myNum);
    return 0;
}
