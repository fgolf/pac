#!/bin/bash

mkdir -p logs

# EGamma
tp_make_plots  --mode Electron   --den EgammaDenID --num EgammaNum --verbose 0 --nev -1 >& logs/egamma_data_id.log &
tp_make_plots  --mode ElectronMC --den EgammaDenID --num EgammaNum --verbose 0 --nev -1 >& logs/egamma_mc_id.log   &
tp_make_plots  --mode Electron   --den EgammaDenIso --num EgammaNum --verbose 0 --nev -1 >& logs/egamma_data_iso.log &
tp_make_plots  --mode ElectronMC --den EgammaDenIso --num EgammaNum --verbose 0 --nev -1 >& logs/egamma_mc_iso.log   &
#tp_make_plots  --mode Electron   --den EgammaDenBoth --num EgammaNum --verbose 0 --nev -1 >& logs/egamma_data_both.log &
#tp_make_plots  --mode ElectronMC --den EgammaDenBoth --num EgammaNum --verbose 0 --nev -1 >& logs/egamma_mc_both.log   &
