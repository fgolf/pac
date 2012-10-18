#!/bin/bash

verbose=0

# make the output dirs
mkdir -p logs

# do the merging
function merge
{
    mkdir -p $output_path
    local name=$1
    local path=$2
    cmd="merge_tchain --input \"${input_path}/${path}/*.root\"  --output \"${output_path}/${name}.root\" --tree tree --option Fast"
    echo $cmd > logs/${name}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_baby_merge.log 2>&1 &
}


input_path=/hadoop/cms/store/user/rwkelley/babies/outreach/52X/v1
output_path=babies_outreach2
merge glusbottom glusbottom
merge glustop    glustop
merge sbottomtop sbottomtop
merge t1tttt     t1tttt

#input_path=/hadoop/cms/store/user/rwkelley/babies/outreach/53X/v1
#output_path=babies_outreach
#merge ttjets   TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge lm6      SUSY_LM6_sftsht_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge lm9      SUSY_LM9_sftsht_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1


