#!/bin/bash

# get the json files
# ------------------------------------------------------------------------------------------------ #

url=https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV
wget --no-check-certificate $url/Reprocessing/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_JSON_v2.txt
wget --no-check-certificate $url/Reprocessing/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_JSON.txt
wget --no-check-certificate $url/Reprocessing/Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12_JSON.txt
wget --no-check-certificate $url/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt

# rename the extensions to json (just my preference)
# ------------------------------------------------------------------------------------------------ #

mv Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_JSON_v2.txt Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_v2.json
mv Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_JSON.txt    Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12.json
mv Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12_JSON.txt    Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12.json
mv Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt         Cert_190456-208686_8TeV_PromptReco_Collisions12.json           

# perform merge
# 198934 is the first run of Run2012C-PromptReco-v2 from the command:
#	dbsql "find min(run),max(run) where dataset=/DoubleMu/Run2012C-PromptReco-v2/AOD"
# 300000 is chosen to be larger than the last run in Run2012D-PromptReco-v1 
# ------------------------------------------------------------------------------------------------ #

mergeJSON.py Cert_190456-208686_8TeV_PromptReco_Collisions12.json:198934-300000 \
 Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12.json \
 Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12.json \
 Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_v2.json > Merged_190456-208686_8TeV_PromptReco_Collisions12.json 

# calculate the luminsoity
# ------------------------------------------------------------------------------------------------ #

lumiCalc2.py overview -i Merged_190456-208686_8TeV_PromptReco_Collisions12.json >& Merged_190456-208686_8TeV_PromptReco_Collisions12.lumi &
