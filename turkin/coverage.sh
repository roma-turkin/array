#! /bin/bash

# gcc -fprofile-arcs -ftest-coverage array.c test.c 
gcc --coverage -fprofile-arcs -ftest-coverage array.c test.c
./a.out
DIRECTORY=$(pwd)
lcov --capture --directory $DIRECTORY --output-file coverage.info
genhtml coverage.info --output-directory out
rm *.gc*
rm *.info
