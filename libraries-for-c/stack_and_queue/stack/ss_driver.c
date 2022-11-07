// ------------------------------------------------------------------------------
//Lesson 4 Exercise:static stack
//
//Print debug statements:Compile with - DDEBUG
// ------------------------------------------------------------------------------
#include <err.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

#include "static_stack.h"

#define HALT_DEDUCTION 1
#define TEST_TOTAL 10
#define POINT_TOTAL 13
static const int point[TEST_TOTAL] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 4};
static int testcount = 0;
static int pass = 0;
static int fail = 0;
static const char *header =
"\n-------------------------------------------------------------------------------";
static const char *section =
"-----------------------------------section-------------------------------------";
static const char *footer =
"-------------------------------------------------------------------------------\n\n";

void test_empty(stack * s, int t)
{
	printf("Is stack empty? %s\n", empty(s) ? "true" : "false");
	if (empty(s) == t) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Empty returned = %d but should %d\n", empty(s), t);
	}
}

void test_top(stack * s, int t)
{
	if (top(s) == t) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Top of stack = %d but should %d\n", top(s), t);
	}
}

double test_runtime(stack * s, int (*fp) (void *), double f){
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(s);
	gettimeofday(&t2, 0);
	time = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	if (time < f) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Too slow\n");
	}
	return time;
}

void report()
{
	puts(header);
	printf("Final Report!\n");
	printf("Completed %d out of %d tests\n", testcount, TEST_TOTAL);
	printf("Total earned points = %d\n", pass);
	printf("Total possible points = %d\n", POINT_TOTAL);
	printf("Final score: %3.2f%%\n", (double)pass / POINT_TOTAL * 100);
	puts("");
	printf("Points distribution:\n");
	for (int i = 0; i < TEST_TOTAL; ++i) {
		printf("Problem #%d:\t%d points\n", i + 1, point[i]);
	}
	puts(footer);
}

void signal_handler(int signal, siginfo_t * info, void *context)
{
	(void)context;

	puts(header);
	puts("");
	printf("EXECUTION PREMATURELY HALTED!\n");
	printf("Caught signal (%d): %s\n", info->si_signo, strsignal(signal));
	printf("Fail at memory address: %p\n", info->si_addr);
	puts("");

	//Count incomplete tests.
	-- testcount;
	int remain = TEST_TOTAL - testcount;

	//Sum up remaining points.
	int skip = POINT_TOTAL - pass;

	//Point status.
	printf("Current points = %d\n", pass);
	printf("Missed points due to %d incomplete test(s) = %d\n", remain, skip);
	if (pass > 0)
		--pass;
	printf("Points after deducting %d point(s) for unexpected error = %d\n",
			HALT_DEDUCTION, pass);

	//Report
	report();
	exit(1);
}

int main(void)
{
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	struct sigaction sa;

	//Signal handling.
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);

	//Declarations specific to this exercise.
	const int N = 10;
	const int BIGN = 100000;

	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Create stack with capacity %d\n", N);

	//Test.
	puts(section);
	stack *sstack = create_stack(N);

	//Verify emptiness of stack.
	test_empty(sstack, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Push %d items with keys 0 to %d\n", N, N - 1);

	//Test.
	puts(section);
	for (int i = 0; i < N; ++i) {
#ifdef DEBUG
		printf("pushing item %d\n", i);
#endif
		push(sstack, i);
	}

	//Verify emptiness of stack.
	test_empty(sstack, 0);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Peek at the top of the stack\n");

	//Verify top of stack.
	puts(section);
	printf("Top should be %d\n", N - 1);
	test_top(sstack, N - 1);
	puts(footer);


	//New Test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Push one more than stack capacity of %d\n", N);

	//Test.
	puts(section);
	push(sstack, N + 1);

	//Verify top of stack.
	printf("Top should be %d\n", N - 1);
	test_top(sstack, N - 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Pop last item %d\n", top(sstack));

	//Test.
	puts(section);
	pop(sstack);

	//Verify top of stack.
	printf("Top should be %d\n", N - 2);
	test_top(sstack, N - 2);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Push item %d\n", N - 1);

	//Test.
	puts(section);
	push(sstack, N - 1);

	//Verify top of stack.
	printf("Top should be %d\n", N - 1);
	test_top(sstack, N - 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Pop until can't pop no more\n");

	//Test.
	puts(section);
	while (!empty(sstack)) {
#ifdef DEBUG
		printf("popping item %d\n", top(sstack));
#endif
		pop(sstack);
	}

	//Verify emptiness of stack.
	test_empty(sstack, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Pop from empty stack\n");

	//Test.
	puts(section);
	pop(sstack);

	//Verify emptiness of stack.
	test_empty(sstack, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Destroy stack\n");

	//Test.
	puts(section);
	delete_stack(&sstack);

	//Verify deletion.
	if (sstack == 0) {
		++pass;
		printf("\tPASS!\n");
	} else {
		printf("\tFAIL! Stack exists\n");
	}


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Performance tests\n");

	//Test.
	puts(section);
	printf("Time to create stack of %d items\n", BIGN);
	gettimeofday(&t1, 0);
	sstack = create_stack(BIGN);
	for (int i = 1; i < BIGN; ++i) {
		push(sstack, i);
	}
	gettimeofday(&t2, 0);
	time = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	printf("Time: %f seconds\n", time);
	if (time < 0.005) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Too slow\n");
	}

	//Test.
	puts(section);
	printf("Time to peek top of stack\n");
	time = test_runtime(sstack, (int (*) (void *))&empty, 0.0001);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to pop off stack\n");
	time = test_runtime(sstack, (int (*) (void *))&pop, 0.0001);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to destroy stack\n");
	gettimeofday(&t1, 0);
	delete_stack(&sstack);
	gettimeofday(&t2, 0);
	time = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	printf("Time: %f seconds\n", time);
	if (time < 0.005) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Too slow\n");
	}
	puts(footer);

	//End of exercise.
	report();
}
