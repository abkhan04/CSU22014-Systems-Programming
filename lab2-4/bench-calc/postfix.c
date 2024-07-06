#include <string.h>
#include "postfix.h"
#include "math.h"

int is_operator(char *token);

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs)
{
    struct double_stack *my_stack = double_stack_new(nargs);

    double num1;
    double num2;

    for (int i = 0; i < nargs; i++)
    {
        if (is_operator(args[i]))
        {
            num2 = double_stack_pop(my_stack);
            num1 = double_stack_pop(my_stack);

            switch (args[i][0])
            {
                case '+':
                    double_stack_push(my_stack, num1 + num2);
                    break;
                case '-':
                    double_stack_push(my_stack, num1 - num2);
                    break;
                case 'X':
                    double_stack_push(my_stack, num1 * num2);
                    break;
                case '/':
                    double_stack_push(my_stack, num1 / num2);
                    break;
                case '^':
                    double_stack_push(my_stack, pow(num1, num2));
                    break;
                default:
                    break;
            }
        }
        else
        {
            double_stack_push(my_stack, atof(args[i]));
        }
    }

    return double_stack_pop(my_stack);
}

int is_operator(char *token)
{
    if (strlen(token) == 1)
    {
        switch (token[0])
        {
            case '+':
            case '-':
            case 'X':
            case '/':
            case '^':
                return 1;
            default:
                return 0;
        }
    }

    return 0;
}