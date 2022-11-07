/**
 * @file qsort_comp_funcs.c
 * @author Kyle Spicer
 * @brief program shows the full logic of creating comparison function for use
 * with qsort. compare_those_nums demonstates the full logic of receiving
 * arguments and stealth compare completes all logic in one line.
 * @version 0.1
 * @date 2022-11-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief compare_those_nums: takes void * data, type casts as an int and
 * assigns to an int *. Then the int * is assigned to an int variable for use
 * in comparing the two types. After, the variables are compared and the 
 * appropriate value is returned.
 * 
 * @param data1 
 * @param data2 
 * @return int 
 */
int compare_those_nums(const void * data1, const void * data2)
{
    int *num1 = (int*)data1; // taking void *, casting to int, assigning to an int *
    int *num2 = (int*)data2; // taking void *, casting to int, assigning to an int *

    int a = *num1; // a = the thing at address num1
    int b = * num2; // b = the thing at address num2

    // compares ints and return appropriate value
    if(a < b)
    {
        return -1;
    }
    else if(a == b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief compare_stealth_nums: completes the same logic as compare_those_nums
 * but only in one line.
 * 
 * @param data1 
 * @param data2 
 * @return int 
 */
int compare_stealth_nums(const void * data1, const void * data2)
{
    // same logic as compare those nums, but completes everything in one line
    return *(int *)data1 - *(int *)data2;
}

int main(void)
{
    int another_array[3] = {6, 5, 4};

    printf("COMPARE: LONG VERSION \n");
    printf("Before: ");
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", another_array[i]);
    }
    printf("\n");

    qsort(another_array, 3, sizeof(int), compare_those_nums);

    printf("After:  ");
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", another_array[i]);
    }
    printf("\n\n");

    int array[3] = {3, 2, 1};
    printf("COMPARE: STEALTH\n");
    printf("Before: ");
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", array[i]);
    }

    qsort(array, 3, sizeof(int), compare_stealth_nums);
    printf("\n");
    printf("After:  ");
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", array[i]);

    }
    printf("\n\n");
}