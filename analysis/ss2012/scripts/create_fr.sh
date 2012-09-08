#!/bin/bash 

ss2012_create_fakerate --nev -1 --dataset data2012ABv1 --channel el --root_file_name electrons.root
ss2012_create_fakerate --nev -1 --dataset data2012ABv1 --channel mu --root_file_name muons.root
hadd -f data/fake_rates/ssFR_data_standard_23May2012v2.root plots/fake_rates/muons/muons.root plots/fake_rates/electrons/electrons.root 
