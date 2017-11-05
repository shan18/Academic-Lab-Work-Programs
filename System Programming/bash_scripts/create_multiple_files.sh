#!/bin/bash

cd ~
# Make 2 directories
mkdir A
mkdir A/B
cd A/B

# create directories
counter=1
while [[ $counter -le 10 ]];
do
	touch $counter.txt
	echo $counter > $counter.txt
	if [[ $counter%2 -eq 0 ]]; then
		echo "NIT Mz" >> $counter.txt
	fi
	((counter++))
done