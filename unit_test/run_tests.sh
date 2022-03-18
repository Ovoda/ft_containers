#!/bin/bash

FILES="./vector/*.cpp"
for f in $FILES
do
    clang++ -D NS=ft -I ../ $f -I ./ && valgrind ./a.out > ft 2>/dev/null
    if [ $? -ne 0 ]
    then
        echo "Error on $f : This is not a valgrind error, your program might have leaks or invalid read/write"
		exit 1
    fi

    clang++ -D NS=std -I ../ $f -I ./ && valgrind ./a.out > std 2>/dev/null
	if [ $? -ne 0 ]
    then
        echo "Error on stl : that shouldn't be happening, please contact me (calide-n@student.42.fr)"
		exit 1
    fi


    diff ft std
    if [ $? -eq 0 ]
    then
        echo "$f passed"
	else
		echo "$f diff error : stl behaves differently"
    fi
	rm -rf ft std
done
