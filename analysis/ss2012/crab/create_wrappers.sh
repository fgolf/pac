#!/bin/bash

default_args="--anal_type vlow_pt --fr ssFR_data_ewkcor_26Feb2013.root --fl ssFL_data_standard_02222013.root --sparms 1 --isFastSim 1 --njets 0"

# T1tttt
./BatchProcessViaCrab.sh \
 "SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1_cfg.py" \
 "/SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z/StoreResults-PU_START52_V9_FastSim-v1/USER" \
 "SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "--sample t1tttt $default_args"

# T4tW (or T6ttWW)
./BatchProcessViaCrab.sh \
 "SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM_cfg.py" \
 "/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER" \
 "SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM" \
 "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "--sample sbottomtop $default_args"

## T1tttt (fixed binning)
#./BatchProcessViaCrab.sh \
# "SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1_cfg.py" \
# "/SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z/StoreResults-PU_START52_V9_FastSim-v1/USER" \
# "t1tttt" \
# "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
# "ss2012_baby.root" \
# "--sample t1tttt $default_args"
#
## T6ttWW
#./BatchProcessViaCrab.sh \
# "SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM_cfg.py" \
# "/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER" \
# "sbottomtop" \
# "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
# "ss2012_baby.root" \
# "--sample sbottomtop $default_args"

