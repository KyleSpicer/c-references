#ifndef PERSON_H
#define PERSON_H

typedef struct person_t person_t;

person_t * person_create(const char * fname, const char * lname, int age);

void person_destroy(person_t * person);

void person_print(person_t * person);

#endif
