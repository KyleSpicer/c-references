#include <stdio.h>
#include <errno.h>

#include "dictionary.h"

#define MAX_LINE_LEN 128

int main(void)
{
	FILE *file = fopen("z.txt", "r");
	if (!file) {
		printf("Error: %d\n", errno);
		exit(1);
	}
	// read lines from file
	char line[MAX_LINE_LEN];

	// create NULL node for dictionary
	node *dict_root = NULL;

	while (fgets(line, MAX_LINE_LEN, file) != NULL) {
		line[strcspn(line, "\n")] = 0;
		insert_node(&dict_root, line);
	}

	// close file
	fclose(file);

    printf("\n\n");
    printf("searching dictionary for \"zygotes\" ==> ");
	search_dictionary(dict_root, "zygotes");

    printf("attempting to delete and search for \"zygotes\" ==> ");
    delete_word(&dict_root, "zygotes");
    search_dictionary(dict_root, "zygotes");
    printf("\n\n");

    // print_dictionary(dict_root);

    // destroy dictionary
    destroy_dictionary(&dict_root);



}
