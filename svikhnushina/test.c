#include <stdio.h>
#include "array.h"
#include <stdlib.h>
#include <time.h>

#define COUNT   1
#define ERROR {printf("Error in %s on line %d\n",__FILE__,__LINE__); res = -1;};

/* sort array */
int res = 0;
void sort_array(ARRAY array, int size)
{
    int i, j, val1, val2;

    for (i = 1; i < size; i++) {
        val1 = (int) get(array, i);
        for (j = i - 1; j >= 0; j--) {
            val2 = (int) get(array, j);
            if ( val1 >= val2 ) break;
            if ( insert(array, j, (void *) val1) ) {
                /*printf("insert(%i, %i): failed\n", j, val1);
                exit(-1);*/
                ERROR
            }
            if ( insert(array, j + 1, (void *) val2) ) {
                /*printf("insert(%i, %i): failed\n", j + 1, val2);
                exit(-1);*/
                ERROR
            }
        }
    }
}

int main()
{
    ARRAY array1 = create_array();
    ARRAY array2 = create_array();
    int i, size, cleared, val1, val2, cnt;
    void *data;

    /* create array & check */
    if ( !array1 ) {
        /*printf("create_array(): failed\n");
        exit(-1);*/
        ERROR
    }
    if ( !array2 ) {
        /*printf("create_array(): failed\n");
        exit(-1);*/
        ERROR
    }


    /* initialize rand */
    srand(time(NULL));

    for (cnt=0; cnt < COUNT; cnt++) {
        /* fill arrays by random integers ascending and descending */
        val1 = rand() % 1000 + 1;
        val2 = rand() % 1000 + 1;
        if (val1 > val2) {
            size = val1;
            cleared = val2;
        } else {
            size = val2;
            cleared = val1;
        }
        //printf("Test %i: origin size=%i, elements to be removed =%i", cnt+1, size, cleared);
        for (i = 0; i < size; i++) {
            data = (void *) (rand() + 1);
            if ( insert(array1, i, data) ) {
              /*  printf("insert(array1, %i, %i): failed\n", i, (int) data);
                exit(-1); */
                ERROR
            }
            if ( insert(array2, size - i - 1, data) ) {
                /*printf("insert(array2, %i, %i): failed\n", i, (int) data);
                exit(-1);*/
                ERROR
            }
        }

        sort_array(array1, size);
        sort_array(array2, size);

        /* part clear */
        for (i = size - cleared; i < size; i++) {
            if ( insert(array1, i, NULL) ) {
                /*printf("insert(array1, %i, NULL): failed\n", i);
                exit(-1);
                */
                ERROR
            }
            if ( insert(array2, i, NULL) ) {
                /*printf("insert(array2, %i, NULL): failed\n", i);
                exit(-1);*/
                ERROR
            }
        }
        size -= cleared;

        /* check array */
        for (i = 0; i < size; i++) {
            val1 = (int) get(array1, i);
            if ( !val1 ) {
                /*printf("get(array1, %i): failed\n", i);
                exit(-1);*/
                ERROR
            }
            val2 = (int) get(array2, i);
            if ( !val2 ) {
                /*printf("get(array2, %i): failed\n", i);
                exit(-1);*/
                ERROR
            }
            if ( val1 != val2 ) {
                /*printf("array1[%i]=%i <> array2[%i]=%i\n", i, val1, i, val2);
                exit(-1);*/
                ERROR
            }
        }

        /* full clear */
        for (i = 0; i < size; i++) {
            if ( insert(array1, i, NULL) ) {
                /*printf("insert(array1, %i, NULL): failed\n", i);
                exit(-1);*/
                ERROR
            }
            if ( insert(array2, i, NULL) ) {
                /*printf("insert(array2, %i, NULL): failed\n", i);
                exit(-1);*/
                ERROR
            }
        }
        //printf("\tsucceed\n");
    }

    /* destroyclear arrays */
    if ( destroy_array(array1) ) {
        /*printf("destroy_array1(): failed\n");
        exit(-1);*/
        ERROR
    };
    if ( destroy_array(array2) ) {
        /*printf("destroy_array2(): failed\n");
        exit(-1);*/
        ERROR
    };

    return res;
}
