#!/bin/bash

# command line options for ss2012_plots
signal_region=${1:-0}
lumi=${2:-1.0}
output_name=${3:-}
min_pt=${4:-20}
max_pt=${5:-1000000}
anal_type=${6:-"high_pt"}
nbtags=${7:-2}
exclusive=${8:-0}
charge_option=${9:-0}  # -1 means --, 1 means ++, anything else means both
options=" --nbtags $nbtags --sr $signal_region --excl $exclusive --lumi $lumi --fr data/fake_rates/ssFR_data_standard_26Nov2012.root --charge $charge_option --min_pt $min_pt --max_pt $max_pt --anal_type $anal_type"

charge_stem=
if [ $charge_option -eq 1 ]; then
    charge_stem="_pp"
elif [ $charge_option -eq -1 ]; then
    charge_stem="_mm"
fi

mkdir -p logs

function make_hists
{
    local sample=$1
    local args=$2
	if [ $exclusive -eq 1 ]; then
    	local cmd="ss2012_plots.exe --sample $sample $args --output plots/$output_name/ex_sr$signal_region/${sample}${charge_stem}.root > logs/${sample}${charge_stem}_hists.log"
	else
    	local cmd="ss2012_plots.exe --sample $sample $args --output plots/$output_name/sr$signal_region/${sample}${charge_stem}.root > logs/${sample}${charge_stem}_hists.log"
	fi
    echo $cmd
    eval $cmd
}

# make the hists
make_hists data     "$options"
make_hists ww       "$options"
make_hists wz       "$options"
make_hists zz       "$options"
make_hists ttg      "$options"
make_hists ttw      "$options"
make_hists ttww     "$options"
make_hists ttz      "$options"
make_hists wwg      "$options"
make_hists www      "$options"
make_hists wwz      "$options"
make_hists wzz      "$options"
make_hists zzz      "$options"
make_hists wmwmqq   "$options"
make_hists wpwpqq   "$options"
make_hists wgstar2e "$options"
make_hists wgstar2m "$options"
make_hists wgstar2t "$options"
make_hists ww_ds    "$options"
make_hists dy       "$options"
make_hists wjets    "$options"
make_hists ttjets   "$options"
make_hists ttdil    "$options"
make_hists ttotr    "$options"
make_hists ttslb    "$options"
make_hists ttslo    "$options"
make_hists t_schan  "$options"
make_hists t_tchan  "$options"
make_hists t_tw     "$options"

# if exclusive SR, add 10 so $signal_region
if [ $exclusive -eq 1 ]; then
	sr_num=$((10+signal_region))
else
   	sr_num=$signal_region
fi

# overlay the hists
if [[ $charge_option -eq 1 || $charge_option -eq 1 ]]; then
    mkdir -p plots/${output_name}
    root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $sr_num, \"$output_name\", \"png\")"
    root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $sr_num, \"$output_name\", \"eps\")"
    root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $sr_num, \"$output_name\", \"pdf\")"
fi

# print txt 
mkdir -p tables
root -b -q -l "macros/PrintYields.C+ ($sr_num, \"$output_name\", $charge_option, 0)" >> tables/yields_${output_name}.txt
cat tables/yields_${output_name}.txt

# print tex
mkdir -p tables/${output_name}
root -b -q -l "macros/PrintYields.C+ ($sr_num, \"$output_name\", $charge_option, 1)" > temp/temp.tex
if [ $exclusive -eq 1 ]; then
	tail -n +3 temp/temp.tex > tables/${output_name}/sr${signal_region}_nbtags${nbtags}_exclusive.tex
else
	tail -n +3 temp/temp.tex > tables/${output_name}/sr${signal_region}_nbtags${nbtags}_inclusive.tex
fi
rm temp/temp.tex
