/**
 * @file person_lib.c
 * @author Kyle Spicer
 * @brief define person functions and prototypes
 * 
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "person_lib.h"

#define MAX_NAME 32

struct person_t
{
    char * first_name;
    char * last_name;
};

person_t * person_create(const char * first_name, const char * last_name)
{
    struct person_t * person = NULL;


    if(!first_name || !last_name){
        goto PERSON_CREATE_EXIT;
    }
    person = calloc(1, sizeof(*person));
    if(person){
        person->first_name = strndup(first_name, MAX_NAME);
        person->last_name = strndup(last_name, MAX_NAME);
        if(!person->first_name || !person->last_name){
            printf("Error with creating first or last name.\n");
            free(person);
            person = NULL;
            goto PERSON_CREATE_EXIT;
        }
    }

    PERSON_CREATE_EXIT:
    return person;
}

void person_destroy(person_t * person)
{
    if(!person){
        return;
    }
    free(person->first_name);
    free(person->last_name);
    free(person);
}

void person_print(person_t * person)
{
    if(!person){
        return;
    }

    printf("\t%s %s\n", person->first_name, person->last_name);
}