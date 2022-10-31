#include "llist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_SIZE 8

// https://www.cs.princeton.edu/courses/archive/spr01/cs126/exercises/adt.html

typedef struct letter_t 
{
    char c;
}letter_t;

void pushpop(const char * input);
void putget(const char * input);
void pushpop_stackque(const char * input);

int main()
{
    printf("\nPrinceton Exercises - Stack and Queue\n\n");

    /*Exercise 1. (Sedgewick, Exercise 4.6).  A letter means push and an 
    asterisk means pop in the following sequence.  Give the sequence of values 
    returned by the pop operations when this sequence of operations is performed 
    on an initially empty LIFO stack.*/

    printf("Exercise 1: \n");
    const char * first_input = "EAS*Y*QUE***ST***IO*N***";
    printf("%s    ==>  ", first_input);
    pushpop(first_input);
    printf("\n\n");

    printf("Exercise 2: \n");
    const char * second_input = "LA*STI*N*FIR*ST**OU*T******";    
    printf("%s ==>  ", second_input);
    pushpop(second_input);
    printf("\n\n");

    printf("Exercise 3: \n");
    const char * third_input = "";    
    printf("\"%s\" ==>  ", third_input);
    pushpop(third_input);
    printf("\n\n");

    /* put means enqueue, get means dequeue */
    printf("Exercise 4: \n");
    const char * fourth_input = "EAS*Y*QUE***ST***O*N***";    
    printf("%s ==>  ", fourth_input);
    putget(fourth_input);
    printf("\n\n");

    /* Using two stacks to mimic queue behavior */
    /* https://www.geeksforgeeks.org/queue-using-stacks/ */
    printf("Exercise 11: \n");
    const char * input = "EAS*Y*QUE***ST***IO*N***";
    printf("%s    ==>  ", input);
    pushpop_stackque(input);
    printf("\n\n");


}

void pushpop(const char * input)
{
    llist_t * stack = llist_create();
    size_t len = strlen(input);
    letter_t *letter = NULL;

    for (size_t i = 0; i <= len; ++i)
    {
        if (len < 1)
        {
            printf("Error. Nothing to pop.");
            break;
        }

        switch(input[i])
        {
            case '*':
                letter = pop(stack);
                printf("%c", letter->c);
                free(letter);
                break;

            default:
                letter = calloc(1, sizeof(*letter));
                letter->c = input[i];
                push(stack, (void *)letter);
                break;
        }
    }
    llist_destroy(stack, free);
}

void putget(const char * input)
{
    llist_t * queue = llist_create();
    size_t len = strlen(input);
    letter_t *letter = NULL;

    for (size_t i = 0; i < len - 1; ++i)
    {
        if (len < 1)
        {
            printf("Error. Nothing to pop.");
            break;
        }

        switch(input[i])
        {
            case '*':
                letter = dequeue(queue);
                printf("%c", letter->c);
                free(letter);
                break;

            default:
                letter = calloc(1, sizeof(*letter));
                letter->c = input[i];
                enqueue(queue, (void *)letter);
                break;
        }
    }
    llist_destroy(queue, free);
}

void pushpop_stackque(const char * input)
{
    llist_t * stack = llist_create();
    llist_t * stack2 = llist_create();

    size_t len = strlen(input);
    letter_t *letter = NULL;

    for (size_t i = 0; i < len; ++i)
    {
        if (len < 1)
        {
            printf("Error. Nothing to pop.");
            break;
        }

        switch(input[i])
        {
            case '*':
                if (size(stack) == 0 && size(stack2) == 0)
                {
                    printf("Error.\n");
                }
                if(size(stack2) == 0)
                {
                    while(size(stack) > 0)
                    {
                        letter = pop(stack);
                        push(stack2, letter);
                    }
                }        
                letter = pop(stack2);
                printf("%c", letter->c);
                free(letter);
                break;

            default:
                letter = calloc(1, sizeof(*letter));
                letter->c = input[i];
                push(stack, (void *)letter);
                break;
        }
    }
    printf("\n");

    llist_destroy(stack, free);
    llist_destroy(stack2, free);

}
/* end of file */
