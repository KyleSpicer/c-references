/**
 * @file person-queue.h
 * @author Kyle Spicer
 * @brief create prototypes for person-queue.h
 * 
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PERSON_H
#define PERSON_H

typedef struct person_t person_t;

person_t * person_create(const char * first_name, const char * last_name);

void person_destroy(person_t * person);

void person_print(person_t * person);

#endif /* PERSON_H */
/* end of file */

