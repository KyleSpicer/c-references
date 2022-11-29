#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

#define MAX_NAME 32

struct person_t
{
    char * ssn;
    char * fname;
    char * lname;
    int age;
    int income;
};

person_t * 
person_create(char * line)
{
    struct person_t * person = NULL;

    if (!line)
    {
        printf("Insufficient data.\n");
        goto PERSON_CREATE_EXIT;
    }

    person = calloc(1, sizeof(*person));
    if(!person){
        return NULL;
    }
    
    if (person)
    {
        // TODO ABCs for all
        person->ssn = strndup(strsep(&line, "\t"), 128);
        person->fname = strndup(strsep(&line, "\t"), 128);
        person->lname = strndup(strsep(&line, "\t"), 128);

        char * age = strsep(&line, "\t");
        char * income = strsep(&line, "\t");
        
        char * ptr = NULL;
        person->age = strtol(age, &ptr, 10);
        if('\0' == *ptr) {
            person->income = strtol(income, &ptr, 10);
        }

        if('\0' != *ptr) {
            person_destroy(person);
            person = NULL;
        }
    }
PERSON_CREATE_EXIT:
    return person;
}

// int person_cmp(void *arg1, void *arg2)
// {
//     person_t *person1 = (person_t *)arg1;
//     person_t *person2 = (person_t *)arg2;
//     if(!person1 || !person2) {
//         return 0;
//     }
//     return strncmp(person1->ssn, person2->ssn, 12);
// }

void
person_destroy(person_t * person)
{
    if (!person)
    {
        return;
    }
    free(person->ssn);
    free(person->fname);
    free(person->lname);
    // free(person->age);
    // free(person->income);
    free(person);
}

void
person_print(person_t * person)
{
    if (!person){
        return;
    }

    printf("%s\t%s\t\t%s\t\t%d\t\t$%d \n", person->ssn, person->fname, person->lname, person->age, person->income);
}

int person_get_income(person_t * person)
{
    return person->income;
}

int person_get_age(person_t * person)
{
    return person->age;
}


/* end of file */