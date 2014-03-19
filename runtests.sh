#! /bin/bash
# gcc -fprofile-arcs -ftest-coverage svikhnushina/array.c turkin/test.c 

names=("turkin" "lysenko" "svikhnushina" "stepanov" "afanasyev")

#ARRAY_FOLDER_NAME="turkin"
#TEST_FOLDER_NAME="turkin"
for ARRAY_FOLDER_NAME in ${names[*]}
do
	for TEST_FOLDER_NAME in ${names[*]}
	do
		gcc $ARRAY_FOLDER_NAME/array.c $TEST_FOLDER_NAME/test.c 	   		     	 2>error_log
		./a.out     					                                             1>output_log
		RESULT=$?
		COMPILATION_ERRORS="No errors occured"
		if [ $(stat -c %s error_log) -ne 0 ]
		then 
			COMPILATION_ERRORS="ERROR! Recompile to check"
		fi
		echo $ARRAY_FOLDER_NAME $TEST_FOLDER_NAME $RESULT $COMPILATION_ERRORS
	done
done

#ARRAY_FOLDER_NAME="afanasyev"
#TEST_FOLDER_NAME="afanasyev"
#gcc $ARRAY_FOLDER_NAME/array.c $TEST_FOLDER_NAME/test.c 	   		     	 2>error_log
#./a.out     					                                             1>output_log
#RESULT=$?
#COMPILATION_ERRORS="No errors occured"
#if [ $(stat -c %s error_log) -ne 0 ]
#then 
#	COMPILATION_ERRORS="ERROR! Recompile to check"
#fi
#echo $ARRAY_FOLDER_NAME $TEST_FOLDER_NAME $RESULT $COMPILATION_ERRORS
#gcc turkin/array.c svikhnushina/test.c -o tsv        2>error_log
#./tsv                                                1>output_log
#RESULT=$?
#if [ "$RESULT" -ne 0 ]
#	then echo "tsv failed"
#fi
#rm tsv
