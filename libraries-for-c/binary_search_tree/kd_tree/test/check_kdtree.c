/**
 * @file check_kdtree.c
 * @author CW2 Kyle Spicer
 * @brief provides robust automated unit testing to verify functions work properly and
 * identifies potential edge cases.
 * 
 * @date 2022-12-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <check.h>		// library for unit testing in C
#include <stdio.h>
#include <stdlib.h>
#include "../src/kd_bst.h"

START_TEST(test_create_node)
{
    tree * valid_test_tree  = create_node(5.22, 6.23);
    ck_assert(valid_test_tree->x_coord == 5.22);
    ck_assert(valid_test_tree->y_coord == 6.23);

}

Suite * check_my_program_suite(void)
{
	Suite *suite;
	TCase *tc_core;

	// Creates the initial suite, because you kind of just need it
	//
	suite = suite_create("kdtree_unit_testing");

	// Confirms successful creation/deletion of structure before continuing
	// to ensure proper handling prior to next Test Cases

	tc_core = tcase_create("tc_kdtree_funcs");
	tcase_add_test(tc_core, test_create_node);


	suite_add_tcase(suite, tc_core);

	return suite;
}

int main(void)
{

	Suite *suite = check_my_program_suite();	// ex: test_calculator_suite
	SRunner *runner = srunner_create(suite);

	// Prevents confusing valigrind errors from appearing 
	srunner_set_fork_status(runner, CK_NOFORK);

	// Actual Suite Runner command of execution with desired verbosity level
	srunner_run_all(runner, CK_VERBOSE);

	// Extract results for exit code handling
	int no_failed = srunner_ntests_failed(runner);

	// free() all resources used for execution of Suite Runner.
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/*** end of file ***/
