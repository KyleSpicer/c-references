// ------------------------------------------------------------------------------
//Lesson 6 Exercise:binary search tree
// ------------------------------------------------------------------------------
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct tree {
	struct tree *parent;
	struct tree *left;
	struct tree *right;
	int data;
};
typedef struct tree tree;

tree *create_node(int value);
tree *insert(tree * search_tree, tree * new_node);
tree *search(tree * root, int data);
tree *minimum(tree * root);
tree *maximum(tree * root);
int size(tree * root);
void print(tree * root);
tree *delete_node(tree ** root, int data);
void delete(tree ** root);



#endif
