#include <stdio.h>
#include <stdlib.h>
#include "../array.h"

struct tree
{
	INDEX index;
	DATA data;
	struct tree * next;
};

ARRAY create_array() 
{
	struct tree * root;
	root = malloc(sizeof(struct tree));
	root->index = -1;
	root->data = NULL;
	root->next = NULL;
	return (root != NULL) ? root : NULL;
}

int insert(ARRAY array, INDEX index, DATA data) 
{
	if ( index < 0 )
		return -1;
	struct tree * leaf;
	leaf = malloc(sizeof(struct tree));
	if ( !leaf )
		return -1;
	leaf->index = index;
	leaf->data = data;
	leaf->next = NULL;

	struct tree * root;
	root = (struct tree *) array;
	if ( !(root->next) )
	{
		root->next = leaf;
		return 0;
	}

	struct tree * current;
	current = root->next;
	while (1)
	{
		if (current->index == index)
		{
			current->data = data;
			return 0;
		}
		else if ( current->next )
		{
			current = current->next;
			continue;
		}
		else
		{
			current->next = leaf;
			return 0;
		}
	}
	
	return -1;
}

DATA get(ARRAY array, INDEX index) 
{
	if ( index < 0 || !(array) )
		return NULL;
	
	struct tree * current;
	current = (struct tree *) array;
	current = current->next;
	
	while (1)
	{
		if (current->index == index)
			return current->data;
		else if ( current->next )
		{
			current = current->next;
			continue;
		}
		else
			return NULL;		
	}
}

int destroy_array(ARRAY array) 
{
	if ( !(array) ) 
		return -1;

	struct tree * root;
	root = (struct tree *) array;
	if ( !(root->next) )
		free(root);
	else
		destroy_array(root->next);
	//root->next = NULL;
	//free(root);
	return 0;
}
