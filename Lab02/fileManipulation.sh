#!/bin/bash

function downloadData
{
	local pathFile=$1
	local flag=0
	local temp
	if [[ -a "$pathFile" ]];then
		read _numNode < $pathFile
		while read LINE;do
			if [[ ${#LINE} -eq 1 ]];then
				flag=1
			
			elif [[ $flag -eq 1 ]]; then
				local _info="$LINE"
				read _source _destination <<< "$_info"
				flag=0
			else
				temp+=("$LINE")
			fi
		done < $pathFile
		addToMatrix ${temp[*]}
	fi
}

function addToMatrix
{
	for ((i=0; i < $_numNode; i++));do
		for ((j=0; j< $_numNode; j++));do
			matrix["$i:$j"]=$1
			shift
		done
	done
}

function uploadData
{
	local filename=$1
	touch "$filename"
	echo "$cost" > "$filename"
	echo -n "$result" >> "$filename"
	return 0
}