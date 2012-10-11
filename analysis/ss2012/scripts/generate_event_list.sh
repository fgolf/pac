#!/bin/bash

raw=$(root -b -q -l macros/SSEventList.C | awk -F'*' '{print $3 $4 $5 $6}' | grep /)
current_dataset=""
prev_dataset=""
outfile=""
mkdir -p $SS/edm

IFS=$'\n'
for line in $raw
do
    current_dataset=`echo $line | awk '{print $1}'`
    if [ "$prev_dataset" != "$current_dataset" ]; then
        outfile="$SS/edm/`echo ${current_dataset}|sed 's|/|_|g' | cut -c2-`.txt"
        echo $current_dataset > $outfile 
    fi
    echo "`echo $line | awk '{print $2"," $3"," $4}'`" >> $outfile

    prev_dataset=$current_dataset
done
unset IFS

