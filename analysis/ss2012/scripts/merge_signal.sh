#!/bin/bash

verbose=0
njets=2
tag=V02-05-09c
path=/nfs-7/userdata/rwkelley/babies/ss2012/$tag

# make the output dirs
mkdir -p logs

# do the merging
function post_process
{
    mkdir -p $output_path
    mkdir -p logs/${tag} 
	local at=$1
    local sample=$2
    local path=$3
    cmd="ss2012_postprocess_signal_baby --sample $sample --input \"${input_path}/${path}/*.root\" --output \"${output_path}/${sample}.root\""
    echo $cmd
    echo $cmd > logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
}

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/signal
#post_process vlow_pt t1tttt     SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1 
post_process vlow_pt sbottomtop SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM

#input_path=/nfs-7/userdata/rwkelley/babies/cms2_V05-03-23_ss2012_V02-05-01
#output_path=$path/signal
#post_process vlow_pt tchiwh /TChiwh/res
