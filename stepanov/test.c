#include "../array.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define ERROR() printf("Error in %s on line %d\n", __FILE__, __LINE__);


void quickSort(ARRAY*, long, long);

int main(int argc, char *argv[])
{
	/* Test #1 */
	// Normal test for create, insert, get, destroy
	int el = 1, *get_el, result;
	ARRAY array = create_array();				if (array == NULL) ERROR();
	result = insert(array, 0, &el);				if (result != 0) ERROR();
	get_el = (int *)get(array, 0);				if (el != *get_el) ERROR();
	result = destroy_array(array);				if (result == -1) ERROR();

	/* Test #2 */
	// Sorting with Quick Sort
	array = create_array();						if (array == NULL) ERROR();
	srand(time(NULL));
	int i;
	long N = 100;
	float num[100];
	for (i = 0; i < N; i++)
	{
		num[i] = rand() % 100;
		result = insert(array, i, &num[i]);
	}
	quickSort(array, 0, N - 1);
	float * prev, *current;
	for (i = 1; i < N; i++)
	{
		prev = (float *)get(array, i - 1);
		current = (float *)get(array, i); 		if (*prev > *current) ERROR();
		// printf("%f \n", *current);
	}
	result = destroy_array(array); 				if (result == -1) ERROR();

	/* Test #3 */


	return 0;
}

void quickSort(ARRAY *s_array, long first, long last)
{
	int result;
	long i = first, j = last;
	float * temp, p;
	long to = (last + first) / 2;
	p = *(float *)get(s_array, to);				if (&p == NULL) ERROR();

	do
	{
		while (*(float *)get(s_array, i) < p) i++;
		while (*(float *)get(s_array, j) > p) j--;

		if (i <= j)
		{
			if (i < j)
			{
				temp = (float *)get(s_array, i);
				//if ( temp != NULL ) ERROR();
				result = insert(s_array, i, (float *)get(s_array, j));
				if (result != 0) ERROR();
				result = insert(s_array, j, temp);
				if (result != 0) ERROR();
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last) quickSort(s_array, i, last);
	if (j > first) quickSort(s_array, first, j);
}
