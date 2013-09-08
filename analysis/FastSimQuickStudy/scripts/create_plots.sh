#!/bin/bash

 lepton_eff_plots --input babies/dy_fullsim.root --output plots/dy_fullsim/dy_fullsim_plots.root
 lepton_eff_plots --input babies/dy_fastsim.root --output plots/dy_fastsim/dy_fastsim_plots.root
 root -b -q -l "macros/OverlayPlots.C+(\"png\")"
 root -b -q -l "macros/OverlayPlots.C+(\"eps\")"
 scp -r plots/compare/png/* uaf-8:/home/users/rwkelley/public_html/drop/fastsim_eff_compare/png/.
