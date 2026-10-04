#!/bin/bash 

if [[ $# -ne 2 ]]; then
  echo "ERROR (1) writer.sh: please run as writer.sh <writefile> <writestr>"
  exit 1
fi 

writefile=$1
writestr=$2
directory=$(dirname $writefile)

mkdir -p $directory
touch $writefile
echo $writestr >> $writefile

