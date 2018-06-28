#!/bin/bash

declare -a queue

function sortQueue
{
	queue=($(echo "${queue[@]}" | tr " " "\n" | sort -t ":" -k 2n | tr "\n" " "))
}

function pushBack
{
	local posNode=$1
	local priNode=$2
	local pathNode="$3"
	queue+=("$posNode:$priNode:$pathNode")
	sortQueue
}

function UCS
{
	local nodeStart=$1
	local nodeStop=$2
	local existed

	#If Source Node is Destination Node 
	if [[ $nodeStart -eq $nodeStop ]]; then
		result="$nodeStart"
		return 0;
	fi

	# Create an array to check the existence of Node in Queue
	while [[ ${#existed[@]} -lt $_numNode ]]; do
		existed+=("0")
	done

	# Add Source Node into Queue
	local pos=0
	local pri=0
	local path=$pos
	pushBack $pos $pri "$path"
	existed[0]="1"
	while [[ ${#queue[@]} -gt 0 ]]; do
		# take the first element in Queue out
		local first="$(echo "${queue[0]}" | tr ":" " ")"
		unset queue[0]
		queue=("${queue[@]}")
		read pos pri path <<< "$first"
		if [[ $pos -eq $nodeStop ]]; then
			result="$path"
			cost="$pri"
			return 0
		fi
		#Add all Child Node of above node into queue
		for ((i = $pos;i<$_numNode;i++));do
			if [[ ${matrix["$pos:$i"]} -ne 0 ]]; then
				local priChild=$(($pri + ${matrix["$pos:$i"]}))
				local pathChild="${path}->$i"
				#If This Node has not existed in Queue 
				if [[ ${existed[$i]} -eq 0 ]]; then
					# Push it into Queue
					pushBack $i $priChild "$pathChild"
					existed[$i]=1
				#If this node has existed in Queue
				else
					# Update it if its priNum is smaller than old priNum
					local oldPos oldPri oldPath
					for ((j=0; j< ${#queue[@]};j++));do
						local temp="$(echo "${queue[$j]}" | tr ":" " ")"
						read oldPos oldPri oldPath <<< "$temp"
						if [[ $oldPos -eq $i ]]; then
							if [[ $oldPri -gt $priChild ]]; then
								queue[$i]="$i:$priChild:$pathChild"
								sortQueue
								break;
							fi
						fi
					done
				fi
			fi
		done
	done
	return 1
}