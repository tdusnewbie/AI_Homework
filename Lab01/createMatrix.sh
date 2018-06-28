#!/bin/bash

filename=$1
_numNode=$2
_source=$3
_destination=$4
_algorithm=$5

if [[ -e $filename ]]; then
	echo "$_numNode" > $filename
	echo "$_source $_destination $_algorithm" >> $filename
	for ((i=0; i<$_numNode; i++)); do
		for ((j=0; j<$_numNode; j++)); do
			_bit=$(( RANDOM % 2 ))
			if [[ $j -eq 0 ]]; then
				temp=${_bit}${temp}
			fi
			temp=${_bit}" "${temp}
		done
		echo "$temp" >> $filename
		temp=""
	done
fi