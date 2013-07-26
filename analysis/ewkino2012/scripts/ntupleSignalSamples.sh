#!/bin/bash

for f in `ls /nfs-7/userdata/fgolf/susy_higgs/sswh_v2/*chargino*.root` ; do
    outfile=${f/.root/_baby.root}
    $PAC/bin/release/ewkino2012_ss_analysis --sample tchiwh --output $outfile --input $f --anal_type ss --lumi 19.5 --fr data/fake_rates/ssFR_qcd_standard_v14May2013.root --fl data/flip_rates/ssFL_data_standard_02222013.root --sparms 1 &
done
