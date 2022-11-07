#include "static_stack.h"

#include <stdio.h>
#include <stdlib.h>

//This is a Last - In First - Out(LIFO) data structure.
//
//Items are pushed and popped from the top.
//
//The top pointer points to the last item on the stack.
stack * create_stack(int size)
{
	//An empty starting position is required to initialize the top pointer
	// because it is moved forward when pushing a new item.The first item will
	// be at the second index of the stack array so the actual capacity is one
	// more than the given size.
	stack * s = (stack *) malloc(sizeof(stack));
	s->capacity = size;
	s->data = (int *)malloc(sizeof(int) * (s->capacity + 1));
	s->top = s->data;
	return s;
}

void delete_stack(stack ** s)
{
	free((*s)->data);
	free(*s);
	*s = 0;
}

void push(stack * s, int data)
{
	if (s->top != &s->data[s->capacity]) {
		//Move top pointer forward and then add to stack.
		//
		//The top pointer always points to the last item on the stack.
		* (++s->top) = data;
	} else {
		printf("Stack of size %d is full.\n", s->capacity);
	}
}

int pop(stack * s)
{
	//Move top pointer backward.
	if (s->top != s->data) {
		int value = *(s->top);
		--(s->top);
		return value;
	} else {
		printf("Reached bottom of stack\n");
		return -1;
	}
}

int top(stack * s)
{
	return *(s->top);
}

int empty(stack * s)
{
	//First data position denotes empty because the top pointer moves forward
	// when pushing an item onto the stack.
	return (s->top == s->data);
}
