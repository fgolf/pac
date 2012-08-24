#!/bin/bash

# command line options for ss2012_plots
signal_region=${1:-0}
lumi=1.0
nbtags=0
suffix="\"png\""
#suffix="\"eps\""
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
#ss2012_plots --sample ttw     --nbtags 0 --sr $signal_region
#ss2012_plots --sample ttw_53X --nbtags 0 --sr $signal_region
#ss2012_plots --sample ttw_53X --nbtags 0 --sr $signal_region --vtx_file plots/vtxreweight/ttw_nvtxs_reweight.root --output plots/sr${signal_region}/ttw_53X_vtxw.root
#ss2012_plots --sample ttw --nbtags 0 --sr $signal_region > logs/ttw_hists.log 2>&1 & 
make_hists ttw     "$options"
make_hists ttw_53X "$options"
#make_hists ttw     "$options --vtx_file plots/vtxreweight/ttw_nvtxs_reweight.root --output plots/sr${signal_region}/ttw_vtxw.root"
#make_hists ttw_53X "$options --vtx_file plots/vtxreweight/ttw_nvtxs_reweight.root --output plots/sr${signal_region}/ttw_53X_vtxw.root"
#
## overlay the hists
root -b -q -l "macros/TTWCompare.C+ ($lumi, $signal_region, \"png\")"
root -b -q -l "macros/TTWCompare.C+ ($lumi, $signal_region, \"eps\")"

