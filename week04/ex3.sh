#!/bin/sh

gcc ex3.c -o ex3

echo "Experiment 1"
./ex3 3&
for i in `seq 1 3`
do
  pstree $$
  sleep 5
done

echo "Experiment 2"
./ex3 5&
for i in `seq 1 5`
do
  pstree $$
  sleep 5
done
