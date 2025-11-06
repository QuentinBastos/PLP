#include <stdio.h>

int main(void)
{
    const int n = 1000;
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
    return 0;
}
