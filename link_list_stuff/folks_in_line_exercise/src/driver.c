#include "llist.h"
#include "person.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 32

int
main()
{
    /* create a struct for link list shell */
    llist_t * list = llist_create();

    /* open .txt file */
    FILE *p_file = fopen("roster.txt", "r");

    if(!p_file)
    {
        printf("Unable to open file./n");
        exit(1);
    }

    char line_from_file[MAX_INPUT_LENGTH];
    /* while loop to create link list from .txt */    
    while((fgets(line_from_file, MAX_INPUT_LENGTH, p_file)) != NULL)
    {
        /* remove newline from fgets */
        line_from_file[strcspn(line_from_file, "\n")] = 0; 

        person_t * person = person_create(line_from_file);

        /* create person struct from line */
        llist_insert_back(list, person);
    }

    fclose(p_file);
    
    // original list
    printf("\nOriginal List:  ");
    llist_print(list, (void (*)(void *))person_print);
    printf("\n\n");

    // added to front
    person_t * new_person_front = person_create("tommy");
    llist_insert_front(list, new_person_front);
    printf("Add to front: ");
    llist_print(list, (void (*)(void *))person_print);
    printf("\n\n");

    // added to back
    person_t * new_person_back = person_create("lorax");
    llist_insert_back(list, new_person_back);
    printf("Add to back:  ");
    llist_print(list, (void (*)(void *))person_print);
    printf("\n\n");

    // extract head
    person_t * extracted_person = extract_head(list);
    person_destroy(extracted_person);
    printf("Extract head:  ");
    llist_print(list, (void (*)(void *))person_print);
    printf("\n\n");

    // extract tail
    person_t * extracted_tail = extract_tail(list);
    person_destroy(extracted_tail);
    printf("Extract tail:  ");
    llist_print(list, (void (*)(void *))person_print);
    printf("\n\n");

    for (int i = 0; i < 7; ++i)
    {
        person_t *temp = extract_tail(list);
        person_destroy(temp);
        printf("%d remain ", 6 - i);
        llist_print(list, (void (*)(void *))person_print);
        printf("\n\n");
    }
    
    llist_destroy(list, (void (*)(void *))person_destroy);

    
}
