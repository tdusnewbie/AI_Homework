#!/bin/bash

declare -a stack

function sortStack
{
	stack=($(echo "${stack[@]}" | tr " " "\n" | sort -t ":" -k 2nbr -k 1nbr | tr "\n" " "))
}

function pushBackStack
{
	local posNode=$1
	local deepNode=$2
	local pathNode=$3
	stack+=("$posNode:$deepNode:$pathNode")
	sortStack
}

function IDS
{
	# Analys Input Parameter
	local nodeStart=$1
	local nodeStop=$2
	#Create an Array to Check the existence of Node in Queue
	local existed
	while [[ ${#existed[@]} -lt $_numNode ]]; do
		existed+=("0");
	done

	# Add source Node into Stack
	local pos=0
	local deep=0
	local path=$pos
	pushBackStack $pos $deep "$path"
	existed[0]="1"
	while [[ ${#stack[@]} -gt 0 ]]; do
		# take the last element in Stack out
		local last="$(echo "${stack[-1]}" | tr ":" " ")"
		unset stack[-1]
		stack=("${stack[@]}")
		read pos deep path <<< "$last"
		if [[ $pos -eq $nodeStop ]]; then
			result="$path"
			cost="$deep"
			return 0
		fi
		#Add all Child Node of above node into queue
		for ((i = $pos ;i<$_numNode;i++));do
			if [[ ${matrix["$pos:$i"]} -ne 0 ]]; then
				local deepChild=$(($deep + 1))
				local pathChild="${path}->$i"
				#If This Node has not existed in Queue 
				if [[ ${existed[$i]} -eq 0 ]]; then
					# Push it into Queue
					pushBackStack $i $deepChild "$pathChild"
					existed[$i]=1
				#If this node has existed in Queue
				else
					# Update it if its priNum is smaller than old priNum
					local oldPos oldDeep oldPath
					for ((j=0; j< ${#stack[@]};j++));do
						local temp="$(echo "${stack[$j]}" | tr ":" " ")"
						read oldPos oldDeep oldPath <<< "$temp"
						if [[ $oldPos -eq $i ]]; then
							if [[ $oldDeep -gt $deepChild ]]; then
								stack[$i]="$i:$deepChild:$pathChild"
								sortStack
								break;
							fi
						fi
					done
				fi
			fi
		done
	done

}


function IDSDemo
{
	for i in {1..10};do
		stack+=("$((RANDOM % 20)):$((RANDOM % 20)):$((RANDOM % 20))")
		echo "${stack[@]}"
	done
	sortStack
	echo "----------------------------------------------"
	echo "${stack[@]}"
	unset stack[-1]
	echo "${stack[@]}"
	#echo "${stack[-1]}"
}