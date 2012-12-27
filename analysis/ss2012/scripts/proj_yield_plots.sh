#!/bin/bash

lumi=${1:-1.0}
out_path=${2:-test}
nbtags=${3:-2}

# do for all signal regions inclusive
for i in {16..58}; do 
    ./scripts/plot_all.sh $i $lumi $out_path 20 100000 high_pt $nbtags; 
done
