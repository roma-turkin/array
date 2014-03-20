#include "../array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ERROR {printf("Error in %s on line %d\n", __FILE__, __LINE__); test_result = -1;}

int main()
{
    int a[100], b=5, i, res,index[10] = {10, 2, 12, 3, 4, 65, 13, 1, 5, 80};
    int test_result = 0;
    srand(time(NULL));
    //Test #1
    ARRAY arr = create_array();
    for(i=0;i<100;i++) 
    {
        a[i] = rand() % 100;
        res = insert(arr, a[i], &a[i]);
        if (res == -1) ERROR
    }
    res = destroy_array(arr);
    if (res == -1) ERROR
    //Test #2
    arr = create_array();
    for(i=0;i<100;i++)
    {
        a[i] = rand() % 100;
        res = insert(arr, a[i], &a[i]);
        if (res == -1) ERROR
    }
    for(i=0;i<100;i++)
    {
        b = rand() % 100;
        res = insert(arr, b, NULL);
        if (res == -1) ERROR
    }
    res = destroy_array(arr);
    if (res == -1) ERROR
    //Test #3
    arr = create_array();
    for(i=0;i<10;i++)
    {
        a[i] = rand() % 10000;
        res = insert(arr, index[i], &a[i]);
        if (res == -1) ERROR
    }
    for(i=0;i<10;i++)
    {
        res = *(int *) get(arr, index[i]);
        if (res != a[i]) ERROR
    }
    for(i=9;i>=0;i--)
    {
        res = insert(arr, index[i], NULL);
        if (res == -1) ERROR
    }
    res = destroy_array(arr);
    if (res == -1) ERROR
    //Test #4
    ARRAY array = create_array();
    insert(array, 10, &b);
    insert(array, 2, &b);
    insert(array, 12, &b);
    insert(array, 14, &b);
    insert(array, 11, &b);
    insert(array, 1, &b);
    insert(array, 5, &b);
    insert(array, 16, &b);
    insert(array, 0, NULL);
    insert(array, 120, NULL);
    insert(array, 10, NULL);
    destroy_array(array);
    //Test #5
    array = create_array();
    insert(array, 0, &b);
    insert(array, 1, &b);
    insert(array, 2, &b);
    insert(array, 3, &b);
    insert(array, 10, &b);
    insert(array, 0, NULL);
    destroy_array(array);
    return test_result;
}
