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

#Read File 
downloadData "$fileinput"

# Use AlgoRithm
UCS $_source $_destination
# echo "Vay Path la: $result"
# echo "${#result}"

uploadData "$fileoutput"
# x+y+z=string.size()
# x=y+1
# z=y
# 3y+1=size
# => y= (size-1)/3
