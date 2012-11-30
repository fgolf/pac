#!/bin/bash 

tag=27Nov2012
#run_list=json/preapproval_v2_cms2.txt
run_list=json/merged_190456-206456_15p86fb_cms2.txt

ss2012_create_fakerate.exe --nev -1 --dataset data --channel el --root_file_name electrons_${tag}.root --run_list $run_list
ss2012_create_fakerate.exe --nev -1 --dataset data --channel mu --root_file_name muons_${tag}.root     --run_list $run_list
hadd -f data/fake_rates/ssFR_data_standard_${tag}.root plots/fake_rates/muons_${tag}/muons_${tag}.root plots/fake_rates/electrons_${tag}/electrons_${tag}.root 
