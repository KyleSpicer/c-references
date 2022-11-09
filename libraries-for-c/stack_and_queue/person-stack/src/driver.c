/**
 * @file driver.c
 * @author Kyle Spicer
 * @brief purpose is to use llist lib and create a queue of person structs
 * and perform various tasks with them
 * 
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>

#include "llist.h"
#include "person_lib.h"

#define MAX_PEOPLE 100

int main()
{
    const char * first_names[MAX_PEOPLE] = {"Craig", "Chante", "Jacob", "Kyle"};
    const char * last_names[MAX_PEOPLE] = {"DeBerry", "Lumpkin", "Hitchcox", "Spicer"};

    // create queue
    llist_t * stack = llist_create();
    
    // populate stack with data
    for(int i = 0; i < MAX_PEOPLE; i++){
        person_t * person = person_create(first_names[i], last_names[i]);
        push(stack, person);
    }

    // print original stack
    printf("Original Stack: \n");
    llist_print(stack, (void (*)(void *))person_print);

    //create new stack to add names to
    llist_t * stack2 = llist_create();

    // remove from first stack and add to second stack
    for(int i = 0; i < MAX_PEOPLE; i++){
        person_t * extracted_person = pop(stack);
        push(stack2, extracted_person);
    }

    // print second stack after modification
    printf("\n\nNew Stack: \n");
    llist_print(stack2, (void (*)(void *))person_print);

    // destroy the list
    llist_destroy(&stack, (void(*)(void*))person_destroy);
    llist_destroy(&stack2, (void(*)(void*))person_destroy);
}

/*** end of file ***/