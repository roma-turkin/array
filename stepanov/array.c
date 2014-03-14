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
	struct node * root;
	root = malloc(sizeof(struct node));
	root->index = -1;
	root->data = NULL;
	root->next = NULL;
	return (root != NULL) ? root : NULL;
}

int insert(ARRAY array, INDEX index, DATA data) 
{
	if ( index < 0 ) return -1;

	struct node * root;
	struct node * leaf;
	struct node * current;

	root = (struct node *) array;

	leaf = malloc(sizeof(struct node));
	if ( !leaf ) return -1;

	leaf->index = index;
	leaf->data = data;
	leaf->next = NULL;

	if ( !(root->next) )
	{
		root->next = leaf;
		return 0;
	}
		
	current = root->next;
	while (1)
	{
		if ( current->next )
			current = current->next;
		else break;
	}
	
	current = root->next;
	while (1)
	{
		if (current->index == index)
		{
			current->data = data;
			free(leaf);
			break;
		}
		if ( current->next )
			current = current->next;
		else
		{
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
	current = current->next;
	
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

	struct node * root;
	root = (struct node *) array;
	if (root->index == -1 && !root->next)
		return -1;
	if (root->next)
	{
		destroy_array(root->next);
		free(root->next);
	}
	root->next = NULL;

	return 0;
}
