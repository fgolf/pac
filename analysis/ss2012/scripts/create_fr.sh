#!/bin/bash 

tag="29Jan2013"
#tag="d0cut"
#tag="test"
run_list=json/final_19p47fb_cms2.txt
nev=-1

ss2012_create_fakerate.exe --nev $nev --sample data_el --channel el --root_file_name electrons_${tag}.root --run_list $run_list
ss2012_create_fakerate.exe --nev $nev --sample data_mu --channel mu --root_file_name muons_${tag}.root     --run_list $run_list
hadd -f data/fake_rates/ssFR_data_standard_${tag}.root plots/fake_rates/muons_${tag}/muons_${tag}.root plots/fake_rates/electrons_${tag}/electrons_${tag}.root 
