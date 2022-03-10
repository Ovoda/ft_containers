#!/bin/sh
clang++ test.cpp -I ../utils -D NAMESPACE=ft && ./a.out > ft
clang++ test.cpp -I ../utils -D NAMESPACE=std && ./a.out > std

diff ft std > diff

rm -rf std ft

if [[ $? -eq 1 ]]
then
    echo "not good"
else
    echo "good"
fi