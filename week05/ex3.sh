#!/bin/sh
gcc -pthread ex3.c -o ex3
rm ex3.txt
for m in 1 2 4 10 100 
do
  /usr/bin/time -a -o ex3.txt ./ex3 10000000 $m
done

rm ex3
