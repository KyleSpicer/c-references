#include "kd_bst.h"
#include "llist.h"
#include "spice_file_io.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <float.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 64
#define SIZENUM 4

// #if (double == 0)
// #if (fabs(double) < DBL_EPSILON)

void stack_print(tree * node)
{
	if (!node) {
		return;
	}

	printf("Node: (%f, %f) distance is %f\n", node->x_coord,
	       node->y_coord, node->distance);
}

void stack_destroy(llist_t * stack)
{
	if(!stack) {
		return;
	}
	stack = NULL;
}

int main(int argc, char *argv[])
{
	// struct for get opt long options
	int option_index = 0;
	static struct option long_options[] = {
		{"file", required_argument, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
		{"distance", required_argument, NULL, 'd'}
	};

	char *file_name = NULL;

	// while loop for switch cases
	int opt = 0;
	while ((opt =
		getopt_long(argc, argv, "hf:", long_options,
			    &option_index)) != -1) {
		switch (opt) {
		case 'h':	// help option
			printf("help message\n");
			exit(1);
			break;

		case 'f':	// file option
			file_name = optarg;	// placing user provided file name in var
			break;

		case 'd':	// distance
			// distance provided by user
			break;

		case '?':	// unknown operators handling
			// help / usage statement
			exit(1);
			break;

		default:
			break;
		}
	}

	// open and verify file
	FILE *fp = file_open_and_verify(file_name);
	if (!fp) {
		printf("Unable to open %s\n", file_name);
		exit(1);
	}

	tree *root = NULL;	// create root
	char buffer[MAXCHAR] = { '\0' };	// buffer for incoming line 

	printf("\nCoordinates: \n");
	// cycle through csv and grab each line
	while (fgets(buffer, MAXCHAR, fp) != 0) {
		int len = strnlen(buffer, MAXCHAR) - 1;
		// replacing newline with NULL
		if ('\n' == buffer[len]) {
			buffer[len] = '\0';
		}
		// passes over first line in file, if not digits
		if (!isdigit(*buffer)) {
			continue;
		}

		char *coords = NULL;
		// to hold first portion of line (x val)
		double x_coor = strtod(buffer, &coords);
		if (',' != *coords) {
			break;
		}
		// to hold second portion of line (y val)
		double y_coor = strtod(coords + 1, &coords);
		if ('\0' != *coords) {
			break;
		}
		// printf("(x: %.1f, y: %.1f)\n", x_coor, y_coor);

		tree *new_node = kd_create_node(x_coor, y_coor);
		if (!root) {
			root = new_node;
			root->number_nodes += 1;

		} else {
			// inserting node into KD tree
			kd_tree_insert(root, new_node, 0);
			root->number_nodes += 1;
		}
	}

////////////////////////////////////////////////////////////////////////////////

	// printf("\nPopulated KD Tree: \n");
	// printvisual(root);

	printf("\n------ START FUNCTION CHECKS ------\n\n");

	printf("Total nodes in tree: %d\n", root->number_nodes);

	tree *minnode = minimum(root);
	printf("Smallest Node = (%0.f, %0.f)\n", minnode->x_coord,
	       minnode->y_coord);

	tree *maxnode = maximum(root);
	printf("Largest Node  = (%0.f, %0.f)\n", maxnode->x_coord,
	       maxnode->y_coord);

////////////////////////////////////////////////////////////////////////////////

	printf("\n------ CHECKING NEAREST NEIGHBOR FUNCTION ------\n\n");
	llist_t *stack = llist_create();
	tree *nearest_node =
	    kd_tree_nearest_neighbor(root, 18.334138,-66.066365, 10, stack, 0);

	llist_print(stack, (void (*)(void *))stack_print);

	printf("\n------ END OF CHECKS ------\n\n");

////////////////////////////////////////////////////////////////////////////////
	destroy_kd_tree(&root);
	llist_destroy(&stack, (void (*)(void *))stack_destroy);
	fclose(fp);

}

/*** end of file ***/
