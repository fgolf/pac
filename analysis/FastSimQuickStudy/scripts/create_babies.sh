#!/bin/bash

path=babies

lepton_eff_baby --sample dy         --input /Users/rwk7t/Data/cms2/dyjets_50323.root         --output ${path}/dy_fullsim.root
lepton_eff_baby --sample dy_fastsim --input /Users/rwk7t/Data/cms2/dyjets_fastsim_50331.root --output ${path}/dy_fastsim.root
