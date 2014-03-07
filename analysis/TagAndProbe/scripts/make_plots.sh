#!/bin/bash

mkdir -p logs

mlow=60
mhigh=120

# Electrons
# analysis=eg_test
analysis=Egamma
#analysis=SameSignEl
label=test

output=plots/${analysis}_${label}/
# tp_make_plots  --mode Electron   --den ${analysis}DenID   --num ${analysis}Num --verbose 0 --nev -1 --output $output/id/data/plots.root   --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_data_id.log   &
# tp_make_plots  --mode ElectronMC --den ${analysis}DenID   --num ${analysis}Num --verbose 0 --nev -1 --output $output/id/mc/plots.root     --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_mc_id.log     &
# tp_make_plots  --mode Electron   --den ${analysis}DenIso  --num ${analysis}Num --verbose 0 --nev -1 --output $output/iso/data/plots.root  --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_data_iso.log  &
# tp_make_plots  --mode ElectronMC --den ${analysis}DenIso  --num ${analysis}Num --verbose 0 --nev -1 --output $output/iso/mc/plots.root    --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_mc_iso.log    &
echo tp_make_plots  --mode Electron   --den ${analysis}DenBoth --num ${analysis}Num --verbose 0 --nev -1 --output $output/both/data/plots.root --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_${label}/data_both.log &
# tp_make_plots  --mode ElectronMC --den ${analysis}DenBoth --num ${analysis}Num --verbose 0 --nev -1 --output $output/both/mc/plots.root   --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_mc_both.log   &

# muons
#analysis=SameSignMu
#output=plots/${analysis}_${label}/
#
#tp_make_plots  --mode Muon   --den ${analysis}DenID   --num ${analysis}Num --verbose 0 --nev -1 --output $output/id/data/plots.root   --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_data_id.log   &
#tp_make_plots  --mode MuonMC --den ${analysis}DenID   --num ${analysis}Num --verbose 0 --nev -1 --output $output/id/mc/plots.root     --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_mc_id.log     &
#tp_make_plots  --mode Muon   --den ${analysis}DenIso  --num ${analysis}Num --verbose 0 --nev -1 --output $output/iso/data/plots.root  --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_data_iso.log  &
#tp_make_plots  --mode MuonMC --den ${analysis}DenIso  --num ${analysis}Num --verbose 0 --nev -1 --output $output/iso/mc/plots.root    --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_mc_iso.log    &
#tp_make_plots  --mode Muon   --den ${analysis}DenBoth --num ${analysis}Num --verbose 0 --nev -1 --output $output/both/data/plots.root --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_data_both.log &
#tp_make_plots  --mode MuonMC --den ${analysis}DenBoth --num ${analysis}Num --verbose 0 --nev -1 --output $output/both/mc/plots.root   --fit_mlow $mlow --fit_mhigh $mhigh >& logs/${analysis}_mc_both.log   &
