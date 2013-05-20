#!/bin/bash

verbose=0
njets=2
tag=V02-05-15
path=/nfs-7/userdata/rwkelley/babies/ss2012/$tag

# make the output dirs

# do the merging
function merge
{
    local name=$1
    local anal_type=$2
    local input=$3
    cmd="ss2012_merge_babies --anal_type $anal_type --verbose $verbose --input \"$input\" --output \"${output_path}/${name}.root\" --njets $njets --run_list $run_list" 
    echo $cmd
    echo $cmd > logs/${name}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_${tag}_baby_merge.log 2>&1 &
}

run_list=json/final_19p49fb_cms2.txt # 19.49 

# high_pt 
input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/high_pt
output_path=$path/hpt
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
merge data_hpt_19p5 high_pt $input_files

# low pt 
input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/low_pt
output_path=$path/lpt
input_files="${input_path}/ElectronHad_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012D-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012D-PromptReco-v1_AOD/*.root"
#merge data_lpt_19p5 low_pt $input_files

# very low pt 
input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/vlow_pt
output_path=$path/vpt
input_files="${input_path}/ElectronHad_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/ElectronHad_Run2012D-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012C-24Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/MuHad_Run2012D-PromptReco-v1_AOD/*.root"
#merge data_vpt_19p5 vlow_pt $input_files
