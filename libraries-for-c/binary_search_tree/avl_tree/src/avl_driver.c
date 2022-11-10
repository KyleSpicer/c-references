#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main()
{
    int nums[] =
	    { 24, 29, 25, 49, 37, 7, 2, 3, 23, 9, 41, 16, 43, 22, 21, 27, 39,
       35, 42, 28 };

	int nums_size = sizeof(nums) / sizeof(int);

    // create root node
    tree * root = create_node(nums[0]);

    // loop for adding remaining elements to avl tree
    for (int i = 1; i < nums_size; i++) {
        tree * temp = create_node(nums[i]);
        avl_insert(root, temp);
    }
    
    // print avl tree
    printf("\n\nOriginal Tree\n");
    printvisual(root);

    // int rand_nums[] = {1, 25, 35, 21, 39, 42, 49, 22, 2, 41, 3, 37, 24, 7, 
	// 28, 16, 9, 23, 43, 29};

    // // remove elements to zero
	// //
	// for(int i = 0; i < nums_size; i++)
	// {
	// 	printf("\n");
	// 	printf("deleting node: %d\n", rand_nums[i]);
	// 	delete_node(&root, rand_nums[i]);
	// 	printvisual(root);
	// 	printf("tree size = %d\n", size(root));
	// }

    delete(&root);
}