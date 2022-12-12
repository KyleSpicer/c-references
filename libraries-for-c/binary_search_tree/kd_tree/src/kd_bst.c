/**
 * @file binary_search_tree.c
 * @author Kyle Spicer
 * 
 * @brief defines functions prototyped in binary_search_tree.h
 * 
 * @date 2022-11-08
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "kd_bst.h"
#include "llist.h"
#include "spice_file_io.h"

tree *create_node(double x, double y, int level)
{
	if (!x || !y || !level) {
		return NULL;
	}
	tree *new_node;
	new_node = calloc(1, sizeof(tree));
	new_node->x_coord = x;
	new_node->y_coord = y;
	new_node->level = level;

	return new_node;
}

tree *kd_tree_insert(tree * root, tree * new_node, int method)
{
	if (!root || !new_node) {
		return NULL;
	}
	tree *new = NULL;

	// if level is even, comp x
	if (0 == method % 2) {
		if (root->x_coord > new_node->x_coord) {
			if (!root->left) {
				root->left = new_node;
				new_node->parent = root;
				return new_node;
			}

		}
		// new node x is larger than root
		else {
			if (!root->right) {
				root->right = new_node;
				new_node->parent = root;
				return new_node;
			}

		}
		new =
		    (new_node->x_coord <
		     root->x_coord) ? root->left : root->right;

	}
	// // if level is odd, comp y
	else {
		if (root->y_coord > new_node->y_coord) {
			if (!root->left) {
				root->left = new_node;
				new_node->parent = root;
				return new_node;
			}

		}

		else {
			if (!root->right) {
				root->right = new_node;
				new_node->parent = root;
				return new_node;
			}
		}
		new =
		    (new_node->y_coord <
		     root->y_coord) ? root->left : root->right;

	}
	return (kd_tree_insert(new, new_node, ++method));

}

tree *search(tree * root, double x_val, double y_val, int method)
{
	if (!root) {
		return NULL;
	}	

	// check root values first, if match, retun root
	if (root->x_coord == x_val
	    && root->y_coord == y_val) {
		return root;
	}

	// // if level is even, comp x values
	else if (!method) {
		if (root->x_coord > x_val) {
		
			return search(root->left, x_val, y_val, !method);
		}
		return search(root->right, x_val, y_val, !method);
	}
	// // if level is odd, comp y value
	else {
		if (root->y_coord > y_val) {
			return search(root->left, x_val, y_val, !method);
		}
		return search(root->right, x_val, y_val, !method);
	}
}

// tree *minimum(tree * root)
// {
//      //Minimum must be in the leftmost path from root to leaf.
//      if (!root) {
//              return NULL;
//      }

//      if (root->left == 0) {
//              return root;
//      }
//      return minimum(root->left);
// }

// tree *maximum(tree * root)
// {
//      //Maximum must be in the rightmost path from root to leaf.
//      if (!root) {
//              return NULL;
//      }

//      if (root->right == 0) {
//              return root;
//      }
//      return maximum(root->right);
// }

// int tree_size(tree * root)
// {
//      if (!root) {
//              return 0;
//      }

//      int sum = 1;
//      sum += tree_size(root->left);
//      sum += tree_size(root->right);
//      return sum;
// }

// void print(tree * root)
// {
//      // pre-order traversal
//      if (!root) {
//              return;
//      }

//      if (root != 0) {
//              int left = 0;
//              int right = 0;
//              if (root->left) {
//                      left = root->left->data;
//              }
//              if (root->right) {
//                      right = root->right->data;
//              }
//              printf("parent = %d, left = %d, right = %d\n", root->data, left,
//                     right);
//              print(root->left);
//              print(root->right);

//      }
// }

// tree *delete_node(tree ** t, int d)
// {
//      // Return parent of deleted node except:
//   //
//   // 1. if deleted node does not exist then return null
//   // 2. if deleted node is the root then return new root
//   tree* node = search(*t, d);
//   tree* tmp = 0;
//   if (node == 0) return *t;

//   // Root node.
//   //
//   // Treat special because root has no parent to relink.
//   //
//   // Only need special handling for:
//   //
//   // i. no children
//   // ii. one child
//   if (node->parent == 0)
//   {
//     if (node->left == 0 && node->right == 0)
//     {
//       free(node);
//       *t = 0;
//       return *t;
//     }
//     if (node->left == 0 || node->right == 0)
//     {
//       tmp = (node->left == 0) ? node->right : node->left;
//       tmp->parent = 0;
//       free(node);
//       *t = tmp;
//       return *t;
//     }
//   }

//   // Replace deleted node with the minimum of its right branch.
//   //
//   // If missing the right branch then replace with the left branch, treating
//   // leaf nodes in the same manner.
//   //
//   // The minimum node cannot have a left child.
//   //
//   // But the minimum node can be the right child of the deleted node so replace
//   // deleted node's data with the minimum after testing if the minimum is its
//   // right child.
//   //
//   // NOTE: If a leaf or missing right branch, then saving the node and copying
//   // its data is extraneous but minimal work overall.
//   tree* x = node;
//   tmp = node->left;
//   if (node->right != 0)
//   {
//     node = minimum(node->right);
//     tmp = node->right;
//   }
//   if (node->data > node->parent->data)
//   {
//     // Right child.
//     node->parent->right = tmp;
//   }
//   else
//   {
//     // Left child.
//     node->parent->left = tmp;
//   }
//   if (tmp != 0)
//   {
//     tmp->parent = node->parent;
//   }
//   x->data = node->data;
//   tmp = node->parent;
//   free(node);
//   return tmp;
// }

void delete(tree ** root)
{
	if (!root || !*root) {
		return;
	}

	delete(&((*root)->left));
	delete(&((*root)->right));
	free(*root);
	*root = NULL;
}

// void preorder(tree * root, void (*action_func)(tree *))
// {
//      if (!root) {
//              return;
//      }

//      action_func(root);
//      preorder(root->left, action_func);
//      preorder(root->right, action_func);
// }

// void postorder(tree * root, void (*action_func)(tree *))
// {
//      if (!root) {
//              return;
//      }
//      postorder(root->left, action_func);
//      postorder(root->right, action_func);
//      action_func(root);
// }

// void inorder(tree * root, void (*action_func)(tree *))
// {
//      if (!root) {
//              return;
//      }
//      inorder(root->left, action_func);
//      action_func(root);
//      inorder(root->right, action_func);

// }

// void levelorder(tree * root, void (*action_func)(tree *))
// {
//      if (!root) {
//              return;
//      };
//      // create queue
//      llist_t * queue = llist_create();
//      enqueue(queue, root);

//      while(0 < list_size(queue)){
//              root = dequeue(queue);
//              if (root) {
//                      action_func(root);
//                      enqueue(queue, root->left);
//                      enqueue(queue, root->right);
//              } else {
//                      printf("We got a null from dequeue\n");
//              }

//      }
//      llist_destroy(&queue, free);
// }

struct trunk {
	struct trunk *prev;
	const char *str;
};

static void print_trunks(struct trunk *p)
{
	if (!p) {
		return;
	}
	print_trunks(p->prev);
	printf("%s", p->str);
}

static void print_recursive(tree * root, struct trunk *prev, int is_left)
{
	if (!root) {
		return;
	}

	struct trunk this_disp = { prev, "     " };
	const char *prev_str = this_disp.str;
	print_recursive(root->right, &this_disp, 1);

	if (!prev) {
		this_disp.str = "---";
		printf("\n");
	} else if (is_left) {
		this_disp.str = ".--";
		printf("\n");
		prev_str = "    |";
	} else {
		this_disp.str = "`--";
		printf("\n");
		prev->str = prev_str;
	}
	// printf("\n");
	print_trunks(&this_disp);
	printf("(%.0f, %.0f)\n", root->x_coord, root->y_coord);

	if (prev) {
		prev->str = prev_str;
	}
	this_disp.str = "    |";

	print_recursive(root->left, &this_disp, 0);
	if (!prev) {
		puts("");
	}
}

void printvisual(tree * root)
{
	if (!root) {
		return;
	}
	print_recursive(root, NULL, 0);

}

int kd_tree_size(tree * root)
{
	if (!root) {
		return -1;
	}
	return root->number_nodes;
}

bool kd_tree_is_empty(tree * root)
{
	if (!root) {
		return NULL;
	}

	if (root->number_nodes == 0) {
		return true;
	}
	return false;
}

/*** end of file ***/
