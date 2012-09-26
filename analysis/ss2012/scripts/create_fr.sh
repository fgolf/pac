#!/bin/bash 

ss2012_create_fakerate --nev -1 --dataset data --channel el --root_file_name electrons.root
ss2012_create_fakerate --nev -1 --dataset data --channel mu --root_file_name muons.root
hadd -f data/fake_rates/ssFR_data_standard_24Sep2012.root plots/fake_rates/muons/muons.root plots/fake_rates/electrons/electrons.root 
