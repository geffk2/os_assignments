#!/bin/sh

./ex1.sh

lspath=$(which ls)
sudo cp $lspath lofsdisk

gcc ex2.c -o ex2
sudo cp ./ex2 lofsdisk
deps=$(ldd ex2 | egrep -o '/lib.*\.[0-9]')
for i in $deps; do
  sudo cp -v --parents "$i" "lofsdisk"
done

sudo chroot lofsdisk ex2
