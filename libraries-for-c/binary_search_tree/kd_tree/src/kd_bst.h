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

#include <stdbool.h>
#include <limits.h>
#include "llist.h"

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct tree tree;

struct tree {
	struct tree *parent;
	struct tree *left;
	struct tree *right;
	double x_coord;
	double y_coord;
	double distance;
	int number_nodes;

};

typedef struct element_t element_t;

/**
 * @brief Create a node object
 * 
 * @param value - int data to store within node
 * @return tree* 
 */
tree *kd_create_node(double x, double y);

/**
 * @brief inserts new node into tree struct
 * 
 * @param search_tree 
 * @param new_node 
 * @return tree* 
 */
tree *kd_tree_insert(tree * search_tree, tree * new_node, int method);

/**
 * @brief searches tree for specified node and returns data
 * 
 * @param root - root node
 * @param data - data you are looking to retrieve in tree
 * @return tree* 
 */
tree *search(tree * root, double x_val, double y_val, int method);

tree *remove_node(tree * root, tree * node_to_remove);

void printvisual(tree * root);

int kd_tree_size(tree * root);

bool kd_tree_is_empty(tree * root);

void destroy_kd_tree(tree ** root);

tree *minimum(tree * root);

tree *maximum(tree * root);

tree *kd_tree_remove_node(tree ** root, double x_val, double y_val);

double find_distance(double x1, double x2, double y1, double y2);

// returns the closest KD Tree element to the coordinates provided.
tree *kd_tree_nearest_neighbor(tree * root, double x, double y, double radius,
			       llist_t * stack, int method);

// void preorder(tree * root, void (*action_func)(tree *));
// void postorder(tree * root, void (*action_func)(tree *));
// void inorder(tree * root, void (*action_func)(tree *));
// void levelorder(tree * root, void (*action_func)(tree *));

#endif				/* BINARY_SEARCH_TREE_H */

/*** end of file ***/
