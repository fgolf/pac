#!/bin/bash

out_name=sswh_v6
lumi=19.5
sr=-1
nev=-1
#options="--no_hist"
options=""

./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options} --mc_only --do_sf --print_evt_list --combine_bkgds --signal tchiwh-150-1,tchiwh-200-1 --print_evt_list >& logs/yields_${out_name}_incl_ss.log
