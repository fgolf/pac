#!/bin/bash

rm ./*.so

cp -r $PAC/bin/release/libMiniFWLite.so .
cp -r $PAC/bin/release/create_fake_rate_baby .
cp -r $PAC/externals/source/cms2_core/CORE/jetcorr/data .
tar -czf input.tgz *
