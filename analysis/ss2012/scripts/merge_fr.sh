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

tag=FakeRate15Nov2012
input_path=/hadoop/cms/store/user/rwkelley/babies/fr/$tag
output_path=/nfs-7/userdata/rwkelley/babies/fr/${tag}

#merge "\"$input_path/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root\""               $output_path/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_dml1.txt 2>&1 & 
#merge "\"$input_path/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root\""              $output_path/DoubleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root              > logs/merge_fr_dml2.txt 2>&1 & 
#merge "\"$input_path/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root\""              $output_path/DoubleMu_Run2012D-PromptReco-v1_AOD/merged_frbaby.root              > logs/merge_fr_dml3.txt 2>&1 & 
#merge "\"$input_path/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root\""       $output_path/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root       > logs/merge_fr_dml4.txt 2>&1 & 
#merge "\"$input_path/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root\""               $output_path/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_dml5.txt 2>&1 & 
#merge "\"$input_path/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root\""               $output_path/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged_frbaby.root               > logs/merge_fr_dml6.txt 2>&1 & 
#
#merge "\"$input_path/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root\""               $output_path/SingleMu_Run2012C-24Aug2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_sml1.txt 2>&1 & 
#merge "\"$input_path/SingleMu_Run2012C-PromptReco-v2_AOD/*.root\""              $output_path/SingleMu_Run2012C-PromptReco-v2_AOD/merged_frbaby.root              > logs/merge_fr_sml2.txt 2>&1 & 
#merge "\"$input_path/SingleMu_Run2012D-PromptReco-v1_AOD/*.root\""              $output_path/SingleMu_Run2012D-PromptReco-v1_AOD/merged_frbaby.root              > logs/merge_fr_sml3.txt 2>&1 & 
#merge "\"$input_path/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root\""       $output_path/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root       > logs/merge_fr_sml4.txt 2>&1 & 
#merge "\"$input_path/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root\""               $output_path/SingleMu_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_sml5.txt 2>&1 & 
#merge "\"$input_path/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root\""               $output_path/SingleMu_Run2012B-13Jul2012-v1_AOD/merged_frbaby.root               > logs/merge_fr_sml6.txt 2>&1 & 
#
#merge "\"$input_path/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_del1.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root\""        $output_path/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged_frbaby.root        > logs/merge_fr_del2.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root\""        $output_path/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged_frbaby.root        > logs/merge_fr_del3.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root\"" $output_path/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged_frbaby.root > logs/merge_fr_del4.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_del5.txt 2>&1 & 
#merge "\"$input_path/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root\""         $output_path/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged_frbaby.root         > logs/merge_fr_del6.txt 2>&1 & 

#merge "\"$input_path/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\"" $output_path/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root >& logs/merge_fr_qcd1.log  &
#merge "\"$input_path/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root\""               $output_path/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/merged_frbaby.root               >& logs/merge_fr_qcd2.log  &
#merge "\"$input_path/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root\""   $output_path/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/merged_frbaby.root   >& logs/merge_fr_qcd3.log  &
#merge "\"$input_path/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root\""                 $output_path/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/merged_frbaby.root                 >& logs/merge_fr_qcd4.log  &
#merge "\"$input_path/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root\""               $output_path/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/merged_frbaby.root               >& logs/merge_fr_qcd5.log  &
#merge "\"$input_path/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root\""     $output_path/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/merged_frbaby.root     >& logs/merge_fr_qcd6.log  &
#merge "\"$input_path/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\""   $output_path/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root   >& logs/merge_fr_qcd7.log  &
#merge "\"$input_path/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\""   $output_path/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root   >& logs/merge_fr_qcd8.log  &
#merge "\"$input_path/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root\""                 $output_path/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/merged_frbaby.root                 >& logs/merge_fr_qcd9.log  &
#merge "\"$input_path/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\""   $output_path/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root   >& logs/merge_fr_qcd10.log &
#merge "\"$input_path/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root\""                 $output_path/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/merged_frbaby.root                 >& logs/merge_fr_qcd11.log &
#merge "\"$input_path/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\""                  $output_path/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root                  >& logs/merge_fr_qcd12.log &
#merge "\"$input_path/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\""  $output_path/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root  >& logs/merge_fr_qcd13.log &
#merge "\"$input_path/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root\""                $output_path/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/merged_frbaby.root                >& logs/merge_fr_qcd14.log &

merge "\"$input_path/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\"" $output_path/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root >& logs/merge_fr_wjets.log &
merge "\"$input_path/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root\"" $output_path/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_frbaby.root >& logs/merge_fr_dyll.log &

