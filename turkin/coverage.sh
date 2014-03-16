#! /bin/bash

 gcc -fprofile-arcs -ftest-coverage array.c test.c 
 ./a.out
 gcov -b array.c test.c
 rm a.out
 rm *.gc*
