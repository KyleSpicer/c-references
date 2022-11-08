#include <stdio.h>
#include <string.h>
#include "copy_binary_search_tree.h"

void print(int *data) {

    printf("%c ", *data);
}

int int_cmp(void *input, void *cmp) {

    int num1 = *(int *) input;
    int num2 = *(int *) cmp;

    int ret = 0;

    if (num2 < num1) {
        ret = -1;
    } else if (num2 > num1) {
        ret = 1;
    }

    return ret;
}

int main(void) {
    int arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    tree *tree = tree_create();

    for (size_t i = 0; i < arr_size; ++i) {
        tree_insert(tree, &arr[i], (int (*)(void *, void *)) int_cmp);
    }

    printf("Preorder: ");
    preorder(tree, (void (*)(void *)) print);
    printf("Postorder: ");
    postorder(tree, (void (*)(void *)) print);
    printf("Inorder: ");
    inorder(tree, (void (*)(void *)) print);
    printf("Levelorder: ");
    levelorder(tree, (void (*)(void *)) print);

    printf("Size: %d\n", tree_size(tree));
    printf("Tree Max: %d\n", *(int *) tree_maximum(tree));
    printf("Tree Max: %d\n", *(int *) tree_minimum(tree));
}