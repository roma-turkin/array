#include "../array.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "unistd.h"
#include "time.h"

void quickSort(ARRAY*, long, long);

int main(int argc, char *argv[])
{
    int result;
	/* Test #1 */
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
	array = create_array();
    assert(array != NULL); 
    srand(time(NULL));
    int i;
    long N = 10;
    float num[N];
    for (i = 0; i < N; i++)
    {
        num[i] = rand() % 100;
        result = insert(array, i, &num[i]);
        assert( result == 0 );
    }
    float * element;

    quickSort(array, 0, N-1);

    float * prev, * current, * temp;
    for (i = 1; i < N; i++)
    {
        prev = (float *)get(array, i-1);
        element = (float *)get(array, i);
        assert( *prev <= *element );
    }

    result = destroy_array(array); 
    assert( result != -1 );

	return 0;
}

void quickSort(ARRAY* s_array, long first, long last)
{
    long i = first, j = last;
    float * temp, p;
    p = *(float *) get(s_array, ((last - first) / 2));

    do
    {
        while ( *(float *) get(s_array, i) < p ) i++;
        while ( *(float *) get(s_array, j) > p ) j++;

        if ( i <= j )
        {
            if (i < j)
            {
                temp = (float *) get(s_array, i);
                insert(s_array, i, (float *) get(s_array, j));
                insert(s_array, j, temp);
            }
            i++;
            j--;
        }
    }
    while ( i <= j );

    if ( i < last ) quickSort(s_array, i, last);
    if ( j > first ) quickSort(s_array, first, j);
}
