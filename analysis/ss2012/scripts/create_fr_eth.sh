#!/bin/bash 

tag=eth_v2
run_list=json/hcp_10p45fb_cms2.txt
#run_list=json/merged_190456-206456_15p86fb_cms2.txt

#ss2012_create_fakerate_eth --nev -1 --sample data_el --channel el --root_file_name electrons_${tag}.root --run_list $run_list
ss2012_create_fakerate_eth --nev -1 --sample data_mu --channel mu --root_file_name muons_${tag}.root     --run_list $run_list
mkdir -p plots/fake_rates/${tag}
hadd -f plots/fake_rates/${tag}/fakerate_${tag}.root plots/fake_rates/muons_${tag}/muons_${tag}.root plots/fake_rates/electrons_${tag}/electrons_${tag}.root 
