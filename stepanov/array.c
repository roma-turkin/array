#include <stdlib.h>
#include <assert.h>
#include "../array.h"

const int ERR = 1;

ARRAY create_array() 
{
	void* arr = (void*) calloc(0, sizeof(void));
	return (arr != NULL) ? arr : NULL;
}

int insert(ARRAY array, INDEX index, DATA data) 
{
	if (DATA == NULL)
	{
		if ( sizeof(array) < (index + 1) * sizeof(DATA) ) return ERR;  
		*(array + index * sizeof(DATA)) = NULL;
		return 0;
	}

	if ( sizeof(array) < (index + 1) * sizeof(DATA) )
		realloc(array, (index + 1) * sizeof(DATA));

	memcpy( *(array + index * sizeof(DATA)), (const void*)data, sizeof(DATA) ); 
	return 0;
}

DATA get(ARRAY array, INDEX index) 
{
	assert(array);
	if ( sizeof(array) < (index + 1) * sizeof(DATA) ) return NULL;
 
	return *(array + index * sizeof(DATA));
}

int destroy_array(ARRAY array) 
{
	if ( !(array) ) return -1;

	free(array);
}