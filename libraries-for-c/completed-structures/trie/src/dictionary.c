#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

node *createnode()
{
	node *new_node = calloc(1, sizeof(*new_node));	// create mem for new node

	// loop through each char for string and add space for children
	for (int i = 0; i < NUM_CHARS; ++i) {
		new_node->children[i] = NULL;
	}

	new_node->end_node = false;	// setting end to false when creating space

	return new_node;
}

bool insert_node(node ** root, char *string_to_insert)
{
	// if tree is empty, create new node and make it root
	if (*root == NULL) {
		*root = createnode();
	}

	unsigned char *string = (unsigned char *)string_to_insert;
	node *temp = *root;	// temp pointer to root for traversing tree
	int length = strlen(string_to_insert);	// len of string sent into func

	for (int i = 0; i < length; i++) {
		if (temp->children[string[i]] == NULL) {
			// create new node for letter
			temp->children[string[i]] = createnode();
		}

		temp = temp->children[string[i]];	// moves temp to current's child
	}

	if (temp->end_node) {
		return false;
	} else {
		temp->end_node = true;
		return true;
	}
}

static void print_dictionary_recursive(node * node, unsigned char *prefix, int length)
{
	if (node->end_node) {
		// if terminal, print the actual word
		printf("Dict word: %s\n", prefix);
	}

	for (int i = 0; i < NUM_CHARS; i++) {
		if (node->children[i] != NULL) {
			prefix[length] = i;
			print_dictionary_recursive(node->children[i],
						   prefix, length + 1);
		}
	}
}

void print_dictionary(node * root)
{
	if (root == NULL) {
		printf("Dictionary is empty!\n");
		return;
	}
	// root, no prefix yet, # of characters seen so far
	print_dictionary_recursive(root, root->word_array, 0);
}

void search_dictionary(node * root, const char *word_to_search)
{
	// ensures no negative index in lookup table
	unsigned char *string = (unsigned char *)word_to_search;
	int length = strlen((const char *)string); // length for word to search
	node * temp = root; // temp node

	for (int i = 0; i < length; i++) {
		if(temp->children[string[i]] == NULL){
			// nothing there so return false
			printf("\"%s\" does not exist in dictionary.\n", word_to_search);
			return;
		}

		unsigned char c = string[i]; // current char
		temp = temp->children[c]; // set temp child to current letter of string
	}

	if(temp->end_node){
		printf("\"%s\" exists in dictionary.\n", word_to_search);
	} // returns true (exists) or false (not flagged)
}

node * delete_word_recursive(node * node, unsigned char *string, bool *deleted)
{
	if (node == NULL) {
		return node;
	}

	// if it starts with NULL char, were at the end
	if ('\0' == *string) {
		// if the end node is true, do this
		if (node->end_node) {
			node->end_node = false;
			*deleted = true;

			if (node_has_children(node) == false) {
				free(node);
				node = NULL;
			}
		}
		return node;
	}
	// string + 1 is incrementing pointer each time recursive func is called
	node->children[string[0]] = delete_word_recursive(node->children[string[0]], string + 1, deleted);

	if (*deleted && node_has_children(node) == false && node->end_node == false) {
		free(node);
		node = NULL;
	}
	return(node);
}

bool delete_word(node **root, const char *word_to_delete)
{
	unsigned char * string = (unsigned char *)string;
	bool result = false;
	if(!root) {
		return false;
	}

	//wrapper func to delete word
	*root = delete_word_recursive(*root, (unsigned char *)word_to_delete, &result);
	return result;
}

bool node_has_children(node * node)
{
	if(node == NULL) {
		return false;
	}

	for(int i = 0; i < NUM_CHARS; i++) {
		if (node->children[i] != NULL) {
			return true;
		}
	}
	return false;
}

static void free_nodes_recursive(node * node)
{
	if (!node) {
		return;
	}

	//recurse through trie
	for (int i = 0; i < NUM_CHARS; i++) {
		free_nodes_recursive(node->children[i]);
	}

	free(node);
}

void destroy_dictionary(node **root)
{
	if (!*root) {
		return;
	}
	free_nodes_recursive(*root);
	root = NULL;	
}





/*** end of file ***/