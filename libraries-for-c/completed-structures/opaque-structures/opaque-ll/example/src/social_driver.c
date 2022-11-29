#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "llist.h"
#include "person.h"

#define MAX_LINE_LEN 256

// build iter_t for linked list - allows access to one 
// element at a time without having to push/pop/peak

int avg_income(int total_salaries, int number_of_people)
{
    return total_salaries / number_of_people;
}

int avg_income_age(llist_t * list, int total_people, int age_to_search)
{
    int person_age = 0; 
    int total_salaries_for_age = 0;
    int number_people_for_age = 0;

    for (int i = 0; i < total_people; ++i) {
        person_t * popped_person = dequeue(list);
        person_age = person_get_age(popped_person);
        if(0 >= person_age) {
            return 0;
        }

        if(age_to_search == person_age) {
            total_salaries_for_age += person_get_income(popped_person);
            number_people_for_age++;
        }

        person_destroy(popped_person);
        popped_person = NULL;
    }

    return total_salaries_for_age / number_people_for_age;
}

int main()
{

    FILE * fp = fopen("people.txt", "r");
    if(!fp) {
        printf("Error: %d\n", errno);
        exit(1);
    }

    llist_t * list = llist_create();

    if(!list) {
        printf("Unable to allocate memory\n");
        exit(1);
    }

    // read in contents of file
    
    int total_salaries = 0;
    char line[MAX_LINE_LEN];

    while(fgets(line, MAX_LINE_LEN, fp) != NULL) {
        line[strcspn(line, "\n")] = 0;

        // create person
        person_t * person = person_create(line);

        // total all salaries from people
        total_salaries += person_get_income(person);

        if(!person) {
            free(person);
            person = NULL;
            exit(1);
        }

        // insert person into list
        llist_insert_back(list, person);

    }

    // get average income for all people
    int num_people = list_size(list);
    int total_avg_income = avg_income(total_salaries, num_people);
    printf("\navg income = $%d\n", total_avg_income);

    // get average income for all people
    int avg_income_for_age;
    int age_to_search = 72;
    
    avg_income_for_age = avg_income_age(list, num_people, age_to_search);
    
    printf("average income (%d) = $%d\n", age_to_search, avg_income_for_age);

    //print llist
    llist_print(list, (void (*)(void *))person_print);

    // destroy llist
    fclose(fp);
    // free memory
    llist_destroy(list, (void (*)(void *))person_destroy);



}