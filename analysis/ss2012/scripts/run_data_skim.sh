#!/bin/bash

verbose=0

# make the output dirs

# do the merging
function run
{
    local name=$1
    local input=$2
    local sample=$3
    cmd="ss2012_analysis --verbose $verbose --sample $sample --input \"${input}\"  --output \"${output_path}/${name}.root\" --run_list $run_list" 
    echo $cmd > logs/run_${name}.log 2>&1 &
    eval $cmd >> logs/run_${name}.log 2>&1 &
    #echo $cmd
    #eval $cmd
}

# DoubleElectron_Run2012A-13Jul2012-v1_AOD
# DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD
# DoubleElectron_Run2012B-13Jul2012-v1_AOD
# DoubleElectron_Run2012C-PromptReco-v1_AOD
# DoubleElectron_Run2012C-PromptReco-v2_AOD
# DoubleMu_Run2012A-13Jul2012-v1_AOD
# DoubleMu_Run2012A-recover-06Aug2012-v1_AOD
# DoubleMu_Run2012B-13Jul2012-v4_AOD
# DoubleMu_Run2012C-PromptReco-v1_AOD
# DoubleMu_Run2012C-PromptReco-v2_AOD
# MuEG_Run2012A-13Jul2012-v1_AOD
# MuEG_Run2012A-recover-06Aug2012-v1_AOD
# MuEG_Run2012B-13Jul2012-v1_AOD
# MuEG_Run2012C-PromptReco-v1_AOD
# MuEG_Run2012C-PromptReco-v2_AOD


# 2012A/B reprocessed 13July
input_path=/nfs-7/userdata/rwkelley/skims/ss2012/53X/v2
output_path=babies2
run_list=json/preapproval_cms2.txt
input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v1_AOD/*.root"
input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v2_AOD/*.root"
input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"
run data_2012ABC_skim_preapproval_10p88 $input_files data
