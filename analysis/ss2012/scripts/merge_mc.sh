#!/bin/bash

verbose=0
njets=2
tag=V03-02-02
path=/nfs-7/userdata/rwkelley/babies/ss2012/$tag


# make the output dirs
mkdir -p logs

# do the merging
function merge
{
    mkdir -p $output_path
    mkdir -p logs/${version} 
    local at=$1
    local name=$2
    local path=$3
    cmd="ss2012_merge_babies --anal_type $at --verbose $verbose --input \"${input_path}/${path}/*.root\"  --output \"${output_path}/${name}.root\" --njets $njets"
    echo $cmd
    echo $cmd > logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
}

function merge_nofilter
{
    mkdir -p $output_path
    mkdir -p logs/${version} 
    local at=$1
    local name=$2
    local path=$3
    cmd="ss2012_merge_babies --anal_type $at --verbose $verbose --input \"${input_path}/${path}/*.root\"  --output \"${output_path}/${name}.root\" --njets $njets --filter 0"
    echo $cmd
    echo $cmd > logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
}

function merge_nofilter2
{
    mkdir -p $output_path
    mkdir -p logs/${version} 
    local at=$1
    local name=$2
    local input=$3
    cmd="ss2012_merge_babies --anal_type $at --verbose $verbose --input \"${input}\"  --output \"${output_path}/${name}.root\" --njets $njets --filter 0"
    echo $cmd
    echo $cmd > logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
}

function merge2
{
    mkdir -p $output_path
    mkdir -p logs/${version} 
    local at=$1
    local name=$2
    local input=$3
    cmd="ss2012_merge_babies --anal_type $at --verbose $verbose --input \"$input\" --output \"${output_path}/${name}.root\" --njets $njets"
    echo $cmd
    echo $cmd > logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
}

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/${tag}/mc
output_path=$path/hpt
#merge high_pt dy             DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wjets_v1       WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wjets_v2       WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2
#merge high_pt wz             WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt zz             ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ww             WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ttg            TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ttw            TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ttww           TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ttz            TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt tbz            TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
#merge high_pt wwg            WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt www            WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wwz            WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wzz            WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt zzz            ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wmwmqq         WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wpwpqq         WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ww_ds          WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wgstar2e       WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wgstar2m       WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wgstar2t       WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge2 high_pt t_schan       "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#merge2 high_pt t_tchan       "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#merge2 high_pt t_tw          "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#merge high_pt ttjets         TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ttjets_powheg1 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt ttjets_powheg2 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
#merge high_pt ttslq          TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1   
#merge high_pt ttdil          TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 
#merge high_pt ttotr          TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 
#merge high_pt wh_zh_tth_hww  WH_ZH_TTH_HToWW_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wh_zh_tth_hzz  WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt wh_zh_tth_htt  WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/lpt
#merge low_pt dy             DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wjets_v1       WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wjets_v2       WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2
#merge low_pt wz             WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt zz             ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ww             WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ttg            TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ttw            TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ttww           TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ttz            TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt tbz            TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
#merge low_pt wwg            WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt www            WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wwz            WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wzz            WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt zzz            ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wmwmqq         WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wpwpqq         WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ww_ds          WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wgstar2e       WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wgstar2m       WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wgstar2t       WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge2 low_pt t_schan       "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#merge2 low_pt t_tchan       "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#merge2 low_pt t_tw          "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#merge low_pt ttjets         TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt ttjets_powheg1 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1 
#merge low_pt ttjets_powheg2 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
#merge low_pt ttslq          TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1   
#merge low_pt ttdil          TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 
#merge low_pt ttotr          TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 
#merge low_pt wh_zh_tth_hww  WH_ZH_TTH_HToWW_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wh_zh_tth_hzz  WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt wh_zh_tth_htt  WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/vpt
# merge vlow_pt dy            DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge vlow_pt wjets_v1      WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge vlow_pt wjets_v2      WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2
# merge vlow_pt wz            WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt zz            ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ww            WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ttg           TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ttw           TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ttww          TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ttz           TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt tbz           TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
# merge vlow_pt wwg           WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt www           WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wwz           WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wzz           WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt zzz           ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wmwmqq        WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wpwpqq        WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ww_ds         WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wgstar2e      WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wgstar2m      WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wgstar2t      WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge2 vlow_pt t_schan      "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
# merge2 vlow_pt t_tchan      "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
# merge2 vlow_pt t_tw         "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
# merge vlow_pt ttjets         TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt ttjets_powheg1 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1 
# merge vlow_pt ttjets_powheg2 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
# merge vlow_pt ttslq          TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1   
# merge vlow_pt ttdil          TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 
# merge vlow_pt ttotr          TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 
# merge vlow_pt wh_zh_tth_hww  WH_ZH_TTH_HToWW_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wh_zh_tth_hzz  WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# merge vlow_pt wh_zh_tth_htt  WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
# 
# # combined wjets
# merge2 high_pt wjets "${input_path}/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1*/root,${input_path}/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root"
# merge2 low_pt  wjets "${input_path}/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1*/root,${input_path}/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root"
# merge2 vlow_pt wjets "${input_path}/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1*/root,${input_path}/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root"

#tag=V02-05-09e
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
#path=/nfs-7/userdata/rwkelley/babies/ss2012/$tag
#output_path=$path/signal
#merge_nofilter vlow_pt sbottomtop SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM 
#merge_nofilter vlow_pt t1tttt SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1 

#tag=V02-05-13
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/${tag}/mc
#path=/nfs-7/userdata/rwkelley/babies/ss2012/${tag}
#output_path=$path/mc
#input_files="${input_path}/W1JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#input_files=$input_files,"${input_path}/W2JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#input_files=$input_files,"${input_path}/W3JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#input_files=$input_files,"${input_path}/W4JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
##echo ${input_files}
#merge2 vlow_pt wjets_large "${input_files}"
##merge_nofilter2 vlow_pt wjets_large "${input_files}"
#merge high_pt w1jets W1JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt w2jets W2JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt w3jets W3JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt w4jets W4JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1

#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/${tag}/mc
#path=/nfs-7/userdata/rwkelley/babies/ss2012/${tag}
#output_path=$path/mc
#input_files="${input_path}/WJetsToLNu_HT-200To300_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1/*.root"
#input_files=$input_files,"${input_path}/WJetsToLNu_HT-250To300_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#input_files=$input_files,"${input_path}/WJetsToLNu_HT-300To400_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#input_files=$input_files,"${input_path}/WJetsToLNu_HT-400ToInf_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
#echo ${input_files}
#merge2 vlow_pt wjets_ht "${input_files}"
#merge high_pt wjets_ht200_250 WJetsToLNu_HT-200To250_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1
#merge high_pt wjets_ht250_300 WJetsToLNu_HT-250To300_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1 
#merge high_pt wjets_ht300_400 WJetsToLNu_HT-300To400_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1 
#merge high_pt wjets_ht400_Inf WJetsToLNu_HT-400ToInf_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1 

# opposite sign babies
#tag=V02-05-09f
#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc_os
#output_path=$path/mc_os
#merge_nofilter high_pt ttjets_os_powheg1 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1 
#merge_nofilter high_pt ttjets_os_powheg2 TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
#merge_nofilter high_pt ttjets_os         TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 


