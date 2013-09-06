#!/bin/bash

verbose=0
njets=2
tag=v10
analysis=ss
path=/nfs-7/userdata/${USER}/babies/ewkino2012/$analysis/$tag/

# make the output dirs

# do the merging
function merge
{
    local name=$1
    local anal_type=$2
    local input=$3
    cmd="ewkino2012_merge_babies --anal_type $anal_type --verbose $verbose --input \"$input\" --output \"${output_path}/${name}.root\" --njets $njets --run_list $run_list" 
    echo $cmd
    echo $cmd > logs/${name}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_${tag}_baby_merge.log 2>&1 &
}

run_list=json/final_19p49fb_cms2.txt # 19.49 

# ss
input_path=/hadoop/cms/store/user/${USER}/babies/ewkino2012/${analysis}/${tag}/${analysis}
output_path=$path
input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012D-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root"
merge data ss $input_files
