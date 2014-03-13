#include "../array.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "unistd.h"
#include "time.h"

int result;

void quickSort(ARRAY*, long, long);

int main(int argc, char *argv[])
{
	/* Test #1 */
	// Normal test for create, insert, get, destroy
   	int el = 1, * get_el;
	ARRAY array = create_array();
	assert( array != NULL );
	result = insert(array, 0, &el);
	assert( result == 0 );
	get_el = (int *) get(array, 0);
	assert( el == *get_el );
	result = destroy_array(array);
	assert( result != -1 );

	/* Test #2 */
	// Sorting with Quick Sort
	array = create_array();
	assert(array != NULL); 
	srand(time(NULL));
	int i;
	long N = 100;
	float num[100];
	for (i = 0; i < N; i++)
	{
		num[i] = rand() % 100;
		result = insert(array, i, &num[i]);
	}
 	quickSort(array, 0, N-1);
	float * prev, * current;
	for (i = 1; i < N; i++)
	{
		prev = (float *)get(array, i-1);
		current = (float *)get(array, i);
		assert( *prev <= *current );
	}
	result = destroy_array(array); 
	assert( result != -1 );
	
	/* Test #3 */


	return 0;
}

void quickSort(ARRAY *s_array, long first, long last)
{
	long i = first, j = last;
	float * temp, p;
	long to = (last + first)/2;
	p = *(float *) get(s_array, to);

	do
	{
		while ( *(float *) get(s_array, i) < p ) i++;
		while ( *(float *) get(s_array, j) > p ) j--;

		if ( i <= j )
		{
			if (i < j)
			{
				temp = (float *) get(s_array, i);
				result = insert(s_array, i, (float *) get(s_array, j));
				assert( result == 0 );
				result = insert(s_array, j, temp);
				assert( result == 0 );
			}
			i++;
			j--;
		}
	}
	while ( i <= j );

	if ( i < last ) quickSort(s_array, i, last);
	if ( j > first ) quickSort(s_array, first, j);
}
