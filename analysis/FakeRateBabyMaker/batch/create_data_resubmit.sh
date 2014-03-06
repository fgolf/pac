#!/bin/bash

date

# double Mu
./resubmitConfig.sh condor_DoubleMu_Run2012B-13Jul2012-v4_AOD.cmd
./resubmitConfig.sh condor_DoubleMu_Run2012A-13Jul2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleMu_Run2012A-recover-06Aug2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleMu_Run2012C-PromptReco-v2_AOD.cmd
./resubmitConfig.sh condor_DoubleMu_Run2012C-24Aug2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleMu_Run2012D-PromptReco-v1_AOD.cmd

# Double El
./resubmitConfig.sh condor_DoubleElectron_Run2012B-13Jul2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleElectron_Run2012A-13Jul2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleElectron_Run2012C-PromptReco-v2_AOD.cmd
./resubmitConfig.sh condor_DoubleElectron_Run2012C-24Aug2012-v1_AOD.cmd
./resubmitConfig.sh condor_DoubleElectron_Run2012D-PromptReco-v1_AOD.cmd

# SingleMu
./resubmitConfig.sh condor_SingleMu_Run2012B-13Jul2012-v1_AOD.cmd
./resubmitConfig.sh condor_SingleMu_Run2012A-13Jul2012-v1_AOD.cmd
./resubmitConfig.sh condor_SingleMu_Run2012A-recover-06Aug2012-v1_AOD.cmd
./resubmitConfig.sh condor_SingleMu_Run2012C-PromptReco-v2_AOD.cmd
./resubmitConfig.sh condor_SingleMu_Run2012C-24Aug2012-v1_AOD.cmd
./resubmitConfig.sh condor_SingleMu_Run2012D-PromptReco-v1_AOD.cmd

# MuHad
#./resubmitConfig.sh condor_MuHad_Run2012B-13Jul2012-v1_AOD.cmd
#./resubmitConfig.sh condor_MuHad_Run2012A-13Jul2012-v1_AOD.cmd
#./resubmitConfig.sh condor_MuHad_Run2012A-recover-06Aug2012-v1_AOD.cmd
#./resubmitConfig.sh condor_MuHad_Run2012C-PromptReco-v2_AOD.cmd
#./resubmitConfig.sh condor_MuHad_Run2012C-24Aug2012-v1_AOD.cmd
#./resubmitConfig.sh condor_MuHad_Run2012D-PromptReco-v1_AOD.cmd

# ElectronHad
#./resubmitConfig.sh condor_ElectronHad_Run2012B-13Jul2012-v1_AOD.cmd
#./resubmitConfig.sh condor_ElectronHad_Run2012A-13Jul2012-v1_AOD.cmd
#./resubmitConfig.sh condor_ElectronHad_Run2012A-recover-06Aug2012-v1_AOD.cmd
#./resubmitConfig.sh condor_ElectronHad_Run2012C-PromptReco-v2_AOD.cmd
#./resubmitConfig.sh condor_ElectronHad_Run2012C-24Aug2012-v1_AOD.cmd
#./resubmitConfig.sh condor_ElectronHad_Run2012D-PromptReco-v1_AOD.cmd

date
