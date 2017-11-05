#!/bin/bash

cd ~
# Make directories
mkdir C
mkdir C/D
cd A/B

# copy and search
for f in *.txt; do
	if grep -Fxq "NIT Mz" $f; then
		cp $f ~/C/D
	fi
done