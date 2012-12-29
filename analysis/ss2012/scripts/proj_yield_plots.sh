#!/bin/bash

lumi=${1:-1.0}
out_path=${2:-test}
nbtags=${3:-2}
min_pt=${4:-20}
max_pt=${5:-1000000}
anal_type=${6:-"high_pt"}

# do for all signal regions inclusive
for i in {16..58}; do 
    ./scripts/plot_all.sh $i $lumi $out_path $min_pt $max_pt $anal_type $nbtags; 
done
