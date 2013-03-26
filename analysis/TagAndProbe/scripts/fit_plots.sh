#!/bin/bash

tp_fit_plots --mode electron --label egamma_test --input plots/Egamma_orig >& logs/egamma_fit.log  &
#tp_fit_plots --mode electron --label ss_mu_test  --input plots/SameSignMu_orig >&logs/egamma_fit.log &
