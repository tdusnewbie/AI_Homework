#!/bin/bash

# Take the Path to neccessary Function
source IOFile.sh
source UCS.sh
source IDS.sh


# Manipulating User Input
fileinput="$1"
declare -u algo="$2"
fileoutput="$3"

# Global Function
declare -A matrix
_numNode=
_source=
_destination=
result=""
cost=0

# Read File 
downloadData "$fileinput"

# Use AlgoRithm
case "$algo" in
	UCS ) UCS $_source $_destination
	;;
	IDS ) IDS $_source $_destination
	;;
esac
result="$(echo "$result" | tr -d ">" | tr "-" " ")"

# Write File 
uploadData "$fileoutput"
# x+y+z=string.size()
# x=y+1
# z=y
# 3y+1=size
# => y= (size-1)/3
