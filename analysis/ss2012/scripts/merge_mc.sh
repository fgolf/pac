#!/bin/bash

verbose=0

# make the output dirs
mkdir -p logs

# do the merging
function merge
{
    mkdir -p $output_path
    local name=$1
    local path=$2
    cmd="ss2012_merge_babies --verbose $verbose --input \"${input_path}/${path}/*.root\"  --output \"${output_path}/${name}.root\""
    echo $cmd > logs/${name}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${name}_baby_merge.log 2>&1 &
}

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/52X/v1
output_path=/nfs-7/userdata/rwkelley/babies/ss2012/52X/v1
#output_path=babies/52X
#merge wwg_fast    8TeV_WWGJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3
#merge www_fast    8TeV_WWWJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3
#merge wwz_fast    8TeV_WWZNoGstarJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3
#merge wzz_fast    8TeV_WZZNoGstarJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3
#merge zzz_fast    8TeV_ZZZNoGstarJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3
#merge t1tttt_fast SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1
#merge t1tttt      SMS-T1ttttProtoScan_Mgluino-350to1200_mLSP-0to400_8TeV-Pythia6Z_StoreResults-PU_START52_V5_FullSim-v1
#merge ttw         TTWJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge ttg         TTGJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge ttw         TTWJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge ttww        TTWWJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge ttz         TTZJets_8TeV-madgraph_v2_Summer12-PU_S7_START52_V9-v1
#merge www         WWWJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge wwz         WZZNoGstarJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge zzz         ZZZNoGstarJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1
#merge wz          WZTo3LNu_TuneZ2star_8TeV_pythia6_tauola_Summer12-PU_S7_START52_V9-v1
#merge zz          ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v3

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/53X/v1
output_path=/nfs-7/userdata/rwkelley/babies/ss2012/53X/v1
#output_path=babies
merge wz        WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge zz        ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ttg       TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ttjets    TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ttw       TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ttww      TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ttz       TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
merge wwg       WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge www       WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge wwz       WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge wzz       WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge zzz       ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ww_ds     WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
