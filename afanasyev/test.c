#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#define Error {printf("Error in %s on line %d; p = %ld\n", __FILE__, __LINE__, p); ret = -1;}

int main()
{
	long p = 0;
	char ret = 0;
	ARRAY a1;
	ARRAY a2;
	ARRAY a3;
	ARRAY a[30];
	long m[100];
	srand(time(NULL));

	a1 = create_array();   if (a1 == NULL) Error
	a2 = create_array();   if (a2 == NULL) Error
	a3 = create_array();   if (a3 == NULL) Error

	//First array: checking indexes -2 .. 2

	if (insert(a1, -2, (void *) 1) != -1) Error
	if (insert(a1, -1, (void *) 2) != -1) Error
	if (insert(a1, 0, (void *) 3) != 0) Error
	if (insert(a1, 1, (void *) 4) != 0) Error
	if (insert(a1, 2, (void *) 5) != 0) Error

	if (get(a1, -2) != (void *) 0) Error
	if (get(a1, -1) != (void *) 0) Error
	if (get(a1, 0) != (void *) 3) Error
	if (get(a1, 1) != (void *) 4) Error
	if (get(a1, 2) != (void *) 5) Error

	//Second array: checking secuential filling with sequential numbers

	for (p = 1; p <= 26; p++)
		if (insert(a2, p, &(m[p])) != 0) Error
	for (p = 1; p <= 26; p++)
		if (get(a2, p) != &(m[p])) Error

	//Third array: checking random filling with sequential numbers

	for (p = 0; p < 30; p++)
	{
		m[p] = rand() % 100000;
		if (insert(a3, m[p], &(m[p])) != 0) Error
	}
	for (p=0; p<30; p++)
		if (get(a3, m[p]) != &(m[p])) Error

	//Array of arrays: I need A LOT OF arrays

	for (p = 1; p <= 26; p++)
	{
		a[p] = create_array();
		if (a[p] == NULL) Error
	}
	for (p = 1; p <= 26; p++)
		if (insert(a[p], p, (void *) &p) != 0) Error
	for (p = 1; p <= 26; p++)
		if (get(a[p], p) != &p) Error
	for (p = 1; p <= 26; p++)
		if (destroy_array(a[p]) != 0) Error

	//Checking "permanent set" and disposing everything

	if (get(a1, 1) != (void *) 4) Error
	if (get(a2, 1) != &(m[1])) Error
	if (destroy_array(a1) != 0) Error
	if (destroy_array(a2) != 0) Error
	if (destroy_array(a3) != 0) Error

	//The last test: some exotic situations

	a1 = create_array();   if (a1 == NULL) Error
	if (get(a1, 10) != NULL) Error
	if (insert(a1, 5, (void *) 5) != 0) Error
	if (insert(a1, 5, (void *) 5) != 0) Error
	if (destroy_array(a1) != 0) Error

	return ret;
}