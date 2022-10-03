#!/bin/sh
gcc -pthread ex4.c -o ex4
rm ex4.txt
for m in 1 2 4 10 100 
do
  echo $m >> ex4.txt
  \time -a -o ex4.txt ./ex4 10000000 $m
done

rm ex4
