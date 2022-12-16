#include "kd_bst.h"
#include "spice_file_io.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <float.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXCHAR 64
#define SIZENUM 4

int main(int argc, char *argv[])
{
	// struct for get opt long options
	int option_index = 0;
	static struct option long_options[] = {
		{"file", required_argument, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
		{"distance", required_argument, NULL, 'd'},
		{"lat", required_argument, NULL, 'x'},
		{"lon", required_argument, NULL, 'y'},
		{"number", required_argument, NULL, 'k'}
	};

	char *arguments = NULL;
	char *file_name = NULL;
	char *user_lat = NULL;
	char *user_lon = NULL;
	char *radius = NULL;
	char *node_number = NULL;
	double user_radius = 0;
	double user_x = DBL_MAX;
	double user_y = DBL_MAX;
	double user_node_amount = 0;
	int opt = 0;

	while ((opt =
		getopt_long(argc, argv, "hf:d:x:y:k:", long_options,
			    &option_index)) != -1) {
		switch (opt) {
		case 'h':
			display_usage_statement();
			exit(1);
			break;

		case 'f':
			file_name = optarg;	// placing user provided file name in var
			break;

		case 'd':	// distance
			radius = optarg;
			user_radius = strtod(radius, &arguments);
			break;

		case 'x':
			user_lat = optarg;
			user_x = strtod(user_lat, &arguments);
			break;

		case 'y':
			user_lon = optarg;
			user_y = strtod(user_lon, &arguments);
			break;

		case 'k':
			node_number = optarg;
			user_node_amount = strtod(node_number, &arguments);
			printf("node amount = %f\n", user_node_amount);
			break;

		case '?':	// unknown operators handling
			printf("Unknown Arguments: %s\n", optarg);
			display_usage_statement();
			exit(1);
			break;

		default:
			display_usage_statement();
			exit(1);
			break;
		}
	}

	// if not provided, exit
	if (!file_name || !user_lat || !user_lon || !radius) {
		printf("\nNot enough arguments to complete program.\n");
		display_usage_statement();
		exit(1);
	}
	// open and validate file
	FILE *fp = file_open_and_verify(file_name);
	if (!fp) {
		printf("Unable to open %s\n", file_name);
		exit(1);
	}

	tree *root = NULL;	// create root
	char buffer[MAXCHAR] = { '\0' };	// buffer for incoming line 

	// cycle through csv and grab each line
	while (fgets(buffer, MAXCHAR, fp) != 0) {
		int len = strnlen(buffer, MAXCHAR) - 1;
		// replacing newline with NULL
		if ('\n' == buffer[len]) {
			buffer[len] = '\0';
		}
		// passes over line in file, if not digits
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

	// printf("\nPopulated KD Tree: \n");
	// printvisual(root);

	printf("\n------ CHECKING NEAREST NEIGHBOR FUNCTION ------\n\n");

	tree *array;		// basic container for array
	array = calloc(root->number_nodes, sizeof(tree));
	if (!array) {
		printf("Unable to create array.\n");
		exit(1);
	}

	kd_tree_nearest_neighbor(root, user_x, user_y, user_radius, 0, array);

	// array sorting function

	for (int i = 0; i < (int)user_node_amount; i++) {
		if (!array[i].x_coord) {
			continue;
		}
		printf("#%d - Node: x: %f, y: %f is a distance of %f\n", i + 1,
		       array[i].x_coord, array[i].y_coord, array[i].distance);
	}

	printf("\n------ END OF CHECKS ------\n\n");

	destroy_kd_tree(&root);
	free(array);
	fclose(fp);
}

/*** end of file ***/
