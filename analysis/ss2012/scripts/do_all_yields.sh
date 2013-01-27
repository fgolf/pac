#!/bin/bash

out_name=AN_draft_19p47fb_v4 
lumi=19.47
sr=-1
nev=-1

./scripts/ss2012_plot_all.py --sr $sr --anal_type high_pt --out_name $out_name --lumi $lumi        >& logs/yields_incl_hpt.log & 
./scripts/ss2012_plot_all.py --sr $sr --anal_type low_pt  --out_name $out_name --lumi $lumi        >& logs/yields_incl_lpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type vlow_pt --out_name $out_name --lumi $lumi        >& logs/yields_incl_vpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type high_pt --out_name $out_name --lumi $lumi --excl >& logs/yields_excl_hpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type low_pt  --out_name $out_name --lumi $lumi --excl >& logs/yields_excl_lpt.log &
./scripts/ss2012_plot_all.py --sr $sr --anal_type vlow_pt --out_name $out_name --lumi $lumi --excl >& logs/yields_excl_vpt.log &
