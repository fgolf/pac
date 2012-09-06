#!/bin/bash

lumi=${1:-1.0}
out_path=${2:-}

# clear the old yield file
echo "" > tables/yields_${out_path}.txt

# do for all signal regions
for i in {0..8}; do 
    ./scripts/plots.sh $i $lumi $out_path; 
done
