// ------------------------------------------------------------------------------
//Lesson 4 Exercise:static queue
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

#include "static_queue.h"

#define HALT_DEDUCTION 1
#define TEST_TOTAL 11
#define POINT_TOTAL 15

static const int point[TEST_TOTAL] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 4};
static int testcount = 0;
static int pass = 0;
static int fail = 0;
static const char *header =
"\n-------------------------------------------------------------------------------";
static const char *section =
"-----------------------------------section-------------------------------------";
static const char *footer =
"-------------------------------------------------------------------------------\n\n";

void test_empty(queue * q, int t)
{
	printf("Is queue empty? %s\n", empty(q) ? "true" : "false");
	if (empty(q) == t) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Empty returned = %d but should %d\n", empty(q), t);
	}
}

void test_front(queue * q, int t)
{
	if (front(q) == t) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Front of queue = %d but should %d\n", front(q), t);
	}
}

double test_runtime(queue * q, int (*fp) (void *), double f){
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(q);
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
	printf("Create queue with capacity %d\n", N);

	//Test.
	puts(section);
	queue *squeue = create_queue(N);

	//Verify emptiness of queue.
	test_empty(squeue, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Enqueue %d items with keys 0 to %d\n", N, N - 1);

	//Test.
	puts(section);
	for (int i = 0; i < N; ++i) {
#ifdef DEBUG
		printf("inserting item %d\n", i);
#endif
		insert(squeue, i);
	}

	//Verify emptiness of queue.
	test_empty(squeue, 0);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Peek at the front of the queue\n");

	//Verify front of queue.
	puts(section);
	printf("Front should be %d\n", 0);
	test_front(squeue, 0);
	puts(footer);


	//New Test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Enqueue one more than queue capacity of %d\n", N);

	//Test.
	puts(section);
	insert(squeue, N + 1);

	//Verify front of queue.
	printf("Front should be %d\n", 0);
	test_front(squeue, 0);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Dequeue first item %d\n", front(squeue));

	//Test.
	puts(section);
	extract(squeue);

	//Verify front of queue.
	printf("Front should be %d\n", 1);
	test_front(squeue, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Equeue item %d\n", 0);

	//Test.
	puts(section);
	insert(squeue, 0);

	//Verify front of queue.
	printf("Front should be %d\n", 1);
	test_front(squeue, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Dequeue until can't dequeue no more\n");

	//Test.
	puts(section);
	while (!empty(squeue)) {
#ifdef DEBUG
		printf("extracting item %d\n", front(squeue));
#endif
		extract(squeue);
	}

	//Verify emptiness of queue.
	test_empty(squeue, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Dequeue from empty queue\n");

	//Test.
	puts(section);
	extract(squeue);

	//Verify emptiness of queue.
	test_empty(squeue, 1);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Reset queue and enqueue first item\n");

	//Test.
	puts(section);
	reset(squeue);

	//Verify emptiness of queue.
	test_empty(squeue, 1);

	//Test.
	puts(section);
	printf("Equeue item %d\n", 15);
	insert(squeue, 15);

	//Verify front of queue.
	printf("Front should be %d\n", 15);
	test_front(squeue, 15);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Destroy queue\n");

	//Test.
	puts(section);
	delete_queue(&squeue);

	//Verify deletion.
	if (squeue == 0) {
		++pass;
		printf("\tPASS!\n");
	} else {
		printf("\tFAIL! Queue exists\n");
	}


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Performance tests\n");

	//Test.
	puts(section);
	printf("Time to create queue of %d items\n", BIGN);
	gettimeofday(&t1, 0);
	squeue = create_queue(BIGN);
	for (int i = 1; i < BIGN; ++i) {
		insert(squeue, i);
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
	printf("Time to peek top of queue\n");
	time = test_runtime(squeue, (int (*) (void *))&empty, 0.0001);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to pop off queue\n");
	time = test_runtime(squeue, (int (*) (void *))&extract, 0.0001);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to destroy queue\n");
	gettimeofday(&t1, 0);
	delete_queue(&squeue);
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

	return 0;
}
