#!/bin/bash

# arguments to BatchProcessViaCrab.sh
# USAGE: ./BatchProcessViaCrab.sh PSET TASK ARGS
#     DSET    - cmssw dataset name
#     TASK    - Unique name for this task (will be used to produce the crab_\${TASK}.cfg, wrapper_\${TASK}.sh, cms2_\${TASK}.sh)
#     DBSURL  - DBS URL for the dataset 
#     OUTFILE - Name of outfile (i.e. baby.root,myMassDB.root)
#     ARGS    - Argument values for wrapper script (comma separated - put \"\" as default for none)
#     USELUMI - Argument to determine where to use the total number of lumis or events
#     CMS2TAG - CMS2 tag 
#     VSPARM  - quoated escaped comma sperated list of the sparms. eg. \"sparm1\",\"sparm2\"
#     FASTSIM - fastsim flag is set (default is true since mostly use this for signal scans)
#     GT      - Global tag to use
# "

default_args="--anal_type vlow_pt --fr ssFR_data_ewkcor_17Apr2013.root --fl ssFL_data_standard_02222013.root --sparms 1 --isFastSim 1 --njets 0 --apply_jec_unc START52_V9"
#crab_dir="test_crab"
crab_dir="/nfs-7/userdata/rwkelley/babies/ss2012/crab/V03-01-01"

# # T1tttt
# # --------------------------------------------------------------------- #
# # https://cmsweb.cern.ch/das/request?view=list&limit=10&instance=cms_dbs_prod_global&input=%2FSMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z%2FStoreResults-PU_START52_V9_FastSim-v1%2FUSER
# ./BatchProcessViaCrab.sh \
#  "/SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z/StoreResults-PU_START52_V9_FastSim-v1/USER" \
#  "SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t1tttt $default_args" \
#  0 \
#  "V02-05-28" \
#  "\"mgluino\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"


# T1tttt (scans)
# --------------------------------------------------------------------- #

# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-1025to1200_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v1%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-1025to1200_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-1025to1200_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-25to500_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v2%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-25to500_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-25to500_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v2" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-25to500_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v2%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-525to1000_25GeVX25GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-525to1000_25GeVX25GeV_Binning_Summer12-START52_V9_FSIM-v2" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-1_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v1%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-1_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-1_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-25to550_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v1%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-25to550_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-25to550_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v1%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v1" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v3%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v3/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v3" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v2%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v2" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v3%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v3/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v3" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-800to1400_mLSP-1_50GeVX50GeV_Binning%2FSummer12-START52_V9_FSIM-v2%2FAODSIM&instance=cms_dbs_prod_global
./BatchProcessViaCrab.sh \
 "/SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-800to1400_mLSP-1_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM" \
 "SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-800to1400_mLSP-1_50GeVX50GeV_Binning_Summer12-START52_V9_FSIM-v2" \
 "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
 "ss2012_baby.root" \
 "${crab_dir}" \
 "--sample t1tttt_scans $default_args" \
 0 \
 "V02-05-28" \
 "\"mgluino\",\"mlsp\"" \
 1 \
 "START52_V9A::All"


# # T6ttWW (T4tW --> UFL's stupid name)
# # --------------------------------------------------------------------- #
# 
# # T6ttWW scan1 (T4tW)
# # https://cmsweb.cern.ch/das/request?view=list&limit=10&instance=cms_dbs_ph_analysis_01&input=%2FSMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph%2FSummer12-START52_V9_FSIM%2FUSER
# ./BatchProcessViaCrab.sh \
#  "/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER" \
#  "SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample sbottomtop $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"msbottom\",\"mchargino\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T6ttWW scan2 (x = 0.5)
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T6ttWW_mSbottom-200to700_mChargino-50to600_mLSP_25to300_x05_8TeV-Madgraph%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T6ttWW_mSbottom-200to700_mChargino-50to600_mLSP_25to300_x05_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T6ttWW_mSbottom-200to700_mChargino-50to600_mLSP_25to300_x05_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t6ttww_x05 $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"msbottom\",\"x\",\"mchargino\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T6ttWW scan3 (x = 0.8)
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T6ttWW_mSbottom-200to700_mChargino-30to600_mLSP_25to475_x08_8TeV-Madgraph%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T6ttWW_mSbottom-200to700_mChargino-30to600_mLSP_25to475_x08_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T6ttWW_mSbottom-200to700_mChargino-30to600_mLSP_25to475_x08_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t6ttww_x08 $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"msbottom\",\"x\",\"mchargino\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T5ttttt scans
# # --------------------------------------------------------------------- #
# 
# # T5tttt scan1
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t5tttt $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"mgluino\",\"mstop\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T5tttt scan2
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_900_1000%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_900_1000/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_900_1000_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t5tttt $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"mgluino\",\"mstop\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T5tttt scan3
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1000_1075%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1000_1075/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1000_1075_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t5tttt $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"mgluino\",\"mstop\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T5tttt scan4
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1000_1075%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1075_1175/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1075_1175_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t5tttt $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"mgluino\",\"mstop\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# 
# # T5tttt scan5
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1175_1200%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1175_1200/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1175_1200_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t5tttt $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"mgluino\",\"mstop\",\"mlsp\"" \
#  1 \
#  "START52_V9A::All"
# 
# #
# # T7btw
# # --------------------------------------------------------------------- #
# #
# # T7btw scan 1
# #https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T7btw_2J_mGo-800to1400_mSbottom-400to1350_mChi-150_mLSP-50_TuneZ2star_8TeV-madgraph-tauola%2FSummer12-START53_V7C_FSIM-v1%2FAODSIM&instance=cms_dbs_prod_global
# ./BatchProcessViaCrab.sh \
#  "/SMS-T7btw_2J_mGo-800to1400_mSbottom-400to1350_mChi-150_mLSP-50_TuneZ2star_8TeV-madgraph-tauola/Summer12-START53_V7C_FSIM-v1/AODSIM" \
#  "SMS-T7btw_2J_mGo-800to1400_mSbottom-400to1350_mChi-150_mLSP-50_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t7btw $default_args" \
#  0 \
#  "V02-05-28" \
#  "\"mgluino\",\"msbottom\",\"mchargino\"" \
#  1 \
#  "START52_V9A::All"
# 
# # T7btw scan 2
# #https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T7btw_2J_mGo-800to1400_mSbottom-500to1350_mChi-300_mLSP-50_TuneZ2star_8TeV-madgraph-tauola%2FSummer12-START53_V7C_FSIM-v1%2FAODSIM&instance=cms_dbs_prod_global
# ./BatchProcessViaCrab.sh \
#  "/SMS-T7btw_2J_mGo-800to1400_mSbottom-500to1350_mChi-300_mLSP-50_TuneZ2star_8TeV-madgraph-tauola/Summer12-START53_V7C_FSIM-v1/AODSIM" \
#  "SMS-T7btw_2J_mGo-800to1400_mSbottom-500to1350_mChi-300_mLSP-50_TuneZ2star_8TeV-madgraph-tauola_Summer12-START53_V7C_FSIM-v1" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t7btw $default_args" \
#  0 \
#  "V02-05-28" \
#  "\"mgluino\",\"msbottom\",\"mchargino\"" \
#  1 \
#  "START52_V9A::All"
# #
# #
# # T5lnu
# # --------------------------------------------------------------------- #
# #
# # https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-T5lnuPlusPlus_mGo-400to1400_mLSP_300to1300_8TeV-Madgraph%2FSummer12-START52_V9_FSIM_UFL%2FUSER&instance=cms_dbs_ph_analysis_01
# ./BatchProcessViaCrab.sh \
#  "/SMS-T5lnuPlusPlus_mGo-400to1400_mLSP_300to1300_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER" \
#  "SMS-T5lnuPlusPlus_mGo-400to1400_mLSP_300to1300_8TeV-Madgraph_Summer12-START52_V9_FSIM_UFL" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_01/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample t5lnu $default_args" \
#  1 \
#  "V02-05-28" \
#  "\"mgluino\",\"mlsp\",\"x\",\"mchargino\"" \
#  1 \
#  "START52_V9A::All"
# 
# # TChiwh
# # --------------------------------------------------------------------- #
# #
# # https://cmsweb.cern.ch/das/request?view=list&limit=10&instance=cms_dbs_ph_analysis_02&input=%2FTChiwh-test%2Ffgolf-TChiwh-test-6138c231f814ac3df24f1150dfcad736%2FUSER
# ./BatchProcessViaCrab.sh \
#  "/TChiwh-test/fgolf-TChiwh-test-6138c231f814ac3df24f1150dfcad736/USER" \
#  "TChiwh-test_fgolf-TChiwh-test-6138c231f814ac3df24f1150dfcad736" \
#  "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet" \
#  "ss2012_baby.root" \
#  "${crab_dir}" \
#  "--sample tchiwh $default_args" \
#  0 \
#  "V02-05-28" \
#  "\"mchargino\",\"mlsp\"" \
#  1 \
#  "START53_V7A::All"
# 
