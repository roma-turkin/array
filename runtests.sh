#! /bin/bash
# gcc -fprofile-arcs -ftest-coverage svikhnushina/array.c turkin/test.c 
rm error_log
rm output_log
gcc turkin/array.c turkin/test.c -o tt 	   		     2>error_log
./tt                                                 1>output_log
RESULT=$?
if [ "$RESULT" -ne 0 ]
	then echo "tt failed"
fi
rm tt

gcc turkin/array.c svikhnushina/test.c -o tsv        2>error_log
./tsv                                                1>output_log
RESULT=$?
if [ "$RESULT" -ne 0 ]
	then echo "tsv failed"
fi
rm tsv

gcc turkin/array.c stepanov/test.c -o tst 			 2>error_log
./tst                                                1>output_log
RESULT=$?
if [ "$RESULT" -ne 0 ]
	then echo "tst failed"
fi
rm tst

gcc turkin/array.c afanasyev/test.c -o ta			 2>error_log
./ta                                                 1>output_log
RESULT=$?
if [ "$RESULT" -ne 0 ]
	then echo "ta failed"
fi
rm ta

gcc turkin/array.c lysenko/test.c -o tl              2>error_log
./tl                                                 1>output_log
RESULT=$?
if [ "$RESULT" -ne 0 ]
	then echo "tl failed"
fi
rm tl
