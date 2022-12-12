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

int main(int argc, char *argv[])
{
	// struct for get opt long options
	int option_index = 0;
	static struct option long_options[] = {
		{"file", required_argument, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
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

		case '?':	// unknown operators entered
			exit(1);
			break;

		default:
			break;
		}
	}

	// open and verify file
	FILE *fp = file_open_and_verify(file_name);
	if (!fp) {
		printf("nothing\n");
		exit(1);
	}

	int level = 2;

	tree *root = NULL;

	// create root
	char buff[MAXCHAR] = { '\0' };
	printf("\nCoordinates: \n");
	while (fgets(buff, MAXCHAR, fp) != 0) {
		int len = strnlen(buff, MAXCHAR) - 1;
		if ('\n' == buff[len]) {
			buff[len] = '\0';
		}

		if (!isdigit(*buff)) {	// skips over first line in file
			continue;
		}

		char *broken = NULL;
		double x_coor = strtod(buff, &broken);
		if (',' != *broken) {
			break;
		}

		double y_coor = strtod(broken + 1, &broken);
		if ('\0' != *broken) {
			break;
		}

		printf("(x: %.1f, y: %.1f)\n", x_coor, y_coor);

		tree *new_node = create_node(x_coor, y_coor, level);


		if (!root) {
			root = new_node;
    		level++;
			root->number_nodes += 1;

		} else {
			kd_tree_insert(root, new_node, 0);
			root->number_nodes += 1;
	    }
	}

	//////// VERIFYING FUNCTIONS AND VARIABLES HOLD CORRECT VALUES ////////////
    // printf("levels = %d\n", level - 2);
	// int nodecount = kd_tree_size(root);
	// printf("Number of nodes = %d\n", nodecount);
	// bool isitempty = kd_tree_is_empty(root);
	// printf("Is KD Tree Empty? %d\n", isitempty);

	// printf("Before inserting new node:\n");
    // printvisual(root);
	// tree * newnode = (create_node(15, 20, 2));
	// kd_tree_insert(root, newnode);
	// tree * anothernode = (create_node(1, 3, 2));
	// kd_tree_insert(root, anothernode);

	
	printvisual(root);
	
	// not valid
	tree * searched = search(root, 2, 4, 0);
	if(!searched) {
		printf("(%d, %d) does not exist.\n", 2, 4);
	}
	
	tree * rootsearch = search(root, 2, 3, 0);
	if(rootsearch){
		printf("(%0.f, %0.f) exists.\n", rootsearch->x_coord, rootsearch->y_coord);		
	}

	tree *randsearch = search(root, 1, 4, 0);
	if(randsearch) {
		printf("(%0.f, %0.f) exists.\n", randsearch->x_coord, randsearch->y_coord);		
	}
	
    delete(&root);
	fclose(fp);

}

/*** end of file ***/
