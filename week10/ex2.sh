#!/bin/sh

mkdir -p ../week01 
echo stuff > ../week01/file.txt

ln ../week01/file.txt _ex2.txt

inum=$(ls -i _ex2.txt | awk '{print $1}')

find .. -inum $inum > ex2.txt 

find .. -inum $inum -exec rm {} \; >> ex2.txt
