#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"
#include "llist.h"

tree *create_node(int value)
{
	if (!value) {
		return NULL;
	}
	tree *new_node;
	new_node = calloc(1, sizeof(tree));
	new_node->data = value;

	return new_node;
}

tree *insert(tree * root, tree * new_node)
{
	if (!root || !new_node) {
		return NULL;
	}
	if (new_node->data < root->data) {
		if (root->left == 0) {
			root->left = new_node;
			new_node->parent = root;
			return new_node;
		}
	} else {
		if (root->right == 0) {
			root->right = new_node;
			new_node->parent = root;
			return new_node;
		}
	}
	tree *new = (new_node->data < root->data) ? root->left : root->right;
	return (insert(new, new_node));
}

tree *search(tree * root, int data)
{
	if (!root || !data) {
		return NULL;
	}
	if (root == 0 || root->data == data) {
		return root;
	}
	tree *n = (data < root->data) ? root->left : root->right;
	return search(n, data);
}

tree *minimum(tree * root)
{
	//Minimum must be in the leftmost path from root to leaf.
	if (!root) {
		return NULL;
	}

	if (root->left == 0) {
		return root;
	}
	return minimum(root->left);
}

tree *maximum(tree * root)
{
	//Maximum must be in the rightmost path from root to leaf.
	if (!root) {
		return NULL;
	}

	if (root->right == 0) {
		return root;
	}
	return maximum(root->right);
}

int tree_size(tree * root)
{
	if (!root) {
		return 0;
	}

	int sum = 1;
	sum += tree_size(root->left);
	sum += tree_size(root->right);
	return sum;
}

void print(tree * root)
{
	// pre-order traversal
	if (!root) {
		return;
	}

	if (root != 0) {
		int left = 0;
		int right = 0;
		if (root->left) {
			left = root->left->data;
		}
		if (root->right) {
			right = root->right->data;
		}
		printf("parent = %d, left = %d, right = %d\n", root->data, left,
		       right);
		print(root->left);
		print(root->right);

	}
}

tree *delete_node(tree ** root, int data)
{
	if (!*root || !root || !data) {
		return NULL;
	}
	//Return parent of deleted node except:
	//
	// 1. if deleted node does not exist then return null
	// 2. if deleted node is the root then return new root

	tree *node = search(*root, data);
	tree *temp = 0;
	if (node == 0) {
		return *root;
	}
	//Root node.
	//
	//Treat special because root has no parent to relink.
	//
	//Only need special handling for:
	//
	// i. no children
	// ii.one child
	if (node->parent == 0) {
		if (node->left == 0 && node->right == 0) {
			free(node);
			*root = 0;
			return *root;
		}
		if (node->left || node->right == 0) {
			temp = (node->left == 0) ? node->right : node->left;
			temp->parent = 0;
			free(node);
			*root = temp;
			return *root;
		}
	}
	//Replace deleted node with the minimum of its right branch.
	//
	//If missing the right branch then replace with the left branch, treating
	// leaf nodes in the same manner.
	//
	//The minimum node cannot have a left child.
	//
	//But the minimum node can be the right child of the deleted node so replace
	// deleted node 's data with the minimum after testing if the minimum is its
	// right child.
	//
	//NOTE:    If a leaf or missing right branch, then saving the node and copying
	// its data is extraneous but minimal work overall.

	tree *x = node;
	temp = node->left;
	if (node->right != 0) {
		node = minimum(node->right);
		temp = node->right;
	}
	if (node->data > node->parent->data) {
		// right child
		node->parent->right = temp;
	} else {
		// left child
		node->parent->left = temp;
	}
	if (temp != 0) {
		temp->parent = node->parent;
	}
	x->data = node->data;
	temp = node->parent;
	free(node);
	return temp;
}

void delete(tree ** root)
{
	if (!root || !*root) {
		return;
	}

	//tree *left = (*root)->left;
	//tree *right = (*root)->right;
	//free(*root);
	//*root = 0;
	delete(&((*root)->left));
	delete(&((*root)->right));
	free(*root);
	*root = NULL;
}

void preorder(tree * root, void (*action_func)(tree *))
{
	if (!root) {
		return;
	}

	action_func(root);
	preorder(root->left, action_func);
	preorder(root->right, action_func);
}

void postorder(tree * root, void (*action_func)(tree *))
{
	if (!root) {
		return;
	}
	postorder(root->left, action_func);
	postorder(root->right, action_func);
	action_func(root);
}

void inorder(tree * root, void (*action_func)(tree *))
{
	if (!root) {
		return;
	}
	inorder(root->left, action_func);
	action_func(root);
	inorder(root->right, action_func);

}

void levelorder(tree * root, void (*action_func)(tree *))
{
	if (!root) {
		return;
	};
	// create queue
	llist_t * queue = llist_create();
	enqueue(queue, root);

	while(0 < list_size(queue)){
		root = dequeue(queue);
		if (root) {
			action_func(root);
			enqueue(queue, root->left);
			enqueue(queue, root->right);
		} else {
			printf("We got a null from dequeue\n");
		}

	}
	llist_destroy(&queue, free);
}


/*** end of file ***/
