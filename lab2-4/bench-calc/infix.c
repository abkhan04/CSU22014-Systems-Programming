#include "infix.h"

int check_precedence(char token);
int is_operator2(char *token);

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs)
{
    struct double_stack *my_stack = double_stack_new(nargs);

    char **postfix_string = malloc(sizeof(char *) * nargs);
    int postfix_nargs = 0;

    for (int i = 0; i < nargs; i++)
    {
        if (args[i][0] == '(')
        {
            double_stack_push(my_stack, args[i][0]);
        }
        else if (is_operator2(args[i]))
        {
            while (check_precedence((char) double_stack_peek(my_stack)) >= check_precedence(args[i][0]))
            {
                postfix_string[postfix_nargs] = malloc(sizeof(char) * 2);
                postfix_string[postfix_nargs][0] = (char) double_stack_pop(my_stack);
                postfix_string[postfix_nargs][1] = '\0';
                postfix_nargs++;
            }

            double_stack_push(my_stack, args[i][0]);
        }
        else if (args[i][0] == ')')
        {
            while ((char) double_stack_peek(my_stack) != '(')
            {
                postfix_string[postfix_nargs] = malloc(sizeof(char) * 2);
                postfix_string[postfix_nargs][0] = (char) double_stack_pop(my_stack);
                postfix_string[postfix_nargs][1] = '\0';
                postfix_nargs++;
            }

            double_stack_pop(my_stack);
        }
        else
        {
            postfix_string[postfix_nargs] = args[i];
            postfix_nargs++;
        }
    }

    while (!double_stack_empty(my_stack))
    {
        postfix_string[postfix_nargs] = malloc(sizeof(char) * 2);
        postfix_string[postfix_nargs][0] = (char) double_stack_pop(my_stack);
        postfix_string[postfix_nargs][1] = '\0';
        postfix_nargs++;
    }

    fprintf(stderr, "message");

    return evaluate_postfix_expression(postfix_string, postfix_nargs);
}

int check_precedence(char token)
{
    if (token == '+' || token == '-')
    {
        return 1;
    }
    else if (token == 'X' || token == '/')
    {
        return 2;
    }
    else if (token == '^')
    {
        return 3;
    }

    return 0;
}

int is_operator2(char *token)
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
