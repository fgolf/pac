#!/bin/bash

cp -r $CMS2CORE/jetcorr .
cp -r $PAC/analysis/ss2012/data/fake_rates/ssFR_data_ewkcor_17Apr2013.root .
cp -r $PAC/analysis/ss2012/data/flip_rates/ssFL_data_standard_02222013.root .
cp -r $PAC/bin/cmssw/release/libMiniFWLite.so .
cp -r $PAC/bin/cmssw/release/ss2012_analysis .
cp -r $PAC/bin/cmssw/release/add_cms2_branches .
tar -czf input.tgz *
cp input.tgz ../.
