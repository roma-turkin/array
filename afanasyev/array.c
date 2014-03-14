#include <stdio.h>
#include <stdlib.h>
#include "array.h"

struct Node                      //Array element
{
	long index;
	void * data;
	struct Node * left;
	struct Node * right;
	int ldep, rdep;          //Depth of this ways
};

struct array                     //Array descriptor
{
	struct Node * ptr;
	char exists;             //Indication of destroyed array
	long nel;                //Number of elements in this array
};

struct array * ad;               //The main pointer!
int nad = 0;                     //Number of arrays
char balancing = 0;              //Pss, guy! Do u need some balancing?
struct Node * targ;              //Target node for inserting
//1 more var: target for balancing

char find(long ind, struct Node * el)       //Weird recursive function...
{                                           //I don't understand
	if (ind == el -> index)             //how it is working...
	{                                   //And I don't use it now...
		targ = el;                  //I will need it later...
		return 0;                   //Maybe.......
	}
	if (ind < el -> index)
		if (el -> left != NULL)
		{
			if (find(ind, el -> left) == 1)
			{
				el -> ldep ++;
				return 1;
			}
		}
		else
		{
			targ = el;
			el -> ldep ++;
			return 1;
		}
	if (ind > el -> index)
		if (el -> right != NULL)
		{
			if (find(ind, el -> right) == 1)
			{
				el -> rdep ++;
				return 1;
			}
		}
		else
		{
			targ = el;
			el -> rdep ++;
			return 1;
		}

	//Here I need checking of ldep - rdep to run balancing

	return 0;
}


void * create_array()
{
	struct array * buf;

	if (nad == 0) ad = NULL;
	if (nad == 10000) return NULL;        //Coz of casting problems (zhirno ne budet?)
	if (nad % 10 == 0)
	{
		buf = (struct array *) realloc( (void *) ad, sizeof(struct array) * (nad + 10));
		if (buf == NULL) return NULL; else ad = buf;
	}

	//If realloc fails, it will return NULL, so I have to save old
	//pointer coz old memory will be left untouched.

	if (nad == 0)            	//First descriptor
	{                               //will be empty
		ad[0].exists = 0;
		nad++;
	}

	ad[nad].ptr = NULL;
	ad[nad].exists = 1;
	ad[nad].nel = 0;
	nad++;
	return (void *) (nad - 1);
}

int insert(void * arr, long ind, void * data)
{
	int ar = (int) arr;
	struct Node * el = ad[ar].ptr;
	struct Node * newel;

	if (ind < 0) return -1;
	if (nad - 1 < ar) return -1; else
		if (ad[ar].exists == 0) return -1;

	if (el == NULL) goto jmp;       //Empty array

	//I have to change the next cycle to recursive function
	//to be able to change ways' depth correctly.

	while (el -> index != ind)
	{
		if (el -> index > ind)
			if (el -> left != NULL) el = el -> left; else break;
		if (el -> index < ind)
			if (el -> right != NULL) el = el -> right; else break;
	}

	if (el -> index == ind)         //Element already exists
	{
		el -> data = data;
		return 0;
	}

jmp:    newel = (struct Node *) malloc(sizeof(struct Node));
	if (newel == NULL) return -1;
	newel -> index = ind;
	newel -> data = data;
	newel -> left = NULL;
	newel -> right = NULL;
	newel -> ldep = 0;
	newel -> rdep = 0;

	if (el == NULL) ad[ar].ptr = newel; else
		if (el -> index > ind) el -> left = newel;
			else el -> right = newel;
	return 0;
}

void * get(void * arr, long ind)
{
	int ar = (int) arr;
	struct Node * el = ad[ar].ptr;

	if (ind < 0) return NULL;
	if (nad - 1 < ar) return NULL; else
		if (ad[ar].exists == 0) return NULL;
	if (el == NULL) return NULL;       //Empty array

	while (el -> index != ind)
	{
		if (el -> index > ind)
			if (el -> left != NULL) el = el -> left; else return NULL;
		if (el -> index < ind)
			if (el -> right != NULL) el = el -> right; else return NULL;
	}

	return el -> data;
}

void remove_branch(struct Node * el)        //Recursive removing of a branch
{
	if (el == NULL) return;
	remove_branch(el -> left);
	remove_branch(el -> right);
	free(el);
}

int destroy_array(void * arr)
{
	int ar = (int) arr;
	if (nad - 1 < ar) return -1; else
		if (ad[ar].exists == 0) return -1;
	remove_branch(ad[ar].ptr);
	ad[ar].exists = 0;
	return 0;
}