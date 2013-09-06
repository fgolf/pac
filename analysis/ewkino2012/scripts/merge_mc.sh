#!/bin/bash


verbose=0
njets=2
tag=v10
analysis=ss
path=/nfs-7/userdata/${USER}/babies/ewkino2012/$analysis/$tag/


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
    cmd="ewkino2012_merge_babies --anal_type $at --verbose $verbose --input \"${input_path}/${path}/*.root\"  --output \"${output_path}/${name}.root\" --njets $njets"
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
    cmd="ewkino2012_merge_babies --anal_type $at --verbose $verbose --input \"${input_path}/${path}/*.root\"  --output \"${output_path}/${name}.root\" --njets $njets --filter 0"
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
    cmd="ewkino2012_merge_babies --anal_type $at --verbose $verbose --input \"${input}\"  --output \"${output_path}/${name}.root\" --njets $njets --filter 0"
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
    cmd="ewkino2012_merge_babies --anal_type $at --verbose $verbose --input \"$input\" --output \"${output_path}/${name}.root\" --njets $njets"
    echo $cmd
    echo $cmd > logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_${at}_baby_merge.log 2>&1 &
}

input_path=/hadoop/cms/store/user/${USER}/babies/ewkino2012/$analysis/${tag}/mc
output_path=$path
merge ss wz             WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss zz             ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss ww             WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss ttg            TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V19-v1
merge ss ttw            TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss ttww           TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss ttz            TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss tbz            TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
merge ss wwg            WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss www            WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wwz            WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wzz            WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss zzz            ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wmwmqq         WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wpwpqq         WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss ww_ds          WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge ss wgstar2e       WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wgstar2m       WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wgstar2t       WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge2 ss t_schan       "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 ss t_tchan       "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 ss t_tw          "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge ss ttjets         TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss ttjets_powheg  TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge ss ttslq          TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
merge ss ttdil          TTJets_FullLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v2
merge ss ttotr          TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 
merge ss dy             DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss dy1j           DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss dy2j           DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1
merge ss dy3j           DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss dy4j           DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge2 ss dyjets        "${input_path}/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1/*.root,${input_path}/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 ss wjets         "${input_path}/W1JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/W2JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/W3JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/W4JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge ss wh_zh_tth_hzz WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wh_zh_tth_hww WH_ZH_TTH_HToWW_M-125_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
merge ss wh_zh_tth_htt WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1 

