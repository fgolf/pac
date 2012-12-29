#!/bin/bash

lumi=${1:-1.0}
output_name=${2:test}
min_pt=${3:-20}
max_pt=${4:-1000000}
anal_type=${5:-"high_pt"}
nbtags=${6:-2}
charge_option=${7:-0}

# clear the old yield file
echo "" > tables/yields_${output_name}.txt

# do for all signal regions inclusive
for i in {0..8}; do 
    ./scripts/plot_all.sh $i $lumi $output_name $min_pt $max_pt $anal_type $nbtags 2 0 $charge_option; 
done

# do for all signal regions exclusive
if [ $nbtags -eq 2 ]; then
    for i in {1..5}; do 
        ./scripts/plot_all.sh $i $lumi $output_name $min_pt $max_pt $anal_type $nbtags 2 1 $charge_option; 
    done
fi

# summary table
charge_stem=
if [ $charge_option -eq 1 ]; then
    charge_stem="_pp"
elif [ $charge_option -eq -1 ]; then
    charge_stem="_mm"
fi

root -b -q -l "macros/PrintSummaryYieldsWrapper.C (\"$output_name\", $charge_option, 0)"
root -b -q -l "macros/PrintSummaryYieldsWrapper.C (\"$output_name\", $charge_option, 0)" > tables/yields_summary_${output_name}${charge_stem}.txt
root -b -q -l "macros/PrintSummaryYieldsWrapper.C (\"$output_name\", $charge_option, 1)" > temp/temp.tex 
tail -n +3 temp/temp.tex > tables/yields_summary_${output_name}${charge_stem}.tex
rm temp/temp.tex
