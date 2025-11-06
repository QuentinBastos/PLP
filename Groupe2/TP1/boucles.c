#include <stdio.h>

int main(void)
{
    printf("Enter a number under 5 :\n");
    int n;
    scanf("%d", &n);
    if (n > 5)
    {
        printf("The number isn't under 5");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (i == j)
            {
                printf("*");
                printf("\n");
            }
            else if (j == 0 || i == n - 1)
            {
                printf("*");
            }
            else
            {
                printf("#");
            }
        }
    }
    printf("\n");

    int i = 0;
    while (i < n)
    {
        int j = 0;
        while (j < i + 1)
        {
            if (i == j)
            {
                printf("*");
                printf("\n");
            }
            else if (j == 0 || i == n - 1)
            {
                printf("*");
            }
            else
            {
                printf("#");
            }
            j++;
        }
        i++;
    }
    return 0;
}
