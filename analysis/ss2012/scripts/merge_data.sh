#!/bin/bash

verbose=0
input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/20Aug
output_path=babies/52X
run_list=json/Cert_190456-195947_8TeV_PromptReco_Collisions12_v2_cms2.txt

# make the output dirs
mkdir -p $output_path
mkdir -p logs

# do the merging
function merge
{
    local name=$1
    local input=$2
    cmd="ss2012_merge_babies --verbose $verbose --input "$input"  --output \"${output_path}/${name}.root\" --run_list $run_list" 
    echo $cmd > logs/${name}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_baby_merge.log 2>&1 &
}

input_files="${input_path}/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012B-PromptReco-v1_AOD/*.root"

merge data $input_files
