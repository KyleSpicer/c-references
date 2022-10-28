#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_sort(const void * first, const void * second)
{
    // a < b -> -1
    // a == b -> 0
    // a > b -> 1
    // where a is element before b

    int a = *(int *)first;
    int b = *(int *)second;

    if(a < b)
    {
        return -1;
    }

    return a != b;
    // return a == b ? 0 : 1;
}

int custom_strcmp(const void *first, const void *second)
{
    char *name1 = *(char **)first;
    char *name2 = *(char **)second;

    return strcmp(name1, name2);
}

int main()
{
    int nums[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = sizeof(nums) / sizeof(int);

    printf("--- Q-Sort with integers --- \n");
    printf("Before : ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    qsort(nums, size, sizeof(*nums), int_sort);

    printf("After  : ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n\n");

    // char names[4][8] = {"Kyle", "Tim", "Jacob", "Chante"};
    char *names[4] = {"Kyle", "Tim", "Jacob", "Chante"};

    printf("--- Q-Sort with strings  ---\n");
    printf("Names: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%s\t", names[i]);
    }
    printf("\n");
    
    qsort(names, 4, sizeof(char *), custom_strcmp);
    // qsort(names, 4, sizeof(char *), strcmp);
    

    printf("After: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%s    ", names[i]);
    }
    printf("\n\n");

}


