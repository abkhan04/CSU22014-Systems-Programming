#include "stack.h"

struct double_stack *double_stack_new(int max_size)
{
    struct double_stack *result;
    result = malloc(sizeof(struct double_stack));
    result -> items = malloc(max_size * sizeof(double));
    result -> max_size = max_size;
    result -> top = -1;

    return result;
}

// push a value onto the stack
void double_stack_push(struct double_stack *this, double value)
{
    if (this -> top < this -> max_size)
    {
        this -> top++;
        this -> items[this -> top] = value;
    }
    else
    {
        printf("Error: Stack Overflow\n");
    }
}

// pop a value from the stack
double double_stack_pop(struct double_stack *this)
{
    if (this -> top != -1)
    {
        double value = this -> items[this -> top];
        this -> top--;
        return value;
    }
    else
    {
        printf("Error: Stack Underflow\n");
        return 0;
    }
}

// check if a stack is empty
int double_stack_empty(struct double_stack *this)
{
    if (this -> top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// look at the top most item on the stack
double double_stack_peek(struct double_stack *this)
{
    return this -> items[this -> top];
}
