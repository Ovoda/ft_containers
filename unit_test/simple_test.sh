#!/bin/bash

clang++ -D NS=ft -I ../ $1 -I ./ && valgrind ./a.out > ft 2>/dev/null
if [ $? -ne 0 ]
then
    echo "Error on $1 : This is not a valgrind error, your program might have leaks or invalid read/write"
    exit 1
fi

clang++ -D NS=std -I ../ $1 -I ./ && valgrind ./a.out > std 2>/dev/null
if [ $? -ne 0 ]
then
    echo "Error on stl : that shouldn't be happening, please contact me (calide-n@student.42.fr)"
    exit 1
fi


diff ft std
if [ $? -eq 0 ]
then
    echo "$1 passed"
else
    echo "$1 diff error : stl behaves differently"
fi
rm -rf ft std

