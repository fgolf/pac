#!/bin/bash

suffix=njets2_v5

pushd babies

rm hpt lpt vpt

ln -s hpt_${suffix} hpt
pushd hpt 
ln -sf data_highpt_19p47.root data.root
ln -sf ttslq.root ttslo.root
ln -sf ttslq.root ttslb.root
popd

ln -s lpt_${suffix} lpt
pushd lpt 
ln -sf data_lowpt_19p47.root data.root
ln -sf ttslq.root ttslo.root
ln -sf ttslq.root ttslb.root
popd

ln -s vpt_${suffix} vpt
pushd vpt 
ln -sf data_vlowpt_19p47.root data.root
ln -sf ttslq.root ttslo.root
ln -sf ttslq.root ttslb.root
popd

popd
