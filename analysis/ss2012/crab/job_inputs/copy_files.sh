#!/bin/bash

#cp -r $SS/json/Cert_*_cms2.txt .
cp -r $SS/crab/AddCMS2Branches.C .
cp -r $SS/data/fake_rates/ssFR_data_ewkcor_13Feb2013.root .
cp -r $SS/data/flip_rates/ssFL_data_standard_02212013.root .
cp -r $PAC/bin/cmssw/release/libMiniFWLite.so .
cp -r $PAC/bin/cmssw/release/ss2012_analysis .
tar -czf input.tgz *
