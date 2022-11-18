/**
 * @file check_llist_library.c
 * @author CW2 Kyle Spicer
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../src/llist.h"
#include "../src/person.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMS 4

/**
 * @brief Verify link list is created when create function is called
 * 
 */
START_TEST(test_valid_llist_create) {

    // verifies that create list function creates a llist
    llist_t * list = llist_create();
    ck_assert(list != NULL);
    llist_destroy(&list, free);

}END_TEST

/**
 * @brief Verifies data successfully added to linked list
 * - creates list, adds person struct, checks size, destroys list at completion
 * 
 */
START_TEST(test_valid_llist_create_with_data) {
    
    // creates mock llist with data
    llist_t * test_list = llist_create();

    // create persons and add to test list
    person_t * person1 = person_create("kyle");
    llist_insert_back(test_list, person1);
    person_t * person2 = person_create("katherine");
    llist_insert_back(test_list, person2);
    person_t * person3 = person_create("lucas");
    llist_insert_back(test_list, person3);
    person_t * person4 = person_create("jack");
    llist_insert_back(test_list, person4);

    // asserts the total size is 4
    ck_assert(list_size(test_list) == 4);

    // clean up memory
    llist_destroy(&test_list, person_destroy);

}END_TEST

/**
 * @brief Create linked list and destroy with destroy function
 * - ck asset ensures memory address is NULL after deletion
 * 
 */
START_TEST(test_valid_destroy_llist) {
    // creates empty list
    llist_t * test_list = llist_create();
    ck_assert(test_list != 0);

    // destroys empty list
    llist_destroy(&test_list, free);
    ck_assert(test_list == NULL);
}END_TEST

/**
 * @brief Creates llist and add elements to front and back
 * - ck asserts check size throughout to ensure elements are being added/removed
 */
START_TEST(test_llist_add_front_and_back) {

    llist_t * tester_list = llist_create();

    person_t * person_1 = person_create("katherine");
    llist_insert_front(tester_list, person_1);
    ck_assert(list_size(tester_list) == 1);

    person_t * person_2 = person_create("jack");
    llist_insert_front(tester_list, person_2);
    ck_assert(list_size(tester_list) == 2);

    person_t * person_3 = person_create("lucas");
    llist_insert_back(tester_list, person_3);
    ck_assert(list_size(tester_list) == 3);

    llist_destroy(&tester_list, person_destroy);

}END_TEST

/**
 * @brief Creates stack, attepmts to pop NULL from empty stack.
 * - ck assert - verifies that NULL is returned when attempting to pop and empty
 * list.
 * 
 */
START_TEST(test_stack_pop_empty) {
    // create stack
    llist_t * stack = llist_create();

    // attempt to pop NULL from empty stack
    ck_assert(pop(stack) == NULL);
    
    // free memory
    llist_destroy(&stack, free);

}END_TEST

/**
 * @brief Attempt to push NULL to empty list verifying that the size is 0
 * 
 */
START_TEST(test_stack_push_null) {
    // create list
    llist_t * stack = llist_create();
    
    // create person with NULL information
    person_t * person = person_create(NULL);

    // attempt to push NULL to stack
    push(stack, person);

    // list size should be zero with no information pushed
    ck_assert(list_size(stack) == 0);
    ck_assert(list_size(stack) != 1);

    // free memory
    llist_destroy(&stack, free);


}END_TEST

/**
 * @brief 
 * 
 */
START_TEST(test_queue_create_enqueue_dequeue) {
    // create queue
    llist_t * queue = llist_create();

    const char * names[5] = {"kyle", "jacob", "craig", "tim", "chante"};

    // enqueueing names and checking size after each entry
    for (int i = 0; i < 5; i++) {
        enqueue(queue, &names[i]);
        ck_assert(list_size(queue) == i + 1);
    }

    // dequeue and check names and size 
    for (int i = 0; i < 5; i++) {
        person_t * person = dequeue(queue);
        ck_assert(person == &names[i]);
        ck_assert(list_size(queue) == 4 - i);
    }

    llist_destroy(&queue, free);
    
    
}END_TEST

START_TEST(test_stack_create_push_pop) {
    // create stack
    llist_t * stack = llist_create();

    const char * names[5] = {"kyle", "jacob", "craig", "tim", "chante"};
    const char * reverse_names[5] = {"chante", "tim", "craig", "jacob", "kyle"};

    // push names to stack and checking size after each entry
    for (int i = 0; i < 5; i++) {
        push(stack, &names[i]);
        ck_assert(list_size(stack) == i + 1);
    }

    // pop names and check size
    for (int i = 0; i < 5; i++) {
        pop(stack);
        ck_assert(list_size(stack) == 4 - i);
    }

    llist_destroy(&stack, free);

}END_TEST

/* creating Suite */
Suite * check_llist(void)
{
    Suite * suite;
    TCase * tc_valid;
    TCase * tc_stack;
    TCase * tc_queue;
    TCase * tc_llist;

    /* creates intitial suite */
    suite = suite_create("check_llist");

    /* confirms successful creation/deletion of structures */
    tc_valid = tcase_create("valid");
    tcase_add_test(tc_valid, test_valid_llist_create);
    tcase_add_test(tc_valid, test_valid_llist_create_with_data);
    tcase_add_test(tc_valid, test_valid_destroy_llist);
    
    
    tc_stack = tcase_create("stack");
    tcase_add_test(tc_stack, test_stack_pop_empty);
    tcase_add_test(tc_stack, test_stack_push_null);
    tcase_add_test(tc_stack, test_stack_create_push_pop);
    
    
    tc_queue = tcase_create("queue");
    tcase_add_test(tc_queue, test_queue_create_enqueue_dequeue);
    
    
    tc_llist = tcase_create("llist");
    tcase_add_test(tc_llist, test_llist_add_front_and_back);

    suite_add_tcase(suite, tc_valid);
    suite_add_tcase(suite, tc_stack);
    suite_add_tcase(suite, tc_queue);
    suite_add_tcase(suite, tc_llist);

    return suite;
}


int main(void)
{
    /* creating Suite*/
    Suite * suite = check_llist();
    SRunner * runner = srunner_create(suite);

    /* prevents confusing valgrind errors from displaying */
    srunner_set_fork_status(runner, CK_NOFORK);
    
    /* actual Suite Runner execution with desired verbosity level */
    srunner_run_all(runner, CK_VERBOSE);
    
    /* extracts results for exit code handling */
    int no_failed = srunner_ntests_failed(runner);
    
    /* free memory */
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}
/*** end of file ***/