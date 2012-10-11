#!/bin/bash

# set cmssw area
pushd $HOME/Development/pac-svn/externals/source/CMSSW_5_3_2_patch4/src/
eval `scramv1 runtime -sh`
popd

# run the script
pushd $SS/edm
./pickEvents.pl DoubleElectron_Run2012A-13Jul2012-v1_AOD.txt  >&  DoubleElectron_Run2012A-13Jul2012-v1_AOD.log  &
./pickEvents.pl DoubleElectron_Run2012B-13Jul2012-v1_AOD.txt  >&  DoubleElectron_Run2012B-13Jul2012-v1_AOD.log  & 
./pickEvents.pl DoubleElectron_Run2012C-PromptReco-v2_AOD.txt >&  DoubleElectron_Run2012C-PromptReco-v2_AOD.log &
./pickEvents.pl DoubleMu_Run2012A-13Jul2012-v1_AOD.txt        >&  DoubleMu_Run2012A-13Jul2012-v1_AOD.log        &
./pickEvents.pl DoubleMu_Run2012B-13Jul2012-v4_AOD.txt        >&  DoubleMu_Run2012B-13Jul2012-v4_AOD.log        &
./pickEvents.pl DoubleMu_Run2012C-24Aug2012-v1_AOD.txt        >&  DoubleMu_Run2012C-24Aug2012-v1_AOD.log        &
./pickEvents.pl DoubleMu_Run2012C-PromptReco-v2_AOD.txt       >&  DoubleMu_Run2012C-PromptReco-v2_AOD.log       &
./pickEvents.pl MuEG_Run2012A-13Jul2012-v1_AOD.txt            >&  MuEG_Run2012A-13Jul2012-v1_AOD.log            &
./pickEvents.pl MuEG_Run2012A-recover-06Aug2012-v1_AOD.txt    >&  MuEG_Run2012A-recover-06Aug2012-v1_AOD.log    &
./pickEvents.pl MuEG_Run2012B-13Jul2012-v1_AOD.txt            >&  MuEG_Run2012B-13Jul2012-v1_AOD.log            &
./pickEvents.pl MuEG_Run2012C-24Aug2012-v1_AOD.txt            >&  MuEG_Run2012C-24Aug2012-v1_AOD.log            &
./pickEvents.pl MuEG_Run2012C-PromptReco-v2_AOD.txt           >&  MuEG_Run2012C-PromptReco-v2_AOD.log           &
popd
