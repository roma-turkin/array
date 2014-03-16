#! /bin/bash

# gcc -fprofile-arcs -ftest-coverage array.c test.c 
gcc --coverage -fprofile-arcs -ftest-coverage array.c test.c
 ./a.out
lcov --capture --directory /home/roman/programming/array/turkin --output-file coverage.info
genhtml coverage.info --output-directory out
rm a.out
rm *.gc*
