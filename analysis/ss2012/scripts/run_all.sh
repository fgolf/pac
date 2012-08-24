#/bin/bash

# data
#ss2012_analysis --nev -1 --sample data --ntuple_type ss_skim_mc > logs/data.log 2>&1 &


# background
#ntuple_type=ss_skim_mc
#ss2012_analysis --nev -1 --sample ttw    --ntuple_type ss_skim_mc > logs/ttw.log    2>&1 &
#ss2012_analysis --nev -1 --sample ttz    --ntuple_type ss_skim_mc > logs/ttz.log    2>&1 &
#ss2012_analysis --nev -1 --sample zz     --ntuple_type ss_skim_mc > logs/zz.log     2>&1 &
#ss2012_analysis --nev -1 --sample wz     --ntuple_type ss_skim_mc > logs/wz.log     2>&1 &
#ss2012_analysis --nev -1 --sample ttjets --ntuple_type ss_skim_mc > logs/ttjets.log 2>&1 &

# SUSY
#ss2012_analysis --nev -1 --sample t1tttt --output babies/t1tttt_skim.root --sparms 1 --ntuple_type ss_skim_mc > logs/t1tttt_skim.log 2>&1 &
#ss2012_analysis --nev -1 --sample t1tttt_fastsim --output babies/t1tttt_fastsim.root --sparms 1 --ntuple_type ss_skim_mc > logs/t1tttt_fastsim.log 2>&1 &
#ss2012_analysis --nev -1 --sample t1tttt_fastsim --output babies/t1tttt_fastsim_cms2.root --sparms 1 --ntuple_type cms2 > logs/t1tttt_fastsim_cms2.log 2>&1 &
#ss2012_analysis --nev 100 --sample t1tttt_fastsim --output output/test.root --sparms 1 --ntuple_type cms2 > logs/test.log 2>&1 &


