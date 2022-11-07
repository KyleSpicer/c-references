// ------------------------------------------------------------------------------
//Lesson 3 Exercise:singly linked list
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

#include "linkedlist.h"

#define HALT_DEDUCTION 1
#define TEST_TOTAL 10
#define POINT_TOTAL 20

static const int point[TEST_TOTAL] = {1, 2, 2, 2, 2, 2, 2, 2, 1, 4};
static int testcount = 0;
static int pass = 0;
static int fail = 0;
static const char *header =
"\n-------------------------------------------------------------------------------";
static const char *section =
"-----------------------------------section-------------------------------------";
static const char *footer =
"-------------------------------------------------------------------------------\n\n";

void test_size(list * l, int sz)
{
	printf("Is the list the expected size?\n");
	if (size(l) == sz) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Size of list = %d but should %d\n", size(l), sz);

#ifdef DEBUG
		print(l);
#endif
	}
}

double test_runtime(list * l, int (*fp) (void *), double f){
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(l);
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

double test_delete_runtime(list * l, void (*fp) (list **), double f){
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(&l);
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

double test_insert_runtime(list * l, list * n, int p,
		void (*fp) (list **, list *, int), double f)
{
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(&l, n, p);
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

void verify_node(list * l, list * n, int p, int v)
{
	if (n->data == v) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Node at position %d = %d but should %d\n", p, n->data, v);
#ifdef DEBUG
		print(l);
#else
		(void)l;
#endif
	}
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
	const int HALF_BIGN = BIGN >> 1;
	int sz = 0;
	list *node = 0;

	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Create list of size %d with keys 0 to %d\n", N, N - 1);

	//Test.
	puts(section);
	list *llist = create_node(0);
	for (int i = 1; i < N; ++i) {
#ifdef DEBUG
		printf("creating node %d\n", i);
#endif
		insert_back(llist, create_node(i));
	}

	//Verify size of list.
	test_size(llist, N);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Inserting node 13 at head position\n");

	//Test.
	puts(section);
	insert_front(&llist, create_node(13));

	//Verify size of list.
	sz = N + 1;
	test_size(llist, sz);

	//Verify head of list.
	printf("Is the head node correct?\n");
	verify_node(llist, llist, 0, 13);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Inserting node 14 at non-existent position %d\n", 30);

	//Test.
	puts(section);
	insert_at(&llist, create_node(14), 30);

	//Verify size of list.
	sz = sz + 1;
	test_size(llist, sz);

	//Verify position of new node.
	printf("Is the new node in the correct position?\n");
	node = llist;
	for (int i = 0; i < sz - 1; ++i) {
		node = node->next;
	}
	verify_node(llist, node, sz - 1, 14);
	puts(footer);


	//New Test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Inserting node 15 at position %d\n", 4);

	//Test.
	puts(section);
	insert_at(&llist, create_node(15), 4);

	//Verify size of list.
	sz = sz + 1;
	test_size(llist, sz);

	//Verify position of new node.
	printf("Is the new node in the correct position?\n");
	node = llist;
	for (int i = 0; i < 4; ++i) {
		node = node->next;
	}
	verify_node(llist, node, 4, 15);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Deleting node 15 at position %d\n", 4);

	//Test.
	puts(section);
	delete_at(&llist, 4);

	//Verify size of list.
	sz = sz - 1;
	test_size(llist, sz);

	//Verify deletion.
	printf("Has node 15 been deleted?\n");
	int found = 0;
	int p = 0;
	node = llist;
	for (int i = 0; i < sz - 1; ++i) {
		if (node->data == 15) {
			found = 1;
			break;
		}
		++p;
		node = node->next;
	}

	if (!found) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Node 15 found at position %d\n", p);

#ifdef DEBUG
		print(llist);
#endif
	}
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Deleting head node at position %d\n", 0);

	//Test.
	puts(section);
	delete_at(&llist, 0);

	//Verify size of list.
	sz = sz - 1;
	test_size(llist, sz);

	//Verify head of list.
	printf("Is the head node correct?\n");
	verify_node(llist, llist, 0, 0);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Deleting node at non-existent position %d\n", 30);

	//Test.
	puts(section);
	delete_at(&llist, 30);

	//Verify size of list.
	sz = sz - 1;
	test_size(llist, sz);

	//Verify tail of list.
	printf("Is the tail node correct?\n");
	node = llist;
	for (int i = 0; i < sz - 1; ++i) {
		node = node->next;
	}
	verify_node(llist, node, sz - 1, 9);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Deleting node at position %d\n", 7);

	//Test.
	puts(section);
	delete_at(&llist, 7);

	//Verify size of list.
	sz = sz - 1;
	test_size(llist, sz);

	//Verify deletion.
	printf("Was the correct node deleted?\n");
	node = llist;
	for (int i = 0; i < 7; ++i) {
		node = node->next;
	}
	verify_node(llist, node, 7, 8);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Destroy list\n");

	//Test.
	puts(section);
	delete(&llist);

	//Verify size of list.
	test_size(llist, 0);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Performance tests\n");

	//Test.
	puts(section);
	printf("Time to create list of %d nodes\n", BIGN);
	gettimeofday(&t1, 0);
	llist = create_node(0);
	list *tail = llist;
	for (int i = 1; i < BIGN; ++i) {
		insert_back(tail, create_node(i));
		tail = tail->next;
	}
	gettimeofday(&t2, 0);
	time = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	printf("Time: %f seconds\n", time);
	if (time < 0.05) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Too slow\n");
	}

	//Test.
	puts(section);
	printf("Time to get the size of the list\n");
	time = test_runtime(llist, (int (*) (void *))&size, 0.01);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to insert into middle\n");
	node = create_node(HALF_BIGN);
	time = test_insert_runtime(llist, node, HALF_BIGN, &insert_at, 0.01);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to destroy list\n");
	time = test_delete_runtime(llist, &delete, 0.01);
	printf("Time: %f seconds\n", time);
	puts(footer);

	//End of exercise.
	report();
}
