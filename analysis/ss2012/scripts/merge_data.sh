#!/bin/bash

verbose=0

# make the output dirs

# do the merging
function merge
{
    local name=$1
    local input=$2
    cmd="ss2012_merge_babies --verbose $verbose --input "$input"  --output \"${output_path}/${name}.root\" --run_list $run_list" 
    echo $cmd > logs/${name}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_baby_merge.log 2>&1 &
    #echo $cmd
    #eval $cmd
}

# 2012 A/B prompt
input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/29Aug
output_path=babies/52X
run_list=json/Cert_190456-195947_8TeV_PromptReco_Collisions12_v2_cms2.txt
mkdir -p $output_path
mkdir -p logs
input_files="${input_path}/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012B-PromptReco-v1_AOD/*.root"
merge data $input_files

# 2012 C
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/29Aug
#output_path=babies/53X
#run_list=json/Cert_190456-200601_8TeV_PromptReco_Collisions12_cms2.txt
#input_files="${input_path}/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v1_AOD/*.root"
#merge data_2012C $input_files
#
## 2012A/B reprocessed
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/29Aug
#output_path=babies/53X
#run_list=json/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_cms2.txt
#input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v4_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v4_AOD/*.root"
#merge data_2012AB_13Jul2012 $input_files

# merge into one baby
#output_path=babies/53X
#run_list=\"\"
#input_files="${output_path}/data_2012C.root,${output_path}/data_2012AB_13Jul2012.root"
#merge data $input_files
