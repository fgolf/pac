#!/bin/bash 

fake_rate_baby_looper --nev -1 --dataset data --channel el --root_file_name electrons.root
fake_rate_baby_looper --nev -1 --dataset data --channel mu --root_file_name muons.root
hadd -f plots/fake_rates/data/ssFR_data_standard_23May2012.root plots/muons/data/muons.root plots/electrons/data/electrons.root 
