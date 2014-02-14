#!/bin/bash 

#version=11Apr2013
#version=7Jan2014absonlyiso # --abs_iso true --invert_iso_only true
#version=10Jan2014absonlyiso # --abs_iso true --invert_iso_only true, got rid of --jet_dphi 2.5, put back electrons
version=31Jan2014onlyisoFOpt #  --invert_iso_only true --FOpt true
#version=23Jan2014absonlyiso # --invert_iso_only true
#version=30Jan2014  # 
nev=-1

# create output dir
mkdir -p plots/fake_rates/${version}

# run data
run_list=json/final_19p49fb_cms2.txt
ss2012_create_fakerate --nev $nev --sample data --channel el --root_file_name electrons_data_${version}.root --run_list $run_list --invert_iso_only true --FOpt true
ss2012_create_fakerate --nev $nev --sample data --channel mu --root_file_name muons_data_${version}.root     --run_list $run_list --invert_iso_only true --FOpt true
hadd -f plots/fake_rates/${version}/ssFR_data_standard_${version}.root plots/fake_rates/muons_data_${version}/muons_data_${version}.root plots/fake_rates/electrons_data_${version}/electrons_data_${version}.root 
#hadd -f plots/fake_rates/${version}/ssFR_data_standard_${version}.root plots/fake_rates/muons_data_${version}/muons_data_${version}.root 

# run DY
run_list=\"\"
ss2012_create_fakerate --nev $nev --sample dy --channel el --root_file_name electrons_dy_${version}.root --run_list $run_list --invert_iso_only true --FOpt true
ss2012_create_fakerate --nev $nev --sample dy --channel mu --root_file_name muons_dy_${version}.root     --run_list $run_list --invert_iso_only true --FOpt true
hadd -f plots/fake_rates/${version}/ssFR_dy_standard_${version}.root plots/fake_rates/muons_dy_${version}/muons_dy_${version}.root plots/fake_rates/electrons_dy_${version}/electrons_dy_${version}.root 
#hadd -f plots/fake_rates/${version}/ssFR_dy_standard_${version}.root plots/fake_rates/muons_dy_${version}/muons_dy_${version}.root 

# run wjets
run_list=\"\"
ss2012_create_fakerate --nev $nev --sample wjets --channel el --root_file_name electrons_wjets_${version}.root --run_list $run_list --invert_iso_only true --FOpt true
ss2012_create_fakerate --nev $nev --sample wjets --channel mu --root_file_name muons_wjets_${version}.root     --run_list $run_list --invert_iso_only true --FOpt true
hadd -f plots/fake_rates/${version}/ssFR_wjets_standard_${version}.root plots/fake_rates/muons_wjets_${version}/muons_wjets_${version}.root plots/fake_rates/electrons_wjets_${version}/electrons_wjets_${version}.root 
#hadd -f plots/fake_rates/${version}/ssFR_wjets_standard_${version}.root plots/fake_rates/muons_wjets_${version}/muons_wjets_${version}.root 

# run qcd
run_list=\"\"
ss2012_create_fakerate --nev $nev --sample qcd --channel el --root_file_name electrons_qcd_${version}.root --run_list $run_list --invert_iso_only true --FOpt true
ss2012_create_fakerate --nev $nev --sample qcd --channel mu --root_file_name muons_qcd_${version}.root     --run_list $run_list --invert_iso_only true --FOpt true
hadd -f plots/fake_rates/${version}/ssFR_qcd_standard_${version}.root plots/fake_rates/muons_qcd_${version}/muons_qcd_${version}.root plots/fake_rates/electrons_qcd_${version}/electrons_qcd_${version}.root 
#hadd -f plots/fake_rates/${version}/ssFR_qcd_standard_${version}.root plots/fake_rates/muons_qcd_${version}/muons_qcd_${version}.root 

# combine the output
cmd="ss2012_make_fr_from_hists --in_data plots/fake_rates/${version}/ssFR_data_standard_${version}.root \
 --in_mc "plots/fake_rates/${version}/ssFR_wjets_standard_${version}.root,plots/fake_rates/${version}/ssFR_dy_standard_${version}.root" \
 --output data/fake_rates/ssFR_data_ewkcor_${version}.root \
 --ele_lumi 0.049 --mu_lumi 0.143 \
 --ele_noiso_lumi 0.000130 --mu_iso_lumi 0.0402"
echo $cmd
eval $cmd
