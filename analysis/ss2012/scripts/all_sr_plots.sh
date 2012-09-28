#!/bin/bash

lumi=${1:-1.0}
out_path=${2:-}

# clear the old yield file
echo "" > tables/yields_${out_path}.txt

# do for all signal regions inclusive
for i in {0..8}; do 
    ./scripts/plot_all.sh $i $lumi $out_path; 
done

# do for all signal regions exclusive
for i in {1..4}; do 
    ./scripts/plot_all.sh $i $lumi $out_path 1; 
done

# summary table
root -b -q -l "macros/PrintSummaryYieldsWrapper.C (\"$out_path\", 0)"
root -b -q -l "macros/PrintSummaryYieldsWrapper.C (\"$out_path\", 0)" > tables/yields_summary_${out_path}.txt
root -b -q -l "macros/PrintSummaryYieldsWrapper.C (\"$out_path\", 1)" > temp/temp.tex 
tail -n +3 temp/temp.tex > tables/yields_summary_${out_path}.tex
rm temp/temp.tex
