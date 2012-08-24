#!/bin/bash

# samples to run on
samples=(t1tttt ttw ttz)

# command line options for ss2012_plots
signal_region=${1:-0}
lumi=20.0
nbtags=2
#suffix="\"png\""
suffix="\"eps\""
options=" --nbtags $nbtags --sr $signal_region"

function make_hists
{
    local sample=$1
    local args=$2
    cmd="ss2012_plots --sample $sample $args > logs/${sample}_hists.log"
    #cmd="ss2012_plots --sample $sample $args"
    echo $cmd
    eval $cmd
}

# make the hists
#make_hists t1tttt "--output plots/sr${signal_region}/t1tttt_mglu600_mlsp0.root  --mglu  600 --mlsp 0 $options"
#make_hists t1tttt "--output plots/sr${signal_region}/t1tttt_mglu600_mlsp100.root  --mglu  600 --mlsp 100 $options"
make_hists t1tttt_fastsim "--output plots/sr${signal_region}/t1tttt_mglu1100_mlsp0.root --mglu 1100 --mlsp 0 $options"
make_hists t1tttt_fastsim "--output plots/sr${signal_region}/t1tttt_mglu1100_mlsp600.root --mglu 1100 --mlsp 600 $options"
make_hists ttz     "$options"
make_hists ttw     "$options"
make_hists ttjets  "$options"
make_hists wz      "$options"
make_hists zz      "$options"

# overlay the hists
root -b -q -l "macros/OverlayPlots.C+ ($lumi, $signal_region, $suffix)"

