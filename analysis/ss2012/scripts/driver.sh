#!/bin/bash

# inputs
# -------------------------- #
input=$1
output=$2
sample=$3
atype=$4
runlist=$5
options=$6

echo "[driver] input    = " ${input}
echo "[driver] output   = " ${output}
echo "[driver] sample   = " ${sample}
echo "[driver] atype    = " ${atype}
echo "[driver] runlist  = " ${runlist}
echo "[driver] options  = " ${options}
echo

if [[ $runlist = "" ]]; then
  echo [driver] runlist is empty
  runlist=\"\"
fi

# hard coded values
# -------------------------- #
fake_rate_file="ssFR_data_ewkcor_26Feb2013.root"
flip_rate_file="ssFL_data_standard_02212013.root"
njets=0

# set local dir to library path
# -------------------------- #
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

# set the command
# -------------------------- #
cmd="./ss2012_analysis --sample $sample --anal_type $atype $options \
 --input $input \
 --output $output.root \
 --run_list $runlist \
 --njets $njets \
 --fr $fake_rate_file \
 --fl $flip_rate_file"

# run it
# -------------------------- #
echo [driver] command to run:
echo $cmd
eval $cmd
