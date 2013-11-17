#!/bin/bash

NUMEVENTS=100
EORMU=-1
# GOODRUNLIST=final_19p49fb_cms2.txt
GOODRUNLIST="\\\"\\\""

# DATA V05-03-23 slim 
# ---------------------------------------------------------#

NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24
TAG=FakeRate16Nov2013

# Double Mu
./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged          babies/fr/$TAG/DoubleMu_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged  babies/fr/$TAG/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged          babies/fr/$TAG/DoubleMu_Run2012B-13Jul2012-v4_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged          babies/fr/$TAG/DoubleMu_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleMu_Run2012C-PromptReco-v2_AOD/merged         babies/fr/$TAG/DoubleMu_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleMu_Run2012D-PromptReco-v1_AOD/merged         babies/fr/$TAG/DoubleMu_Run2012D-PromptReco-v1_AOD
#
## Double Ele
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged          babies/fr/$TAG/DoubleElectron_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged  babies/fr/$TAG/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged          babies/fr/$TAG/DoubleElectron_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged          babies/fr/$TAG/DoubleElectron_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged         babies/fr/$TAG/DoubleElectron_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged         babies/fr/$TAG/DoubleElectron_Run2012D-PromptReco-v1_AOD

# SingleMu 
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/SingleMu_Run2012B-13Jul2012-v1_AOD/merged         babies/fr/$TAG/SingleMu_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/merged babies/fr/$TAG/SingleMu_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/SingleMu_Run2012A-13Jul2012-v1_AOD/merged         babies/fr/$TAG/SingleMu_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/SingleMu_Run2012C-24Aug2012-v1_AOD/merged         babies/fr/$TAG/SingleMu_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/SingleMu_Run2012C-PromptReco-v2_AOD/merged        babies/fr/$TAG/SingleMu_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/SingleMu_Run2012D-PromptReco-v1_AOD/merged        babies/fr/$TAG/SingleMu_Run2012D-PromptReco-v1_AOD

## MuHad
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/MuHad_Run2012A-13Jul2012-v1_AOD/merged         babies/fr/$TAG/MuHad_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/MuHad_Run2012A-recover-06Aug2012-v1_AOD/merged babies/fr/$TAG/MuHad_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/MuHad_Run2012B-13Jul2012-v1_AOD/merged         babies/fr/$TAG/MuHad_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/MuHad_Run2012C-24Aug2012-v1_AOD/merged/        babies/fr/$TAG/MuHad_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/MuHad_Run2012C-PromptReco-v2_AOD/merged        babies/fr/$TAG/MuHad_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/MuHad_Run2012D-PromptReco-v1_AOD/merged        babies/fr/$TAG/MuHad_Run2012D-PromptReco-v1_AOD
#
## ElectronHad
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/ElectronHad_Run2012A-13Jul2012-v1_AOD/merged         babies/fr/$TAG/ElectronHad_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD/merged babies/fr/$TAG/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/ElectronHad_Run2012B-13Jul2012-v1_AOD/merged         babies/fr/$TAG/ElectronHad_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/ElectronHad_Run2012C-24Aug2012-v1_AOD/merged/        babies/fr/$TAG/ElectronHad_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/ElectronHad_Run2012C-PromptReco-v2_AOD/merged        babies/fr/$TAG/ElectronHad_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/ElectronHad_Run2012D-PromptReco-v1_AOD/merged        babies/fr/$TAG/ElectronHad_Run2012D-PromptReco-v1_AOD

# MC (5-2-X)
# ---------------------------------------------------------#

#TAG=FakeRate19March2013
NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC
OUTPUT_PATH=babies/fr/${TAG}/

#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST /hadoop/cms/store/group/snt/papers2012/Summer12MC/TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1/V05-02-27/ babies/fr/$TAG/TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1

#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST /hadoop/cms/store/group/snt/papers2012/Summer12MC/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1/V05-02-27/ babies/fr/$TAG/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1

#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST /hadoop/cms/store/group/snt/papers2012/Summer12MC/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12-PU_S7_START52_V9-v1/V05-02-27/ babies/fr/$TAG/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12-PU_S7_START52_V9-v1

#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST /hadoop/cms/store/group/snt/papers2012/Summer12MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12-PU_S7_START52_V9-v2/V05-02-27/ babies/fr/$TAG/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12-PU_S7_START52_V9-v2

# MC (5-3-X)
# ---------------------------------------------------------#

#TAG=FakeRate19March2013
GOODRUNLIST="\\\"\\\""
NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC
OUTPUT_PATH=babies/fr/${TAG}/

#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24 babies/fr/$TAG/TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-20_slim/SingleOrDiLepton babies/fr/$TAG/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim babies/fr/$TAG/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-13_slim babies/fr/$TAG/TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2
./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim babies/fr/$TAG/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-18_slim babies/fr/$TAG/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-18_slim/                 babies/fr/$TAG/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-18_slim/                 babies/fr/$TAG/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/V05-03-18_slim/                babies/fr/$TAG/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/V05-03-18_slim/               babies/fr/$TAG/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-18_slim/               babies/fr/$TAG/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-18_slim/   babies/fr/$TAG/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim/   babies/fr/$TAG/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim/   babies/fr/$TAG/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim/   babies/fr/$TAG/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim/  babies/fr/$TAG/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18_slim/ babies/fr/$TAG/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/V05-03-18_slim/     babies/fr/$TAG/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/V05-03-18_slim/     babies/fr/$TAG/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28         babies/fr/$TAG/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28         babies/fr/$TAG/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28         babies/fr/$TAG/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28       babies/fr/$TAG/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28       babies/fr/$TAG/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28       babies/fr/$TAG/QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28       babies/fr/$TAG/QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28       babies/fr/$TAG/QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28       babies/fr/$TAG/QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28       babies/fr/$TAG/QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28       babies/fr/$TAG/QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28      babies/fr/$TAG/QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28      babies/fr/$TAG/QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28     babies/fr/$TAG/QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28     babies/fr/$TAG/QCD_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1
# ./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28           babies/fr/$TAG/QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1

##
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-13_slim/ $OUTPUT_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-28/      $OUTPUT_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/W1JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/ $OUTPUT_PATH/W1JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/W2JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/ $OUTPUT_PATH/W2JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/W3JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/ $OUTPUT_PATH/W3JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/W4JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/ $OUTPUT_PATH/W4JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
#
#./writeConfig.sh $EORMU $NUMEVENTS $GOODRUNLIST $NTUPLE_PATH/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/ $OUTPUT_PATH/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1
