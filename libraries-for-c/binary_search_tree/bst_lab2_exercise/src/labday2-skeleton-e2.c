#include <stdio.h>
#include <stdlib.h>

// BINARY TREE DEFINITION BELOW
// No need to edit this code, as it is provided for you to work with.
struct node {
	int value;
	struct node *left;
	struct node *right;
};

struct node *new_node(int value)
{
	// define a pointer to dynamically allocated memory for a node
	struct node *node = (struct node *)(malloc(sizeof(struct node)));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// SECTION 2.1
int height(struct node *root)
{
	if(!root) {
		return 0;
	}
	else {
		// start height count at 1, to account for root node
		int max_height = 1;

		// recursively determine left and right height
		int l_height;
		int r_height;
		l_height = height(root->left);
		r_height = height(root->right);

		// determine which height is greater
		if (l_height > r_height) {
			max_height += l_height;
		}
		else {
			max_height += r_height;
		}
		return max_height;
		}
}

// SECTION 2.2
int recursive_preorder_traversal(struct node *node)
{
	if(!node) {
		return 0;
	}
	
	printf(" %d ", node->value);
	recursive_preorder_traversal(node->left);
	recursive_preorder_traversal(node->right);
}

int recursive_postorder_traversal(struct node *node)
{
	if(!node) {
		return 0;
	}

	recursive_postorder_traversal(node->left);
	recursive_postorder_traversal(node->right);
	printf(" %d ", node->value);
}

int recursive_inorder_traversal(struct node *node)
{
	if(!node) {
		return 0;
	}

	recursive_inorder_traversal(node->left);
	printf(" %d ", node->value);
	recursive_inorder_traversal(node->right);

}

//SECTION 2.3

int print_height_of_tree(struct node *root, int level)
{
	if(!root) {
		return 0;
	}

	// if not at desired level, recursively travel down
	if (level > 1) {
		print_height_of_tree(root->left, level - 1);
		print_height_of_tree(root->right, level - 1);
	}

	else {
		printf("%d ", root->value);
	}
}

//SECTION 2.4

int binary_search(struct node *root, int num)
{
	if(!root) {
		printf("Not found.\n");
		return 0;
	}
	if (root->value == num) {
		printf("Found %d\n", num);
		return 1;
	}
	else if (root->value > num) {
		printf("Visited %d\n", root->value);
		return binary_search(root->left, num);
	}
	printf("Visited %d\n", root->value);
	return binary_search(root->right, num);
}

//SECTION 2.5

int max_bst(struct node *root)
{
	if(!root) {
		return 0;
	}
	
	struct node * curr = root;
	while(curr->right) {
		curr = curr->right;
	}
	return curr->value;
}

int min_bst(struct node *root)
{
	if(!root) {
		return 0;
	}

	struct node * curr = root;
	while(curr->left) {
		curr = curr->left;
	}
	return curr->value;
}

int verify_bst(struct node *root)
{
	if(!root) {
		return 0;
	}
	
	if (root->left == NULL && root->right == NULL) {
		return 1;
	}

	if ((max_bst(root->left) < root->value) &&
		(min_bst(root->right) > root->value) &&
		verify_bst(root->left) && verify_bst(root->right)) {
			return 1;
		}
	
}

//SECTION 2.6

int flip(struct node *root)
{
	if(root) {
		flip(root->left);
		flip(root->right);
	
		// swap nodes
		struct node * temp = root->right;
		root->right = root->left;
		root->left = temp;
		return 1;
	}

	else{
		return 0;
	}
}

struct node *insert_backward_bst(struct node * root, int data)
{
	if(!root) {
		return new_node(data);
	}

	if(data > root->value) {
		root->left = insert_backward_bst(root->left, data);
	}
	else if (data < root->value) {
		root->right = insert_backward_bst(root->right, data);
	}

	return root;
}

//SECTION 2.7
struct node *build_backwards_bst(int *arr, int size)
{
	if(!*arr || !size) {
		return NULL;
	}

	struct node * new_tree = NULL;

	for (int i = 0; i < size; i++) {
		new_tree = insert_backward_bst(new_tree, arr[i]);
	}
	return new_tree;
}

//SECTION 2.8
int left_children_count_aux(struct node * root) 
{
	if (root) {
		if (root->left) {
			return 1 +left_children_count_aux(root->left) + left_children_count_aux(root->right);
		}
		else {
			return left_children_count_aux(root->left) + left_children_count_aux(root->right);
		}
	}
	return 0;
}

int right_children_count_aux(struct node * root)
{
	if (root) {
		if (root->right) {
			return 1 + right_children_count_aux(root->left) + right_children_count_aux(root->right);
		}
	}
	return 0;
}

int *left_right_children_count(struct node *root, int *children)
{
	children[0] = left_children_count_aux(root);
	children[1] = right_children_count_aux(root);
	return children;
}

struct node * insert_bst(struct node * root, int to_insert)
{
	if (!root) {
		return new_node(to_insert);
	}

	if (to_insert > root->value) {
		root->right = insert_bst(root->right, to_insert);
	}
	else if (to_insert < root->value) {
		root->left = insert_bst(root->left, to_insert);
	}
	return root;
}

int inorder_bst_to_file(struct node * node, FILE * fp)
{
	if(!node) {
		return 0;
	}

	inorder_bst_to_file(node->left, fp);
	fprintf(fp, "%d ", node->value);
	inorder_bst_to_file(node->right, fp);
}

int read_and_write()
{
	struct node * new_bst = NULL;
	int number;
	FILE *fp = fopen("numbers.txt", "r");

	if(!fp) {
		printf("failed to open file.\n");
		return 0;
	}
	printf("Successfully opened \"numbers.txt\"\n");
	// insert into bst from file
	while(fscanf(fp, "%d ", &number) != EOF) {
		new_bst = insert_bst(new_bst, number);
	}
	printf("Successfully read contents from file and added to new binary search tree\n");

	fclose(fp);
	printf("Successfully closed \"numbers.txt\"\n\n");

	fp = fopen("numbers_sorted.txt", "w");

	if(!fp) {
		printf("failed to open file.\n");
		return 0;
	}
	printf("Successfully opened \"numbers_sorted.txt\"\n");

	inorder_bst_to_file(new_bst, fp);
	printf("Successfully wrote contents from new binary search tree to \"numbers_sorted.txt\"\n");

	fclose(fp);
	printf("Successfully closed \"numbers_sorted.txt\"\n\n");

	return 0;
}

int main()
{
	// arrays
	int backwards[7] = { 28, 16, 13, 13, 19, 8, 60 };
	int children[2] = { 0, 0 };

	printf("Exercise 2 Testing Utilities:\n");

	// tree 'root_1'
	struct node *root_1 = new_node(1);
	root_1->left = new_node(2);
	root_1->right = new_node(3);
	root_1->left->left = new_node(4);

	// tree 'root_2'
	struct node *root_2 = NULL;

	// tree 'root_3'
	struct node *root_3 = new_node(3);

	// tree 'root_4'
	struct node *root_4 = new_node(4);
	root_4->left = new_node(8);
	root_4->right = new_node(12);
	root_4->left->left = new_node(16);
	root_4->left->right = new_node(20);
	root_4->right->left = new_node(24);
	root_4->right->right = new_node(28);

	//manually create BST
	struct node *binary = new_node(16);
	binary->left = new_node(8);
	binary->right = new_node(26);
	binary->left->left = new_node(4);
	binary->left->right = new_node(11);
	binary->right->left = new_node(22);
	binary->right->right = new_node(30);

	printf("height of root_1: %d\n", height(root_1));
	printf("height of root_2: %d\n", height(root_2));
	printf("height of root_3: %d\n", height(root_3));
	printf("height of root_4: %d\n", height(root_4));

	printf("-----");
	printf("traversals of root_4:\n");
	printf("In-order traversal: ");
	recursive_inorder_traversal(root_4);
	printf("\n Pre-order traversal: ");
	recursive_preorder_traversal(root_4);
	printf("\n Post-order traversal: ");
	recursive_postorder_traversal(root_4);

	printf("\nPrinting levels of tree:\n");
	printf("Level 3 of root_4: ");
	print_height_of_tree(root_4, 3);
	printf("\n-----\n");

	binary_search(binary, 29);
	printf("-----\n");

	printf("not a binary search tree: %d\n", verify_bst(root_4));
	printf("this is a binary search tree: %d\n", verify_bst(binary));
	printf("------\n");
	printf("Before flipping:\n");
	recursive_inorder_traversal(binary);
	flip(binary);
	printf("\nAfter flipping:\n");
	recursive_inorder_traversal(binary);
	flip(binary);
	printf("\nAfter flipping again\n");
	recursive_inorder_traversal(binary);

	struct node *backward_tree = build_backwards_bst(backwards, 7);
	printf("\n-----\n");
	recursive_inorder_traversal(backward_tree);

	printf("\nLeft and right children of binary tree: %d, %d",
	       left_right_children_count(binary, children)[0],
	       left_right_children_count(binary, children)[1]);

	struct node *root_5 = new_node(1);
	root_5->left = new_node(2);
	root_5->right = new_node(3);
	root_5->left->left = new_node(4);

	printf("\nLeft and right children of binary tree: %d, %d",
	       left_right_children_count(root_5, children)[0],
	       left_right_children_count(root_5, children)[1]);

	printf("\n\nRunning read and Write:\n\n");
	read_and_write();
}
