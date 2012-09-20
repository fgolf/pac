#!/bin/bash

# command line options for ss2012_plots
signal_region=${1:-0}
lumi=${2:-1.0}
out_path=${3:-}

nbtags=2
njets=2
#suffix="\"png\""
suffix="\"eps\""
#options=" --nbtags $nbtags --gr 1 --sr $signal_region --lumi $lumi --fr data/fake_rates/ssFR_data_standard_12Sep2012.root"
options=" --nbtags $nbtags --sr $signal_region --lumi $lumi --fr data/fake_rates/ssFR_data_standard_12Sep2012.root"
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
make_hists data    "$options"
make_hists wz      "$options"
make_hists zz      "$options"
make_hists ttg     "$options"
make_hists ttw     "$options"
make_hists ttww    "$options"
make_hists ttz     "$options"
make_hists wwg     "$options"
make_hists www     "$options"
make_hists wwz     "$options"
make_hists wzz     "$options"
make_hists zzz     "$options"
#make_hists wmwmqq  "$options"

# overlay the hists
#root -b -q -l "macros/OverlaySSPlots.C+ ($lumi, $signal_region, \"$out_path\", \"png\")"
#root -b -q -l "macros/OverlaySSPlots.C++ ($lumi, $signal_region, \"$out_path\", \"eps\")"
#mkdir -p tables
#root -b -q -l "macros/PrintYields.C++    ($signal_region, \"$out_path\")" >> tables/yields_${out_path}.txt
