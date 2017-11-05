#!/bin/bash

cd /media/shan/Local\ Disk/TV/Arrow\ Season\ 5
touch cop.txt

for f in *; do
	echo $f | sed 's/ /\\ /g'
done