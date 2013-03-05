#!/bin/bash

#cp -r $SS/json/Cert_*_cms2.txt .
cp -r $SS/data/fake_rates/ssFR_data_ewkcor_26Feb2013.root .
cp -r $SS/data/flip_rates/ssFL_data_standard_02222013.root .
cp -r $PAC/bin/cmssw/release/libMiniFWLite.so .
cp -r $PAC/bin/cmssw/release/ss2012_analysis .
cp -r $PAC/bin/cmssw/release/add_cms2_branches .
tar -czf input.tgz *
cp input.tgz ../.
