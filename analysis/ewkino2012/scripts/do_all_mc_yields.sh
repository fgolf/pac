#!/bin/bash

out_name=sswh_v9
lumi=19.5
sr=-1
nev=-1
options=""

./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options} --mc_only --print_evt_list --combine_bkgds --signal tchiwh-150-1 --print_evt_list --suffix all >& logs/yields_${out_name}_incl_ss.log &

options="--norm_hist"

./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options} --mc_only --print_evt_list --combine_bkgds --signal tchiwh-150-1 --print_evt_list --suffix all >& logs/yields_${out_name}_incl_ss.log &
