/**
 * @file binary_search_tree.h
 * @author Kyle Spicer
 * 
 * @brief holds prototypes and tree struct definition for use 
 * within binary_search_tree.c
 * 
 * @date 2022-11-08
 * 
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct tree tree;

/**
 * @brief Create a node object
 * 
 * @param value - int data to store within node
 * @return tree* 
 */
static tree *tree_create(); // returns pointer to wrapper structure

/**
 * @brief inserts new node into tree struct
 * 
 * @param search_tree 
 * @param new_node 
 * @return tree* 
 */
tree *tree_insert(tree * root, void * data, int (*compare_data)(void *initial, void *comparison));

/**
 * @brief searches tree for specified node and returns data
 * 
 * @param root - root node
 * @param data - data you are looking to retrieve in tree
 * @return tree* 
 */
tree *tree_search(tree * root, void * data);

/**
 * @brief returns leftmost path from root to leaf
 * 
 * @param root 
 * @return tree* 
 */
tree *tree_minimum(tree * root);

/**
 * @brief Maximum must be in the rightmost path from root to leaf.
 * 
 * @param root 
 * @return tree* 
 */
tree *tree_maximum(tree * root);

/**
 * @brief returns the approximate number of nodes within tree
 * 
 * @param root 
 * @return int 
 */
int tree_size(tree * root);

/**
 * @brief prints root, left, and right node of called node
 * 
 * @param root 
 */
void tree_print(tree * root);

/**
 * @brief frees and returns specified node
 * 
 * @param root 
 * @param data 
 * @return tree* 
 */
tree *delete_tree(tree ** root, void * data);

/**
 * @brief deletes tree, frees point to struct, sets mem address to NULL
 * 
 * @param root 
 */
void destroy_tree(tree ** root);

/**
 * @brief processes a node then recurses down the left subtree before
 * recursing down the right subtree.
 * 
 * @param root 
 * @param action_func 
 */
void preorder(tree * root, void (*action_func)(void *));

/**
 * @brief recurses down the left subtree of a node before recursing down the
 * right subtree, then processes the node.
 * 
 * @param root 
 * @param action_func 
 */
void postorder(tree * root, void (*action_func)(void *));

/**
 * @brief recurses down the left subtree of a node then processes the 
 * node before recursing down the right subtree.
 * 
 * @param root 
 * @param action_func 
 */
void inorder(tree * root, void (*action_func)(void *));

/**
 * @brief processes every node in a level before descending to the next
 * level. Requires a queue struct.
 * 
 * @param root 
 * @param action_func 
 */
void levelorder(tree* root, void (*action_func)(void *));

void print_visual(tree *root);

int array_int_sort(const void * data1, const void * data2);

#endif /* BINARY_SEARCH_TREE_H */
/*** end of file ***/

