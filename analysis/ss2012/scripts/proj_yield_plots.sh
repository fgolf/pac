#!/bin/bash

lumi=${1:-1.0}
out_path=${2:-}

# do for all signal regions inclusive
for i in {16..56}; do 
    ./scripts/plot_all.sh $i $lumi $out_path; 
done
