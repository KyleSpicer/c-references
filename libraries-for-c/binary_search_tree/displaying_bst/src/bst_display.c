#include <stdio.h>

#include "binary_search_tree.h"

#define NUMS 20

int main()
{
	int nums[NUMS] =
	    { 24, 29, 25, 49, 37, 7, 2, 3, 23, 9, 41, 16, 43, 22, 21, 27, 39,
       35, 42, 28 };
	int nums_size = sizeof(nums) / sizeof(int);

	tree *root = create_node(nums[0]);

	for (int i = 1; i < nums_size; i++) {
		tree *temp = create_node(nums[i]);
		insert(root, temp);
	}
	// print statement
	printvisual(root);

	delete(&root);
}
