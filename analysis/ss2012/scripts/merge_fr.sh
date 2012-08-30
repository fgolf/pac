#!/bin/bash

function merge
{
    local input_file=$1
    local output_file=$2 
    cmd="merge_tchain --input $input_file --output $output_file --tree tree --option Fast"
    echo $cmd
    eval $cmd
}
# data

#tag=FakeRate20May2012_3p95fb
#input_path=/hadoop/cms/store/user/rwkelley/babies/fr/$tag
#output_path=/nfs-7/userdata/rwkelley/babies/fr/$tag
#
#merge "\"$input_path/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root\""   $output_path/DoubleElectron_Run2012A-PromptReco-v1_AOD/merged_frbaby.root > logs/merge_fr_dela.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root\""   $output_path/DoubleElectron_Run2012B-PromptReco-v1_AOD/merged_frbaby.root > logs/merge_fr_delb.txt 2>&1 &
#merge "\"$input_path/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root\""         $output_path/DoubleMu_Run2012A-PromptReco-v1_AOD/merged_frbaby.root       > logs/merge_fr_dmua.txt 2>&1 &
#merge "\"$input_path/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root\""         $output_path/DoubleMu_Run2012B-PromptReco-v1_AOD/merged_frbaby.root       > logs/merge_fr_dmub.txt 2>&1 &
#merge "\"$input_path/SingleMu_Run2012A-PromptReco-v1_AOD/*.root\""         $output_path/SingleMu_Run2012A-PromptReco-v1_AOD/merged_frbaby.root       > logs/merge_fr_mega.txt 2>&1 &
#merge "\"$input_path/SingleMu_Run2012B-PromptReco-v1_AOD/*.root\""         $output_path/SingleMu_Run2012B-PromptReco-v1_AOD/merged_frbaby.root       > logs/merge_fr_megb.txt 2>&1 &

tag=FakeRate20May2012
input_path=/hadoop/cms/store/user/fgolf/babies/fr/$tag
output_path=/nfs-7/userdata/rwkelley/babies/fr/${tag}_2012Cv2

merge "\"$input_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root\""   $output_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged_frbaby.root > logs/merge_fr_dela.txt 2>&1 & 
merge "\"$input_path/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root\""         $output_path/DoubleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root       > logs/merge_fr_dmua.txt 2>&1 &
merge "\"$input_path/SingleMu_Run2012C-PromptReco-v2_AOD/*.root\""         $output_path/SingleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root       > logs/merge_fr_megb.txt 2>&1 &
