#!/bin/sh
gcc publisher.c -o pub
gcc subscriber.c -o sub

mkfifo /tmp/ex2
for i in `seq 1 $1`
do
  if [ $(expr $i % 2) != "0" ]; then
    tmux split-window -h './sub'
  else
    tmux split-window -v './sub'
  fi

  # ./sub&
done

./pub $1
jobs
wait
rm pub sub /tmp/ex2
