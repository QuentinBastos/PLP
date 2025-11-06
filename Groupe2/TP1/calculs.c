#include <stdio.h>

int main(void)
{
    int num1 = 0, num2 = 0;
    char op = 0;

    printf("Operator (use one of: `+` `-` `*` `/` `%%` `&` `|` `~`): ");
    if (scanf(" %c", &op) != 1) {
        fprintf(stderr, "Failed to read operator\n");
        return 1;
    }

    if (op == '~') {
        printf("Enter one integer: ");
        if (scanf("%d", &num1) != 1) {
            fprintf(stderr, "Invalid integer\n");
            return 1;
        }
    } else {
        printf("Enter two integers (num1 num2): ");
        if (scanf("%d %d", &num1, &num2) != 2) {
            fprintf(stderr, "Invalid integers\n");
            return 1;
        }
    }

    switch (op) {
    case '+':
        printf("%d + %d = %d\n", num1, num2, num1 + num2);
        break;
    case '-':
        printf("%d - %d = %d\n", num1, num2, num1 - num2);
        break;
    case '*':
        printf("%d * %d = %d\n", num1, num2, num1 * num2);
        break;
    case '/':
        if (num2 == 0) {
            fprintf(stderr, "Error: division by zero\n");
        } else {
            printf("%d / %d = %d\n", num1, num2, num1 / num2);
        }
        break;
    case '%':
        if (num2 == 0) {
            fprintf(stderr, "Error: modulo by zero\n");
        } else {
            printf("%d %% %d = %d\n", num1, num2, num1 % num2);
        }
        break;
    case '&':
        printf("%d & %d = %d\n", num1, num2, num1 & num2);
        break;
    case '|':
        printf("%d | %d = %d\n", num1, num2, num1 | num2);
        break;
    case '~':
        printf("~%d = %d\n", num1, ~num1);
        break;
    default:
        fprintf(stderr, "Unknown operator: %c\n", op);
        return 1;
    }

    return 0;
}
