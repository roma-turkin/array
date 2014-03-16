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
	long nel;                //Number of elements in this array (not in use now)
};

struct array * ad;               //The main pointer!
int nad = 0;                     //Number of arrays
char balancing = 0;              //Pss, guy! Do u need some balancing?
char waiting = 0;                //Ehm...
struct Node * targ;              //Target node for inserting
struct Node * btarg;             //Target node for balancing
struct Node * root;              //Previous node for btarg


char find(long ind, struct Node * el)       //Weird recursive function...
{                                           //I don't understand
	if (ind == el -> index)             //how it is working...
	{
		targ = el;
		return 0;
	}
	if (ind < el -> index)
		if (el -> left != NULL)
		{
			if (find(ind, el -> left) == 1)
			{
				el -> ldep ++;
				goto check;
			}
			else return 0;
		}
		else
		{
			targ = el;
			el -> ldep ++;
			goto check;
		}
	if (ind > el -> index)
		if (el -> right != NULL)
		{
			if (find(ind, el -> right) == 1)
			{
				el -> rdep ++;
				goto check;
			}
			else return 0;
		}
		else
		{
			targ = el;
			el -> rdep ++;
			goto check;
		}

check:  if ((el -> ldep - el -> rdep) * (el -> ldep - el -> rdep) > 4)
	{
		balancing = 1;        //Choose highest node with
		btarg = el;           //abs(rdep - ldep) > 2
		waiting = 0;
	}
	else if (balancing == 1 && waiting == 0)
	{
		waiting = 1;
		root = el;
	}
	return 1;
}

struct Node * balance(struct Node * el, struct Node * root)
{
	char dirrt = 1, direl = 1;                    //1 - left node, 2 - right node
	int n = el -> rdep;                   	      //Number of nodes in brunch being transferred
	struct Node * go = el -> left;
	struct Node * newroot;

	if (root != NULL)
		if (root -> right == el) dirrt = 2;   //Direction of disbalanced node from root
	if (el -> rdep > el -> ldep)                  //Direction of larger weight from el
	{
		direl = 2;
		n = el -> ldep;
		go = el -> right;
	}
	n++;

	if (root != NULL)
		if (dirrt == 1) root -> left = go; else root -> right = go;
	else newroot = go;
	//Attaching overweighted branch to root element

	while ((go -> left != NULL && direl == 2) || (go -> right != NULL && direl == 1))
	{
		if (direl == 2)                //Search for utmost node
		{                              //in overweighted branch
			go -> ldep += n;
			go = go -> left;
		}
		else
		{
			go -> rdep += n;
			go = go -> right;
		}
	}

	if (direl == 2)                        //Attach light branch
	{                                      //to that node
		go -> left = el;
		go -> ldep += n;
		el -> rdep = 0;
		el -> right = NULL;
		go = el -> left;
		if (go != NULL)
			if ((go -> ldep - go -> rdep) * (go -> ldep - go -> rdep) > 4)
				balance(go, el);
	}
	else
	{
		go -> right = el;
		go -> rdep += n;
		el -> ldep = 0;
		el -> left = NULL;
		go = el -> right;
		if (go != NULL)
			if ((go -> ldep - go -> rdep) * (go -> ldep - go -> rdep) > 4)
				balance(go, el);
	}

	if (root == NULL) return newroot;
	return NULL;
}

void * create_array()
{
	struct array * buf;

	if (nad == 0) ad = NULL;
	if (nad == 10000) return NULL;        //Coz of casting issues (zhirno ne budet?)
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

	find(ind, el);
	el = targ;

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

	if (balancing == 1)             //Launching balancing
	{
		if (waiting == 1) balance(btarg, root);
			else ad[ar].ptr = balance(btarg, NULL);
		waiting = 0;
		balancing = 0;
	}

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