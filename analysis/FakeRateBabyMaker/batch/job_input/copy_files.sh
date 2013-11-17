#!/bin/bash

rm ./*.so

cp -r $PAC/bin/release/libMiniFWLite.so .
cp -r $PAC/bin/release/create_fake_rate_baby .
cp -r $PAC/externals/source/cms2_core/CORE/jetcorr/data .

g++ ../sweepRoot.C -o sweepRoot `root-config --cflags --libs`

tar -czf input.tgz *
