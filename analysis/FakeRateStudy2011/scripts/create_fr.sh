#!/bin/bash 

nev=-1
tag=_orig
#tag=_mc3pt150_v3
#nev=100000
#tag=_test
vtx_file=data/vtxreweight.root

# qcd
fake_rate_study_2011 --nev $nev --sample qcd11 --channel mu --root_file_name plots/qcd/qcd$tag.root --vtx_file $vtx_file > logs/qcd$tag.log 2>&1 &

#ttbar
fake_rate_study_2011 --nev $nev --sample ttbar11 --channel mu --root_file_name plots/ttbar/ttbar$tag.root --vtx_file $vtx_file > logs/ttbar$tag.log 2>&1 &
