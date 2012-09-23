#/bin/bash

mkdir -p $PAC/analysis/ss2012/logs
nev=${1:--1}
ntuple_type=ss_skim
verbose=0
njets=2

# do the merging
function run
{
    local sample=$1
    local output_path=$2
    local run_list=${3:-\"\"}
    cmd="ss2012_analysis.exe --verbose $verbose --sample $sample --output \"${output_path}/${sample}.root\" --run_list $run_list  --ntuple_type $ntuple_type --nev $nev --njets $njets"
    echo $cmd
    echo $cmd > logs/run_${sample}.log 2>&1 &
    eval $cmd >> logs/run_${sample}.log 2>&1 &
}

# samples 
output=babies_jets2
run data     $output json/preapproval_cms2.txt
run zz       $output 
run wz       $output 
run ww       $output 
run ttjets   $output 
run ttg      $output 
run ttw      $output 
run ttww     $output 
run ttz      $output 
run wwg      $output 
run www      $output 
run wwz      $output 
run wzz      $output 
run zzz      $output 
run wgstar2e $output 
run wgstar2m $output 
run wgstar2t $output 
run wmwmqq   $output 
run wpwpqq   $output 
run ww_ds    $output 
run lm6      $output 
run lm9      $output 
