#!/bin/bash

# command line options for ss2012_plots
signal_region=${1:-0}
lumi=${2:-1.0}
out_path=${3:-}

nbtags=0
njets=2
#options=" --nbtags $nbtags --gr 1 --sr $signal_region --lumi $lumi --fr data/fake_rates/ssFR_data_standard_23Sep2012.root"
options=" --nbtags $nbtags --sr $signal_region --lumi $lumi --fr data/fake_rates/ssFR_data_standard_24Sep2012.root"
mkdir -p logs

function make_hists
{
    local sample=$1
    local args=$2
    cmd="ss2012_plots.exe --sample $sample $args --output plots/$out_path/sr$signal_region/$sample.root > logs/${sample}_hists.log"
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
make_hists t_schan  "$options"
make_hists tw       "$options"

# overlay the hists
root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $signal_region, \"$out_path\", \"png\")"
root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $signal_region, \"$out_path\", \"eps\")"
root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $signal_region, \"$out_path\", \"pdf\")"

# print txt 
mkdir -p tables
root -b -q -l "macros/PrintYields.C+ ($signal_region, \"$out_path\")"    >> tables/yields_${out_path}.txt

# print tex
mkdir -p tables/${out_path}
root -b -q -l "macros/PrintYields.C+ ($signal_region, \"$out_path\", 1)" > temp/temp.tex
tail -n +3 temp/temp.tex > tables/${out_path}/sr${signal_region}_nbtags${nbtags}_inclusive.tex
rm temp/temp.tex

