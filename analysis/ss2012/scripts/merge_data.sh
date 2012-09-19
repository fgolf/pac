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

# 2012 A/B prompt 3.95
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/29Aug
#output_path=babies/52X
#run_list=json/Cert_190456-195947_8TeV_PromptReco_Collisions12_v2_cms2.txt
#mkdir -p $output_path
#mkdir -p logs
#input_files="${input_path}/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-PromptReco-v1_AOD/*.root"
#merge data_3p95_noskim $input_files

# 2012 A/B prompt 5.1
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/03Sep
#output_path=babies/52X
#run_list=json/Cert_190456-196531_8TeV_PromptReco_Collisions12_cms2.txt # 5.097 /fb 
#mkdir -p $output_path
#mkdir -p logs
#input_files="${input_path}/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-PromptReco-v1_AOD/*.root"
#merge data_2012AB_prompt_5p1 $input_files

# 2012A/B reprocessed with prompt json
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/03Aug
#output_path=babies/53X
#run_list=json/Cert_190456-196531_8TeV_PromptReco_Collisions12_cms2.txt 
#input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
#merge data_2012AB_13july2012_5p1_promptjson $input_files

# 2012A/B reprocessed
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/17Sep
#output_path=babies2
#run_list=json/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_cms2.txt # 5p21
#input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
#merge data_2012AB_13july2012_5p21 $input_files

# 2012A/B reprocessed
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/17Sep
#output_path=babies2
#run_list=json/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_cms2.txt # 0.082 /fb 
#input_files="${input_files},${input_path}/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#merge data_2012AB_06aug2012_0p082 $input_files

## 2012A/B reprocessed
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/03Aug
#output_path=babies/53X
##run_list=json/Cert_190456-200601_8TeV_PromptReco_Collisions12_cms2.txt  # 8.49
##run_list=json/Cert_190456-196509_8TeV_PromptReco_Collisions12_cms2.txt   # 5.05
#run_list=json/Cert_190456-201678_8TeV_PromptReco_Collisions12_cms2.txt   # 9.707
#run_list=json/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_cms2.txt # 
#input_files="${input_path}/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-13Jul2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012A-recover-06Aug2012-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012B-13Jul2012-v1_AOD/*.root"
##merge data_2012AB_rereco_9p71 $input_files

# 2012 C
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/17Sep
#run_list=json/Cert_190456-201678_8TeV_PromptReco_Collisions12_cms2.txt   # 9.707 for prompt
#output_path=babies2
#input_files="${input_path}/DoubleMu_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/MuEG_Run2012C-PromptReco-v2_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v1_AOD/*.root"
#input_files="${input_files},${input_path}/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"
#merge data_2012Cv12_4p61 $input_files

# merge into one baby
input_path=babies2
output_path=babies2
run_list=\"\"
input_files="${output_path}/data_2012Cv12_4p61.root"
input_files="${input_files},${output_path}/data_2012AB_06aug2012_0p082.root"
input_files="${input_files},${output_path}/data_2012AB_13july2012_5p21.root"
merge data_2012ABC_9p90 $input_files
