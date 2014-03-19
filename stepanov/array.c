#include <stdio.h>
#include <stdlib.h>
#include "../array.h"

struct node
{
	INDEX index;
	DATA data;
	struct node * next;
};

ARRAY create_array() 
{
	struct node * current;
	current = malloc(sizeof(struct node));
	current->index = 0;
	current->data = NULL;
	return (current != NULL) ? current : NULL;
}

int insert(ARRAY array, INDEX index, DATA data) 
{
	if ( index < 0 ) return -1;

	struct node * current;

	current = (struct node *) array;

	while (1)	
	{
		if (current->index == index)
		{
			current->data = data;
			break;
		}
		if ( current->next )
			current = current->next;
		else
		{
			struct node * leaf;
			leaf = malloc(sizeof(struct node));
			if ( !leaf ) return -1;
			leaf->index = index;
			leaf->data = data;
			leaf->next = NULL;
			current->next = leaf;
			break;
		}
	}
	return 0;
}

DATA get(ARRAY array, INDEX index) 
{
	if ( index < 0 || !(array) )
		return NULL;
	
	struct node * current;
	current = (struct node *) array;
	
	while (1)
	{
		if (current->index == index)
			return current->data;
		if ( current->next )
			current = current->next;
		else return NULL;		
	}
}

int destroy_array(ARRAY array) 
{
	if (!array) return -1;

	struct node * current;
	current = (struct node *) array;
	if (current->next)
	{
		destroy_array(current->next);
		current->next = NULL;
	}
	free(current);
	return 0;
}
