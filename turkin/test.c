#include <stdio.h>
#include "../array.h"
int main(){
    ARRAY array = create_array();
    int a[10],i;
    for (i = 0; i < 9; i++){
        a[i] = i;
        insert(array,i,&a[i]);
    }
    int *d;
    for (i = 0; i < 20; i++){
        d = get(array,i);
        if (d){
            printf("Element #%d is %d\n",i,*d);
        }
        else{
            printf("No such element:%d\n",i);
        }
    }
    i = -1;
    d = get(array,i);
    if (d){
        printf("Element %d is %d\n",i,*d);
    }
    destroy_array(array);
    printf("%p\n",array);
    if (array){
        for (i = 0; i < 20; i++)
        {
         d = get(array,i);
         if (d) printf("%d %d\n",i,*d);
        }
    }
}
