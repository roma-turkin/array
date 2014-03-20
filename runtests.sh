#! /bin/bash
# gcc -fprofile-arcs -ftest-coverage svikhnushina/array.c turkin/test.c 
#"svikhnushina"

names=("turkin" "lysenko" "stepanov" "afanasyev" "svikhnushina")

echo "array.c|test.c| Returned value  | Errors (if any) "
echo "-------------------------------------------------"
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
			COMPILATION_ERRORS="Warnings! Recompile to check"
		fi
		echo $ARRAY_FOLDER_NAME "|" $TEST_FOLDER_NAME "|" "Returned value " $RESULT "|" $COMPILATION_ERRORS
	done
done
