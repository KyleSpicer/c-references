#ifndef STATIC_STACK_H
#define STATIC_STACK_H

struct stack {
	int *top;
	int *data;
	int capacity;
};
typedef struct stack stack;

stack *create_stack(int);
void delete_stack(stack **);
void push(stack *, int);
int pop(stack *);
int top(stack *);
int empty(stack *);

#endif
