#!/bin/bash

out_name=sswh_v7_hybrid
lumi=19.5
sr=1
nev=-1
options=""
#options="--do_sf"

./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options} --do_sf --hybrid --print_evt_list --categorize_rare --signal tchiwh-150-1,tchiwh-200-1 --print_evt_list >& logs/yields_${out_name}_incl_ss.log

options="--norm_hist"

./scripts/ewkino2012_plot_all.py --sr $sr --anal_type ss --out_name $out_name --lumi $lumi ${options} --do_sf --hybrid --print_evt_list --categorize_rare --signal tchiwh-150-1,tchiwh-200-1 --print_evt_list >& logs/yields_${out_name}_incl_ss.log
