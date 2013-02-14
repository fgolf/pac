#!/bin/bash 

# eth_v2 uses full dataset
# eth_v3 is same as v2 but remove hlt_mu8 and does not require offline muons to be matched to trigger objects
# eth_v4 is same as v3 but only uses runs <= 194076 (i.e. ICHEP dataset)
# eth_v5 is same as v2 but uses FR babies that (hopefully) don't have a bug
# eth_v6 is same as v5 but adds a Z/upsilon veto for muons
# eth_v7 same as v6 but found but that away jet pt was actually 40, switching to 50 but now have dR(jet,FO) > 1.0 instead of 0.4
# eth_v8 same as v6 but with correct away jet and veto requirements
# eth_v9 same as v8 but with our binning for the muon pt
# eth_v10 run with the new code, fix away jet JEC

tag=eth_v10
run_list=json/final_19p47fb_cms2.txt

/home/users/fgolf/pac/bin/debug/ss2012_create_fakerate --nev -1 --sample data_el --channel el --root_file_name electrons_${tag}.root --run_list $run_list --tight_d0 0 --eth_binning 1 --fr_type eth
/home/users/fgolf/pac/bin/debug/ss2012_create_fakerate --nev -1 --sample data_mu --channel mu --root_file_name muons_${tag}.root     --run_list $run_list --tight_d0 0 --eth_binning 1 --fr_type eth
mkdir -p plots/fake_rates/${tag}
hadd -f plots/fake_rates/${tag}/fakerate_${tag}.root plots/fake_rates/muons_${tag}/muons_${tag}.root plots/fake_rates/electrons_${tag}/electrons_${tag}.root 

# ss2012_create_fakerate_eth.exe  --nev -1 --sample qcd --channel el --root_file_name electrons_qcd_${tag}.root --tight_d0 0 --eth_binning 1 --fr_type eth
# ss2012_create_fakerate_eth.exe  --nev -1 --sample qcd --channel mu --root_file_name muons_qcd_${tag}.root     --tight_d0 0 --eth_binning 1 --fr_type eth
# hadd -f data/fake_rates/ssFR_qcd_standard_${tag}.root plots/fake_rates/muons_qcd_${tag}/muons_qcd_${tag}.root plots/fake_rates/electrons_qcd_${tag}/electrons_qcd_${tag}.root
