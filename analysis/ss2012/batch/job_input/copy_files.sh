#!/bin/bash

pac=$PAC
#pac=$HOME/Development/pac_ss2012_V03-01-05
cp -r $pac/analysis/ss2012/data/fake_rates/ssFR_data_ewkcor_17Apr2013.root .
cp -r $pac/analysis/ss2012/data/flip_rates/ssFL_data_standard_02222013.root .
cp -r $pac/bin/release/libMiniFWLite.so .
cp -r $pac/bin/release/ss2012_analysis .
cp -r $CMS2CORE/jetcorr .
tar -czf input.tgz *
