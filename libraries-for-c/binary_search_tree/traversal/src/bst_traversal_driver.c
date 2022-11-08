// ------------------------------------------------------------------------------
//Lesson 7 Exercise:binary search tree traversal
//
//Print debug statements:Compile with - DDEBUG
// ------------------------------------------------------------------------------
//
#include <err.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

#include "binary_search_tree.h"

#define HALT_DEDUCTION 1
#define TEST_TOTAL 8
#define POINT_TOTAL 14
static const int point[TEST_TOTAL] = {2, 1, 1, 1, 1, 1, 1, 6};
static int testcount = 0;
static int pass = 0;
static int fail = 0;
static int *traversal_sequence = 0;
static int traversal_step = 0;
struct {
	int error_flag;
	int on_step;
	int on_key;
	tree *on_node;
} traversal_fail;
static const char *header =
"\n-------------------------------------------------------------------------------";
static const char *section =
"-----------------------------------section-------------------------------------";
static const char *footer =
"-------------------------------------------------------------------------------\n\n";

int *random_array(int n)
{
	//Return an array of n unique random numbers between 0 and n - 1.
	//
	//Initialize array from 0 to n - 1, then randomly permute to avoid duplicates.
	int *a = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		a[i] = i;
	}
	srand(0);
	int j;
	for (int i = 0; i < n; ++i) {
		j = rand() % n;
		int tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
	return a;
}

void test_size(tree * t, int sz)
{
	printf("Is the tree the expected size?\n");
	if (tree_size(t) == sz) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Size of tree = %d but should %d\n", tree_size(t), sz);

#ifdef DEBUG
		print(l);
#endif
	}
}

void test_traversal(tree * t,
		void (*fp) (tree *, void (*) (tree *)), void (*tp) (tree *),
		int size)
{
	traversal_step = 0;
	traversal_fail.error_flag = 0;
	traversal_fail.on_step = 0;
	traversal_fail.on_key = 0;
	traversal_fail.on_node = 0;
	fp(t, tp);
	if (traversal_fail.error_flag == 0) {
		if (traversal_step < size) {
			++fail;
			printf("\tFAIL! Traversal halted early on step %d instead of %d\n",
					traversal_step, size);
		} else {
			++pass;
			printf("\tPASS!\n");
		}
	} else {
		++fail;
		printf("\tFAIL! Traversal failed on step %d: Found node %d instead of %d\n",
				traversal_fail.on_step,
				traversal_fail.on_node->data,
				traversal_fail.on_key);
	}
}

double test_traversal_runtime(tree * t, void (*fp) (tree *, void (*) (tree *)),
		void (*tp) (tree *), double f){
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(t, tp);
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

double test_delete_runtime(tree * t, void (*fp) (tree **), double f){
	struct timeval t1;
	struct timeval t2;
	double time = 0.0;
	gettimeofday(&t1, 0);
	fp(&t);
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

void verify_node(tree * t, int v)
{
	if (t->data == v) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Node = %d but should %d\n", t->data, v);
#ifdef DEBUG
		print(l);
#endif
	}
}

void verify_traversal(tree * t)
{
	if (t->data != traversal_sequence[traversal_step]) {
		traversal_fail.error_flag = 1;
		traversal_fail.on_step = traversal_step;
		traversal_fail.on_key = traversal_sequence[traversal_step];
		traversal_fail.on_node = t;
	}
	++traversal_step;
}

void noop(tree * t)
{
	(void)t;
}

void report(void)
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
	const int BIGN = 100000;
	int a[] = {10, 12, 3, 8, 11, 14, 2, 5, 7, 9, 13, 15, 1, 4, 16, 30, 25, 22, 29, 38};
	int preorder_sequence[] =
	{
		6, 3, 2, 1, 5, 4, 10, 8, 7, 9, 12, 11, 14, 13, 15, 16, 30, 25, 22, 29, 38
	};
	int postorder_sequence[] =
	{
		1, 2, 4, 5, 3, 7, 9, 8, 11, 13, 22, 29, 25, 38, 30, 16, 15, 14, 12, 10, 6
	};
	int inorder_sequence[] =
	{
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 22, 25, 29, 30, 38
	};
	int levelorder_sequence[] =
	{
		6, 3, 10, 2, 5, 8, 12, 1, 4, 7, 9, 11, 14, 13, 15, 16, 30, 25, 38, 22, 29
	};
	int sz = 0;
	int tree_size = 0;

	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Create binary search tree with root node %d\n", 6);

	//Test.
	puts(section);
	tree *bst = create_node(6);
	sz = 1;

	//Verify size of tree.
	test_size(bst, sz);

	//Verify root node.
	printf("Is the root node correct?\n");
	verify_node(bst, 6);
	puts(footer);


	//New Test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Insert 10, 12, 3, 8, 11, 14, 2, 5, 7, 9, 13, 15, 1, 4, 16 ");
	printf("30, 25, 22, 29, 38\n");

	//Test.
	puts(section);
	for (unsigned int i = 0; i < sizeof(a) / sizeof(int); ++i) {
#ifdef DEBUG
		printf("Inserting node %d\n", i);
#endif
		insert(bst, create_node(a[i]));
	}
#ifdef DEBUG
	print(bst);
#endif
	sz = sz + sizeof(a) / sizeof(int);

	//Verify size of tree.
	test_size(bst, sz);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Preorder traversal\n");

	//Test.
	puts(section);
	traversal_sequence = &preorder_sequence[0];
	tree_size = sizeof(preorder_sequence) / sizeof(int);
	test_traversal(bst, &preorder, &verify_traversal, tree_size);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Postorder traversal\n");

	//Test.
	puts(section);
	traversal_sequence = &postorder_sequence[0];
	tree_size = sizeof(postorder_sequence) / sizeof(int);
	test_traversal(bst, &postorder, &verify_traversal, tree_size);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Inorder traversal\n");

	//Test.
	puts(section);
	traversal_sequence = &inorder_sequence[0];
	tree_size = sizeof(inorder_sequence) / sizeof(int);
	test_traversal(bst, &inorder, &verify_traversal, tree_size);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Levelorder traversal\n");

	//Test.
	puts(section);
	traversal_sequence = &levelorder_sequence[0];
	tree_size = sizeof(levelorder_sequence) / sizeof(int);
	test_traversal(bst, &levelorder, &verify_traversal, tree_size);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Destroy tree\n");

	//Test.
	puts(section);
	delete(&bst);

	//Verify size of tree.
	test_size(bst, 0);
	puts(footer);


	//New test.
	puts(header);
	printf("Test #%d:\n", ++testcount);
	printf("Performance tests\n");

	//Test.
	puts(section);
	printf("Time to create tree of %d nodes\n", BIGN);
	int *rarray = random_array(BIGN);
	gettimeofday(&t1, 0);
	bst = create_node(rarray[0]);
	for (int i = 1; i < BIGN; ++i) {
		insert(bst, create_node(rarray[i]));
	}
	gettimeofday(&t2, 0);
	time = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
	printf("Time: %f seconds\n", time);
	if (time < 0.1) {
		++pass;
		printf("\tPASS!\n");
	} else {
		++fail;
		printf("\tFAIL! Too slow\n");
	}
	free(rarray);

	//Test.
	puts(section);
	printf("Time for preorder traversal\n");
	time = test_traversal_runtime(bst, &preorder, &noop, 0.02);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time for postorder traversal\n");
	time = test_traversal_runtime(bst, &postorder, &noop, 0.02);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time for inorder traversal\n");
	time = test_traversal_runtime(bst, &inorder, &noop, 0.02);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time for levelorder traversal\n");
	time = test_traversal_runtime(bst, &levelorder, &noop, 0.05);
	printf("Time: %f seconds\n", time);

	//Test.
	puts(section);
	printf("Time to destroy tree\n");
	time = test_delete_runtime(bst, &delete, 0.05);
	printf("Time: %f seconds\n", time);
	puts(footer);

	//End of exercise.
	report();
}
