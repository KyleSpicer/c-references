/**
 * @file unit_testing.c
 * @author CW2 Kyle Spicer
 * @brief shell to create and start simple unit testing in C
 * @version 0.1
 * @date 2022-11-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// reference for testing
// https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

#include <check.h> // library for unit testing in C
#include <stdio.h>
#include <stdlib.h>

// step 1: create main with proper logic 
// step 2: create Suite
// step 3: create tests

START_TEST(test_func_1)
{
    // complete logic for function
    // use ck_something to run test.
    // reference libcheck url for examples and functions to use
}END_TEST


START_TEST(test_func_1)
{
    // complete logic for function
    // use ck_something to run test.
    // reference libcheck url for examples and functions to use

}END_TEST

Suite *check_my_program_suite(void)
{
    Suite *suite;
	TCase *tc_core;

	// Creates the initial suite, because you kind of just need it
	//
	suite = suite_create("my_program_test");

	// Confirms successful creation/deletion of structure before continuing
	// to ensure proper handling prior to next Test Cases
	//
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_func_1);
	tcase_add_test(tc_core, test_func_2);
	suite_add_tcase(suite, tc_core);

	return suite;
}

int main(void)
{
	// Instantiate and initialize the Suite Runner
	//
	// If additional Test Suites are desired, add with srunner_add_suite()
	// Generally speaking:
	// - Suite Runner is responsibile testing entire program
	// - 1x Test Suite per library
	// - 1+ Test Cases per logical "section"
	// - Multiple Unit Tests per function
	//
	// The Test Cases and Unit Tests are logical groupings of things, so you
	// could say "This Test Case handles file open and validation functions"
	//
	// Other developers prefer to chunk their thoughts out differently,
	// "This Test Cases are responsible for testing ALL my functions on
	// invalid input"
	//
	Suite *suite = check_my_program_suite(); // ex: test_calculator_suite
	SRunner *runner = srunner_create(suite);

	// Prevents valigrind errors from appearing that could be mistakenly be
	// considered the programmers fault. Will run slower! For details, see:
	//
	// https://libcheck.github.io/check/doc/check_html/check_4.html#Finding-Memory-Leaks
	//
	srunner_set_fork_status(runner, CK_NOFORK);

	// Actual Suite Runner command of execution with desired verbosity level
	//
	srunner_run_all(runner, CK_VERBOSE);

	// Extract results for exit code handling
	//
	int no_failed = srunner_ntests_failed(runner);

	// free() all resources used for execution of Suite Runner.
	// Documentation mentions it also cleans up for Test Cases, but that
	// appears to be just THEIR portion, you are still responsible for
	// cleaning up after yourself
	//
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}