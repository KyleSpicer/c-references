#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

#define MAX_FNAME 16
#define MAX_LNAME 32

struct person_t
{
    char * fname;
    char * lname;
    int    age;
};

person_t *
person_create(const char * fname, const char * lname, int age)
{
    struct person_t * person = NULL;

    if (!fname || !lname || age < 0)
    {
        goto PERSON_CREATE_EXIT;
    }
    person = calloc(1, sizeof(*person));
    if (person)
    {
        person->age = age;

        person->fname = strndup(fname, MAX_FNAME);
        if (!person->fname)
        {
            free(person);
            person = NULL;
            goto PERSON_CREATE_EXIT;
        }
        person->lname = strndup(lname, MAX_LNAME);
        if (!person->lname)
        {
            free(person->fname);
            free(person);
            person = NULL;
        }
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
    free(person->lname);
    free(person);
}

void
person_print(person_t * person)
{
    if (!person)
    {
        return;
    }

    printf("%s %s is %d y/o\n", person->fname, person->lname, person->age);
}
