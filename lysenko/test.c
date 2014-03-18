#include "../array.h"
#include <stdio.h>
#include <time.h>

int main()
{
    ARRAY arr = create_array();
    int a[100], b=2, c=6, i, res;
    srand(time(NULL));
    for(i=0;i<100;i++) 
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
        insert(arr, i, &a[i]);
    }
    for(i=0;i<100;i++) printf("%d\n", *(int *) get(arr, i));
    for(i=0;i<10;i++) insert(arr, i, NULL);
    res = destroy_array(arr);
    printf("%d\n", res);
    /*for(i=0;i<10;i++)
    {
        one = *(int *) get(arr, i);
        for(j=i;j<10;j++)
        {
            two = *(int *) get(arr, j);
            if (two < one)
            {
                insert(arr,i,&two);
                insert(arr,j,&one);
            }
        }
    }*/
    return 0;
}
