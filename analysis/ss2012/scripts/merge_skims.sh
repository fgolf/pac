#!/bin/bash

function merge
{
    local input_path=$1
    local output_path=$2 
    local dataset_name=$3
    local output_file=${output_path}/${dataset_name}/ntuple_skim.root
    local input_file="\"${input_path}/${dataset_name}/*.root\""
    local log_name=logs/merge_${dataset_name}.log
    cmd="merge_tchain --input $input_file --output $output_file --tree Events --option Fast"
    echo $cmd
    echo $cmd > $log_name
    eval $cmd >> $log_name 2>&1 &
}
# data

# data
# -------------------------------------------------------#

input_path=/hadoop/cms/store/user/rwkelley/skims/ss2012/29Sep
output_path=/nfs-7/userdata/rwkelley/skims/ss2012/53X/v1
#merge ${input_path} ${output_path} DoubleMu_Run2012A-PromptReco-v1_AOD
#merge ${input_path} ${output_path} DoubleMu_Run2012B-PromptReco-v1_AOD
merge ${input_path} ${output_path} DoubleMu_Run2012C-PromptReco-v1_AOD
merge ${input_path} ${output_path} DoubleMu_Run2012A-13Jul2012-v1_AOD
merge ${input_path} ${output_path} DoubleMu_Run2012A-recover-06Aug2012-v1_AOD
merge ${input_path} ${output_path} DoubleMu_Run2012C-PromptReco-v2_AOD
merge ${input_path} ${output_path} DoubleMu_Run2012B-13Jul2012-v4_AOD
#merge ${input_path} ${output_path} MuEG_Run2012A-PromptReco-v1_AOD
#merge ${input_path} ${output_path} MuEG_Run2012B-PromptReco-v1_AOD
merge ${input_path} ${output_path} MuEG_Run2012B-13Jul2012-v1_AOD
merge ${input_path} ${output_path} MuEG_Run2012A-13Jul2012-v1_AOD
merge ${input_path} ${output_path} MuEG_Run2012C-PromptReco-v1_AOD
merge ${input_path} ${output_path} MuEG_Run2012A-recover-06Aug2012-v1_AOD
merge ${input_path} ${output_path} MuEG_Run2012C-PromptReco-v2_AOD
#merge ${input_path} ${output_path} DoubleElectron_Run2012A-PromptReco-v1_AOD
#merge ${input_path} ${output_path} DoubleElectron_Run2012B-PromptReco-v1_AOD
merge ${input_path} ${output_path} DoubleElectron_Run2012B-13Jul2012-v1_AOD
merge ${input_path} ${output_path} DoubleElectron_Run2012A-13Jul2012-v1_AOD
merge ${input_path} ${output_path} DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD
merge ${input_path} ${output_path} DoubleElectron_Run2012C-PromptReco-v1_AOD
merge ${input_path} ${output_path} DoubleElectron_Run2012C-PromptReco-v2_AOD

input_path=/hadoop/cms/store/user/rwkelley/skims/ss2012/53X/v1
output_path=/nfs-7/userdata/rwkelley/skims/ss2012/53X/v1
merge ${input_path} ${output_path} DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} SUSY_LM6_sftsht_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} SUSY_LM9_sftsht_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ${input_path} ${output_path} ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
