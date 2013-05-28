#!/bin/bash

rm -f input.tgz
rm -rf job_input/jetcorr
rm -f job_input/*
cp sweepRoot job_input/
cp -r $CMS2CORE/jetcorr job_input/
cp -r $PAC/analysis/ewkino2012/data/fake_rates/ssFR_qcd_standard_26Feb2013.root job_input/
cp -r $PAC/analysis/ewkino2012/data/fake_rates/ssFR_data_ewkcor_17Apr2013.root job_input/
cp -r $PAC/analysis/ewkino2012/data/flip_rates/ssFL_data_standard_02222013.root job_input/
cp -r $PAC/bin/cmssw/release/libMiniFWLite.so job_input/
cp -r $PAC/bin/cmssw/release/ewkino2012_ss_analysis job_input/
cp -r $PAC/bin/cmssw/release/add_cms2_branches job_input/
cd job_input
tar -pczf input.tgz *
cd -
cp job_input/input.tgz .


