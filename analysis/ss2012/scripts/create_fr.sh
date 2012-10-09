#!/bin/bash 

label=12p26fb
date=08Oct2012
run_list=json/preapproval_v3_cms2.txt

#ss2012_create_fakerate --nev -1 --dataset data --channel el --root_file_name electrons_${label}.root --run_list $run_list
#ss2012_create_fakerate --nev -1 --dataset data --channel mu --root_file_name muons_${label}.root     --run_list $run_list
hadd -f data/fake_rates/ssFR_data_standard_${date}.root plots/fake_rates/muons_${label}/muons_${label}.root plots/fake_rates/electrons_${label}/electrons_${label}.root 
