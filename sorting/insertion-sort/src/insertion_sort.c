/* This program demonstrates the insertion sort method */

#include <stdio.h>

#include "llist.h"

void insertion_sort(int data[], int size);

int main()
{
    int nums[10] = { 5, 3, 6, 11, 1, 2, 4, 4, 12, 3};
    int nums_size = sizeof(nums) / sizeof(int);

    printf("Before: ");
    for(int i = 0; i < nums_size; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    insertion_sort(nums, nums_size);

    printf("After : ");
    for(int i = 0; i < nums_size; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

}

void insertion_sort(int data[], int size)
{
    int i, j, key;
    for (i = 1; i <= size - 1; i++)
    {
        key = data[i]; // key is individual element in array
        j = i;

        while(data[j - 1] > key && j >= 1)
        {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = key;
    }
}

/* end of file */