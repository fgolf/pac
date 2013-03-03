#!/bin/bash

verbose=0
njets=2
tag=V02-05-04
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
    echo $cmd > logs/${version}/${name}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_baby_merge.log 2>&1 &
}

function merge2
{
    mkdir -p $output_path
    mkdir -p logs/${version} 
	local at=$1
    local name=$2
    local path=$3
    cmd="ss2012_merge_babies --anal_type $at --verbose $verbose --input \"$input\" --output \"${output_path}/${name}.root\" --njets $njets"
    echo $cmd
    echo $cmd > logs/${version}/${name}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${version}/${name}_${tag}_baby_merge.log 2>&1 &
}

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/hpt
merge high_pt dy            DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wjets         WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wz            WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt zz            ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ww            WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttg           TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttjets        TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttw           TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttww          TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttz           TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt tbz           TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
merge high_pt wwg           WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt www           WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wwz           WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wzz           WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt zzz           ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wmwmqq        WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wpwpqq        WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ww_ds         WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wgstar2e      WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wgstar2m      WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wgstar2t      WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt t_schan       Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt t_tchan       Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt t_tw          Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt tbar_schan    T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt tbar_tchan    T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge high_pt tbar_tw       T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge2 high_pt t_schan      "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 high_pt t_tchan      "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 high_pt t_tw         "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge high_pt ttjets_powheg TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge high_pt ttslq         TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1   
merge high_pt ttdil         TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge high_pt ttotr         TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/lpt
merge low_pt dy            DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wjets         WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wz            WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt zz            ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ww            WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ttg           TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ttjets        TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ttw           TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ttww          TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ttz           TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt tbz           TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
merge low_pt wwg           WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt www           WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wwz           WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wzz           WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt zzz           ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wmwmqq        WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wpwpqq        WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt ww_ds         WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wgstar2e      WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wgstar2m      WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge low_pt wgstar2t      WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt t_schan       Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt t_tchan       Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt t_tw          Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt tbar_schan    T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt tbar_tchan    T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge low_pt tbar_tw       T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge2 low_pt t_schan      "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 low_pt t_tchan      "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 low_pt t_tw         "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge low_pt ttjets_powheg TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge low_pt ttslq         TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1   
merge low_pt ttdil         TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge low_pt ttotr         TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/vpt
merge high_pt dy            DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wjets         WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wz            WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt zz            ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ww            WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttg           TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttjets        TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttw           TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttww          TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ttz           TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt tbz           TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
merge high_pt wwg           WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt www           WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wwz           WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wzz           WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt zzz           ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wmwmqq        WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wpwpqq        WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt ww_ds         WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wgstar2e      WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wgstar2m      WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge high_pt wgstar2t      WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge vlow_pt t_schan       Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge vlow_pt t_tchan       Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge vlow_pt t_tw          Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge vlow_pt tbar_schan    T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge vlow_pt tbar_tchan    T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#merge vlow_pt tbar_tw       T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
merge2 vlow_pt t_schan      "${input_path}/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 vlow_pt t_tchan      "${input_path}/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge2 vlow_pt t_tw         "${input_path}/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,${input_path}/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"
merge vlow_pt ttjets_powheg TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge vlow_pt ttslq         TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1   
merge vlow_pt ttdil         TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2 
merge vlow_pt ttotr         TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1 


#input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/V01-03-02/eth
#output_path=babies/V01-03-02/ept_njets${njets}_${version}
#merge ttjets_powheg TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2 


#merge sbottomtop SbottomTop_msb450-510_mch140-320_mlsp50_8TeV_FS_v1_fgolf-SbottomTop_msb450-510_mch140-320_mlsp50_8TeV_FS_v1
