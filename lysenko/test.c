#include "../array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ERROR {printf("Error in %s on line %d\n", __FILE__, __LINE__); test_result = -1;}

int main()
{
    int a[100], b, i, res,index[10] = {10, 2, 12, 3, 4, 65, 13, 1, 5, 80};
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
    /*//Test #4
    ARRAY arr = create_array();
    for(i=0;i<1000;i++)
    {
        insert()
    for(i=0;i<1000;i++)
    {
        one = *(int *) get(arr, i);  for(j=i;j<10;j++)
        {
            two = *(int *) get(arr, j);
            if (two < one)
            {
                insert(arr,i,&two);
                insert(arr,j,&one);
            }
        }
    }*/
    return test_result;
    return 0;
}
