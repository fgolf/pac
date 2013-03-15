#!/bin/bash

mkdir -p logs
output=plots/Egamma_orig/
mlow=60
mhigh=120

# EGamma
tp_make_plots  --mode Electron   --den EgammaDenID   --num EgammaNum --verbose 0 --nev -1 --output $output/id/data/plots.root   --fit_mlow $mlow --fit_mhigh $mhigh >& logs/egamma_data_id.log &
tp_make_plots  --mode ElectronMC --den EgammaDenID   --num EgammaNum --verbose 0 --nev -1 --output $output/id/mc/plots.root     --fit_mlow $mlow --fit_mhigh $mhigh >& logs/egamma_mc_id.log   &
tp_make_plots  --mode Electron   --den EgammaDenIso  --num EgammaNum --verbose 0 --nev -1 --output $output/iso/data/plots.root  --fit_mlow $mlow --fit_mhigh $mhigh >& logs/egamma_data_iso.log &
tp_make_plots  --mode ElectronMC --den EgammaDenIso  --num EgammaNum --verbose 0 --nev -1 --output $output/iso/mc/plots.root    --fit_mlow $mlow --fit_mhigh $mhigh >& logs/egamma_mc_iso.log   &
tp_make_plots  --mode Electron   --den EgammaDenBoth --num EgammaNum --verbose 0 --nev -1 --output $output/both/data/plots.root --fit_mlow $mlow --fit_mhigh $mhigh >& logs/egamma_data_iso.log &
tp_make_plots  --mode ElectronMC --den EgammaDenBoth --num EgammaNum --verbose 0 --nev -1 --output $output/both/mc/plots.root   --fit_mlow $mlow --fit_mhigh $mhigh >& logs/egamma_mc_iso.log   &
