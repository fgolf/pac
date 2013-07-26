#!/bin/bash

out_name=sswh_v9_data
lumi=19.5
sr=-1
nev=--1
#options="--no_hist"
options="--print_evt_list --verbose"

./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options} --suffix all >& logs/yields_${out_name}_incl_ss.log &
#./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options}
