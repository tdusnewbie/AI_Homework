#!/bin/bash

function downloadData
{
	local pathFile="$1"
	local flag=0
	local temp
	if [[ -a "$pathFile" ]];then
		while read LINE;do
			if [[ $flag -lt 2 ]]; then
				case $flag in
					0) _numNode=$LINE
					;;
					1) local _info="$LINE"
					read _source _destination <<< "$_info"
					;;
				esac
				let flag++
			else
				temp+=("$LINE")
			fi
		done < "$pathFile"
		temp=$(echo "${temp[@]}" | tr -d '\r' )
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
	echo "$result" >> "$filename"
	return 0
}
