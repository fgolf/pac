#!/bin/bash

#out_name=AN_draft_19p5fb_v5
#out_name=V03-02-02
out_name=V03-02-02_3lep_veto
lumi=19.5
sr=-1
nev=-1
#options="--no_hist"
#options=""
options="--3lep_veto"

./scripts/ss2012_plot_all.py --sr $sr --anal_type high_pt --out_name $out_name --lumi $lumi        ${options} >& logs/yields_${out_name}_incl_hpt.log & 
./scripts/ss2012_plot_all.py --sr $sr --anal_type low_pt  --out_name $out_name --lumi $lumi        ${options} >& logs/yields_${out_name}_incl_lpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type vlow_pt --out_name $out_name --lumi $lumi        ${options} >& logs/yields_${out_name}_incl_vpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type high_pt --out_name $out_name --lumi $lumi --excl ${options} >& logs/yields_${out_name}_excl_hpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type low_pt  --out_name $out_name --lumi $lumi --excl ${options} >& logs/yields_${out_name}_excl_lpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type vlow_pt --out_name $out_name --lumi $lumi --excl ${options} >& logs/yields_${out_name}_excl_vpt.log &
