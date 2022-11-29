#ifndef PERSON_H
#define PERSON_H

typedef struct person_t person_t;
person_t * person_create(char * line);
void person_destroy(person_t * person);
void person_print(person_t * person);

int person_get_age(person_t * person);
int person_get_income(person_t * person);

#endif