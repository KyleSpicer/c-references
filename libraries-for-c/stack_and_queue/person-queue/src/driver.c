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
    llist_t * queue = llist_create();

    // create people and insert into queue
    for(int i = 0; i < MAX_PEOPLE; i++){
        person_t * person = person_create(first_names[i], last_names[i]);
        enqueue(queue, person);
    }

    // display full queue
    printf("\nOriginal Queue: \n");
    llist_print(queue, (void(*)(void *))person_print);

    // dequeue and enqueue 3 of 4 people
    for(int i = 1; i < MAX_PEOPLE; i++){
        person_t * extracted_person = dequeue(queue);
        enqueue(queue, extracted_person);
    }

    // display new queue
    printf("\nNew Queue (after 3 dequeue/enqueues): \n");
    llist_print(queue, (void(*)(void *))person_print);

    llist_destroy(&queue, (void(*)(void*))person_destroy);

}

/*** end of file ***/