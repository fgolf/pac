#!/bin/bash

verbose=0
njets=2

# make the output dirs

# do the merging
function merge
{
    local name=$1
    local input=$2
    cmd="ss2012_merge_babies --verbose $verbose --input "$input" --output \"${output_path}/${name}.root\" --njets $njets --run_list $run_list" 
    echo $cmd
    echo $cmd > logs/${name}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_baby_merge.log 2>&1 &
    #eval $cmd
}

# 2012ABC reprocessed
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/17Sep
#output_path=temp
#run_list=json/preapproval_cms2.txt # 11.38 
#input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"
#merge data_2012ABC_preaproval_11p38 $input_files

# 2012ABC reprocessed (no 2012C v1)
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/20Sep
#output_path=babies
#run_list=json/preapproval_cms2.txt # 10.88 
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v1_AOD/*.root"
#merge data_2012Cv1_0p50fb $input_files

# 2012A/B reprocessed (no 2012C v1)
input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/22Sep
output_path=babies_njets${njets}
run_list=json/preapproval_v2_cms2.txt # 10.88 
input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"
merge data_2012ABC_preapproval_10p88 $input_files
