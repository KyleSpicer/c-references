#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

#define MAX_FNAME 32

struct person_t
{
    char * fname; // full name
};

person_t *
person_create(const char * fname)
{
    struct person_t * person = NULL;

    if (!fname)
    {
        goto PERSON_CREATE_EXIT;
    }
    person = calloc(1, sizeof(*person));
    if (person)
    {
        // person->age = age;

        person->fname = strndup(fname, MAX_FNAME);
        if (!person->fname)
        {
            free(person);
            person = NULL;
            goto PERSON_CREATE_EXIT;
        }
        // person->lname = strndup(lname, MAX_LNAME);
        // if (!person->lname)
        // {
            // free(person->fname);
            // free(person);
            // person = NULL;
        // }
    }
PERSON_CREATE_EXIT:
    return person;
}

void
person_destroy(person_t * person)
{
    if (!person)
    {
        return;
    }

    free(person->fname);
    // free(person->lname);
    free(person);
}

void
person_print(person_t * person)
{
    if (!person)
    {
        return;
    }

    printf("%s    ", person->fname);
}
