#!/bin/bash

cp -r $SS/data/fake_rates/ssFR_data_ewkcor_17Apr2013.root .
cp -r $SS/data/flip_rates/ssFL_data_standard_02222013.root .
cp -r $PAC/bin/release/libMiniFWLite.so .
cp -r $PAC/bin/release/ss2012_analysis .
cp -r $CMS2CORE/jetcorr .
tar -czf input.tgz *
