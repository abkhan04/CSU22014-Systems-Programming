#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct double_stack
{
    double *items;
    int max_size;
    int top;
};

// prototypes of functions that operate on the double stack
// create a new empty stack
struct double_stack *double_stack_new(int max_size);

// push a value onto the stack
void double_stack_push(struct double_stack *this, double value);

// pop a value from the stack
double double_stack_pop(struct double_stack *this);

// check if a stack is empty
int double_stack_empty(struct double_stack *this);

// look at the top most item on the stack
double double_stack_peek(struct double_stack *this);

#endif
