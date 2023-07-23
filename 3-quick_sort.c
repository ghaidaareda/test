#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
/**
 *
 *
 *
 */
void swap(int *a, int *b)
{
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
}

int partition(int *array, size_t start, size_t end)
{
        size_t j;
        int pivot = array[end];
        size_t i = start - 1;

        for (j = start; j < end; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	print_array(array ,end - 0 + 1);
	swap(&array[i + 1], &array[end]);
	return (i + 1);
}


void quick_sort(int *array, size_t size)
{
	size_t pivot;

	if (size <= 1)
		return;
	pivot = partition(array, 0, size - 1);
	quick_sort(array, pivot);
    	quick_sort(&array[pivot + 1], size - pivot - 1);
}

