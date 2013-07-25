#!/bin/bash

verbose=0
tag=v8
ana_type=ss
path=/nfs-7/userdata/${USER}/babies/ewkino2012/${ana_type}/$tag

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
    local br=${4:-1.}
    cmd="ewkino2012_postprocess_signal_baby --sample $sample --input \"${input_path}/${path}/res/*.root\" --output \"${output_path}/${sample}.root\" --br $br"
    echo $cmd > logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
}

input_path=/home/users/fgolf/pac/analysis/ewkino2012/crab/test_crab/
output_path=$path/signal
post_process ss tchiwh TChiwh-test_fgolf-TChiwh-test-6138c231f814ac3df24f1150dfcad736 0.01382
