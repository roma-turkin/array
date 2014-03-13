#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void main()
{
	long p;
	ARRAY a1;
	ARRAY a2;
	ARRAY a3;
	ARRAY a[30];
	long m[100];
	randomize;

	a1 = create_array();
	a2 = create_array();
	a3 = create_array();
	if (a1 == NULL || a2 == NULL || a3 == NULL) {printf("Looser!\n"); return;}

	//First array: checking indexes -2 .. 2

	for (p = -2; p <= 2; p++) printf("%d ", insert(a1, p, (void *) (p+3)));
	printf("\n");
	for (p = -2; p <= 2; p++) printf("%d ", (int) get(a1, p));
	printf("\n");

	//Second array: checking secuential filling with letters

	for (p = 1; p <= 26; p++) printf("%d ", insert(a2, p, (void *) (p+96)));
	printf("\n");
	for (p = 1; p <= 26; p++) printf("%c", (char) get(a2, p));
	printf("\n");

	//Third array: checking random filling with secuential numbers

	for (p=0; p<30; p++)
	{
		m[p] = random(1000);
		printf("%d ", insert(a3, m[p], (void *) p));
	}
	printf("\n");

	for (p=0; p<30; p++) printf("%d ", (int) get(a3, m[p]));
	printf("\n");

	//Array of arrays: I need A LOT OF arrays

	for (p = 1; p <= 26; p++)
	{
		a[p] = create_array();
		if (a[p] == NULL) {printf("Allocating problems while creating %dth massive", p); return;}
	}
	for (p = 1; p <= 26; p++) printf("%d ", insert(a[p], p, (void *) (p+96)));
	printf("\n");
	for (p = 1; p <= 26; p++) printf("%c", (char) get(a[p], p));
	printf("\n");
	for (p = 1; p <= 26; p++) printf("%d ", destroy_array(a[p]));
	printf("\n");

	printf("4 is %d, a is %c\n", (int) get(a1, 1), (char) get(a2, 1));

	printf("%d %d %d\n", destroy_array(a1), destroy_array(a2), destroy_array(a3));

	printf("Succesfully ended\n");
}

