#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 256		// enough to house string

typedef struct node {
	struct node *children[NUM_CHARS];	// array for children
	bool end_node;		// checks if its the end of a word
    unsigned char word_array[NUM_CHARS];
} node;

node *createnode();

bool insert_node(node ** root, char *string_to_insert);

void print_dictionary(node * root);

void search_dictionary(node * root, const char *word_to_search);

node * delete_word_recursive(node * node, unsigned char *string, bool *deleted);

bool delete_word(node **root, const char *word_to_delete);

bool node_has_children(node * node);

void destroy_dictionary(node **root);

#endif				/* DICTIONARY_H */
