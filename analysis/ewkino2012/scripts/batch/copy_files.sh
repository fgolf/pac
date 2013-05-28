#!/bin/bash

rm -f job_input/*
EWK=$PAC/analysis/ewkino2012
cp -r $EWK/data/fake_rates/ssFR_qcd_standard_26Feb2013.root job_input/
cp -r $EWK/data/fake_rates/ssFR_data_ewkcor_17Apr2013.root job_input/
cp -r $SS/data/flip_rates/ssFL_data_standard_02222013.root job_input/
cp -r $PAC/bin/release/libMiniFWLite.so job_input/
cp -r $PAC/bin/release/ewkino2012_ss_analysis job_input/
cp sweepRoot job_input/
cp driver.sh job_input/
cd job_input
tar -pczf input.tgz *
cd -
