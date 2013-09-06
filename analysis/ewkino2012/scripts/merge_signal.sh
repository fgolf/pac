#!/bin/bash

verbose=0
tag=v10
ana_type=ss
path=/nfs-7/userdata/${USER}/babies/ewkino2012/${ana_type}/$tag

# make the output dirs
mkdir -p logs

# do the merging
function post_process
{
    mkdir -p $output_path
    mkdir -p logs/${tag} 
    local at=$1
    local sample=$2
    local input=$3
    local br=${4:-1.}
    cmd="ewkino2012_postprocess_signal_baby --sample $sample --input \"$input\" --output \"${output_path}/${sample}.root\" --br $br"
    echo $cmd > logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
    eval $cmd >> logs/${tag}/${sample}_${tag}_baby_merge.log 2>&1 &
}

input_path=/home/users/fgolf/pac/analysis/ewkino2012/crab/test_crab/
#input_path=/nfs-7/userdata/fgolf/babies/ewkino2012/ss/v9-20-10/signal/unmerged/test_crab
#input_path=/hadoop/cms/store/user/fgolf/babies/ewkino2012/ss/v10/mc/WinoNLSP_WinoNLSP/
output_path=$path/signal
input_files="${input_path}/SMS-TChiWH_WlnuHWW_2J_mChargino-130to225_mLSP-1to50_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-TChiWH_WlnuHWW_2J_mChargino-200to500_mLSP-170to370_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-TChiWH_WlnuHWW_2J_mChargino-250to500_mLSP-1to50_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1/res/*.root"
input_files="${input_files},${input_path}/SMS-TChiWH_WlnuHWW_2J_mChargino-200to500_mLSP-70to150_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1/res/*.root"
#input_files="${input_path}/*.root"
post_process ss tchiwh ${input_files} 0.07577
