#include "../array.h"
#include <stdio.h>

int main()
{
    ARRAY arr = create_array();
    int a=1, b=2, c=6;
    insert(arr, 0, &a);
    insert(arr, 3, &b);
    DATA res = get(arr, 38);
    if (res == NULL) printf("FAIL GET");
    else printf("%d\n", *(int *)res);
    destroy_array(arr);
    destroy_array(arr);
    return 0;
}
