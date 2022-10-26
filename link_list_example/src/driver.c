#include "llist.h"
#include "person.h"

int
main()
{
    llist_t * list = llist_create();

    person_t * person1 = person_create("Tim", "DeBerry", 12);

    person_t * person2 = person_create("Kyle", "Spicer", 42);

    person_t * person3 = person_create("Jacob", "Hitchcox", 99);

    person_t * person4 = person_create("Chante", "Lumpkin", 25);

    llist_insert_back(list, person1);
    llist_insert_front(list, person2);
    llist_insert_back(list, person3);
    llist_insert_front(list, person4);

    llist_print(list, (void (*)(void *))person_print);

    llist_destroy(list, (void (*)(void *))person_destroy);
}
