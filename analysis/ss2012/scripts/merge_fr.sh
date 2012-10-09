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

#tag=FakeRate20May2012
#input_path=/hadoop/cms/store/user/fgolf/babies/fr/$tag
#output_path=/nfs-7/userdata/rwkelley/babies/fr/${tag}_2012Cv2
#
#merge "\"$input_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root\""   $output_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged_frbaby.root > logs/merge_fr_dela.txt 2>&1 & 
#merge "\"$input_path/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root\""         $output_path/DoubleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root       > logs/merge_fr_dmua.txt 2>&1 &
#merge "\"$input_path/SingleMu_Run2012C-PromptReco-v2_AOD/*.root\""         $output_path/SingleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root       > logs/merge_fr_megb.txt 2>&1 &

#tag=FakeRate20May2012_submit2
#input_path=/hadoop/cms/store/user/fgolf/babies/fr/$tag
#output_path=/nfs-7/userdata/rwkelley/babies/fr/${tag}
#
#merge "\"$input_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root\""        $output_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged_frbaby.root        > logs/merge_fr_del1.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_del2.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root\""        $output_path/DoubleElectron_Run2012A-PromptReco-v1_AOD/merged_frbaby.root        > logs/merge_fr_del3.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root\"" $output_path/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root > logs/merge_fr_del4.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_del5.txt 2>&1 & 

tag=FakeRate20May2012_12p26fb
input_path=/hadoop/cms/store/user/rwkelley/babies/fr/$tag
output_path=/nfs-7/userdata/rwkelley/babies/fr/${tag}

merge "\"$input_path/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root\""               $output_path/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_dml1.txt 2>&1 & 
merge "\"$input_path/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root\""              $output_path/DoubleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root              > logs/merge_fr_dml1.txt 2>&1 & 
merge "\"$input_path/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root\""       $output_path/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root       > logs/merge_fr_dml4.txt 2>&1 & 
merge "\"$input_path/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root\""               $output_path/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_dml2.txt 2>&1 & 
merge "\"$input_path/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root\""               $output_path/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged_frbaby.root               > logs/merge_fr_dml5.txt 2>&1 & 

merge "\"$input_path/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root\""               $output_path/SingleMu_Run2012C-24Aug2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_sml1.txt 2>&1 & 
merge "\"$input_path/SingleMu_Run2012C-PromptReco-v2_AOD/*.root\""              $output_path/SingleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root              > logs/merge_fr_sml1.txt 2>&1 & 
merge "\"$input_path/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root\""       $output_path/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root       > logs/merge_fr_sml4.txt 2>&1 & 
merge "\"$input_path/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root\""               $output_path/SingleMu_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_sml2.txt 2>&1 & 
merge "\"$input_path/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root\""               $output_path/SingleMu_Run2012B-13Jul2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_sml5.txt 2>&1 & 

merge "\"$input_path/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_sml1.txt 2>&1 & 
merge "\"$input_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root\""        $output_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged_frbaby.root        > logs/merge_fr_sml1.txt 2>&1 & 
merge "\"$input_path/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root\"" $output_path/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root > logs/merge_fr_sml4.txt 2>&1 & 
merge "\"$input_path/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_sml2.txt 2>&1 & 
merge "\"$input_path/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_sml5.txt 2>&1 & 
