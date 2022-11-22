#!/bin/sh 

fallocate 50MiB lofs.img
sudo losetup /dev/loop13 lofs.img 

mkfs lofs.img
mkdir lofsdisk
sudo mount lofs.img lofsdisk

