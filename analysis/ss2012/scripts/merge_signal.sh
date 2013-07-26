#!/bin/bash

verbose=0
njets=2
tag=V03-02-04
path=/nfs-7/userdata/rwkelley/babies/ss2012/$tag
gen_count_from_tree=1
maxsize=21474836480 # 20GB size limit

# make the output dirs
mkdir -p logs

# do the merging
function post_process
{
    mkdir -p $output_path
    mkdir -p logs/${tag} 
	local at=$1
    local sample=$2
    local path=$3
    cmd="ss2012_postprocess_signal_baby --sample $sample --input \"${input_path}/${path}/*.root\" --output \"${output_path}/${sample}.root\" --gen_count_from_tree $gen_count_from_tree --maxsize $maxsize"
    echo $cmd
    echo $cmd > logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
}

function post_process2
{
    mkdir -p $output_path
    mkdir -p logs/${tag} 
	local at=$1
    local sample=$2
    local input_files=$3
    cmd="ss2012_postprocess_signal_baby --sample $sample --input \"${input_files}\" --output \"${output_path}/${sample}.root\" --gen_count_from_tree $gen_count_from_tree --maxsize $maxsize"
    echo $cmd
    echo $cmd > logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
}

input_path=/hadoop/cms/store/user/rwkelley/babies/ss2012/$tag/mc
output_path=$path/signal
#post_process vlow_pt t1tttt     SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1 v1
#post_process vlow_pt t1tttt     SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1
#post_process vlow_pt sbottomtop SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM 

#input_path=/nfs-7/userdata/rwkelley/babies/cms2_V05-03-23_ss2012_V02-05-01
#post_process vlow_pt tchiwh /TChiwh/res

#input_path=/nfs-7/userdata/rwkelley/babies/ss2012/crab/22Apr2013
#output_path=$path/signal
#
#Post_process vlow_pt t1tttt SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1
#Post_process vlow_pt sbottomtop SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM
#Post_process vlow_pt t6ttww_x08 SMS-T6ttWW_mSbottom-200to700_mChargino-30to600_mLSP_25to475_x08_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL
#Post_process vlow_pt t6ttww_x05 SMS-T6ttWW_mSbottom-200to700_mChargino-50to600_mLSP_25to300_x05_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL
#Post_process vlow_pt t5lnu      SMS-T5lnuPlusPlus_mGo-400to1400_mLSP_300to1300_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL
#
# t1ttt scans
input_path=/nfs-7/userdata/rwkelley/babies/ss2012/crab/V03-02-04
input_files="${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-1025to1200_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-25to500_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v2/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-525to1000_25GeVX25GeV_Binning_Summer12-START52_V9_FSIM-v2/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-1_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-25to550_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v3/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v2/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v3/res/*.root"
input_files="${input_files},${input_path}/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-800to1400_mLSP-1_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v2/res/*.root"
post_process2 vlow_pt t1tttt_scans "${input_files}"
#
## T5tttt scans
#input_files="${input_path}/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1000_1075_Summer12-START52_V9_FSIM_UFL/res/*.root"
#input_files=",${input_files}/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1075_1175_Summer12-START52_V9_FSIM_UFL/res/*.root"
#input_files=",${input_files}/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1175_1200_Summer12-START52_V9_FSIM_UFL/res/*.root"
#input_files=",${input_files}/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_900_1000_Summer12-START52_V9_FSIM_UFL/res/*.root"
#input_files=",${input_files}/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL/res/*.root"
#post_process vlow_pt t5tttt "${input_files}"
#
## T7btw scans
#input_files="${input_path}/SMS-T7btw_2J_mGo-800to1400_mSbottom-400to1350_mChi-150_mLSP-50_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1/rest/*.root"
#input_files=",${input_files}/SMS-T7btw_2J_mGo-800to1400_mSbottom-500to1350_mChi-300_mLSP-50_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1/rest/*.root"
#post_process vlow_pt t7btw "${input_files}"
