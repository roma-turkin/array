#include <stdio.h>
#include "../array.h"
int main(){
    ARRAY array = create_array();
    int a = 1;
    int b = 2;
    int c = 3;
    insert(array,1,&a);
    insert(array,2,&b);
    insert(array,3,&c);
    int * d; 
    d = get(array,2);
    printf("%d\n",*d);
}
