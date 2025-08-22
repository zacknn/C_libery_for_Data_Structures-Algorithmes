#ifndef STACK_H
#define STACK_H

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity);
void push(Stack* stack, int value);
int pop(Stack* stack);
int peek(Stack* stack);
int stack_is_empty(Stack* stack);
void free_stack(Stack* stack);

#endif

