#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
/**
 *swap-swap elements
 *@a:a
 *@b:b
 *Return:void
 */
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * selection_sort-sorts an array in ascending order using the Selection sort
 * @array:array of integers
 * @size:size of array
 * Return:void
 */

void selection_sort(int *array, size_t size)
{
	unsigned int i, j, min;

	for (i = 0; i < size - 1; i++)
	{
		min = i;
	for (j = i + 1; j < size; j++)
	{
		if (array[j] < array[min])
		{
			min = j;
		}
	}
	swap(&array[min], &array[i]);
	print_array(array, size);
	}
}
