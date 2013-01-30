#!/bin/bash


# DATA TAG V05-03-18 (slimCMS2) 
# ---------------------------------------------------------#

##
## high pT
##

#GOODRUNLIST="\\\"\\\""
#SAMPLE=data
#ATYPE=0  #datatype field: 1 is fastsim
#DATE=v16_highpt
#NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-18
#
## Double Mu
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged         babies/ss2012/$DATE/DoubleMu_Run2012B-13Jul2012-v4_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/DoubleMu_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ss2012/$DATE/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged         babies/ss2012/$DATE/DoubleMu_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleMu_Run2012C-PromptReco-v2_AOD/merged        babies/ss2012/$DATE/DoubleMu_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleMu_Run2012D-PromptReco-v1_AOD/merged        babies/ss2012/$DATE/DoubleMu_Run2012D-PromptReco-v1_AOD
#
## Double Ele
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/DoubleElectron_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/DoubleElectron_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ss2012/$DATE/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged         babies/ss2012/$DATE/DoubleElectron_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged        babies/ss2012/$DATE/DoubleElectron_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged        babies/ss2012/$DATE/DoubleElectron_Run2012D-PromptReco-v1_AOD
#
## MuEG
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuEG_Run2012B-13Jul2012-v1_AOD/merged            babies/ss2012/$DATE/MuEG_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuEG_Run2012A-13Jul2012-v1_AOD/merged            babies/ss2012/$DATE/MuEG_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuEG_Run2012A-recover-06Aug2012-v1_AOD/merged    babies/ss2012/$DATE/MuEG_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuEG_Run2012C-24Aug2012-v1_AOD/merged            babies/ss2012/$DATE/MuEG_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuEG_Run2012C-PromptReco-v2_AOD/merged           babies/ss2012/$DATE/MuEG_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuEG_Run2012D-PromptReco-v1_AOD/merged           babies/ss2012/$DATE/MuEG_Run2012D-PromptReco-v1_AOD

##
## low pT
##

#GOODRUNLIST="\\\"\\\""
#SAMPLE=data
#ATYPE=0  
#DATE=v16_lowpt
#NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-18
#
## Double Mu
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012B-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/MuHad_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012A-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/MuHad_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ss2012/$DATE/MuHad_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012C-24Aug2012-v1_AOD/merged         babies/ss2012/$DATE/MuHad_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012C-PromptReco-v2_AOD/merged        babies/ss2012/$DATE/MuHad_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012D-PromptReco-v1_AOD/merged        babies/ss2012/$DATE/MuHad_Run2012D-PromptReco-v1_AOD
#
## Double Ele
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012B-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/ElectronHad_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012A-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/ElectronHad_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ss2012/$DATE/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012C-24Aug2012-v1_AOD/merged         babies/ss2012/$DATE/ElectronHad_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012C-PromptReco-v2_AOD/merged        babies/ss2012/$DATE/ElectronHad_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012D-PromptReco-v1_AOD/merged        babies/ss2012/$DATE/ElectronHad_Run2012D-PromptReco-v1_AOD

##
## very low pT
##

#GOODRUNLIST="\\\"\\\""
#SAMPLE=data
#ATYPE=0  
#DATE=v16_vlowpt
#NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-18
#
## Double Mu
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012B-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/MuHad_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012A-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/MuHad_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ss2012/$DATE/MuHad_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012C-24Aug2012-v1_AOD/merged         babies/ss2012/$DATE/MuHad_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012C-PromptReco-v2_AOD/merged        babies/ss2012/$DATE/MuHad_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/MuHad_Run2012D-PromptReco-v1_AOD/merged        babies/ss2012/$DATE/MuHad_Run2012D-PromptReco-v1_AOD
#
## Double Ele
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012B-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/ElectronHad_Run2012B-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012A-13Jul2012-v1_AOD/merged         babies/ss2012/$DATE/ElectronHad_Run2012A-13Jul2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ss2012/$DATE/ElectronHad_Run2012A-recover-06Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012C-24Aug2012-v1_AOD/merged         babies/ss2012/$DATE/ElectronHad_Run2012C-24Aug2012-v1_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012C-PromptReco-v2_AOD/merged        babies/ss2012/$DATE/ElectronHad_Run2012C-PromptReco-v2_AOD
#./writeConfig.sh $ATYPE 0 $SAMPLE $NTUPLE_PATH/ElectronHad_Run2012D-PromptReco-v1_AOD/merged        babies/ss2012/$DATE/ElectronHad_Run2012D-PromptReco-v1_AOD

# MC Tag V05-03-X
# ---------------------------------------------------------#

##
## full sim 
##

#GOODRUNLIST="\\\"\\\""
#VER=v16_highpt
#ATYPE=0
#NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC
#OUTPUT_PATH=babies/ss2012/53X/$VER
#
## fullsim
#SUSY=0
#FASTSIM=0
#
#TAG="V05-03-13_slim"
#CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
#./writeConfig.sh $ATYPE $SUSY ttjets   $NTUPLE_PATH/TT_CT10_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v2/$TAG             $OUTPUT_PATH/TT_CT10_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v2
#./writeConfig.sh $ATYPE $SUSY ttww     $NTUPLE_PATH/TTWWJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                           $OUTPUT_PATH/TTWWJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY ttz      $NTUPLE_PATH/TTZJets_8TeV-madgraph_v2_${CAMPAIGN}-v1/$TAG/                         $OUTPUT_PATH/TTZJets_8TeV-madgraph_v2_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY ttg      $NTUPLE_PATH/TTGJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                            $OUTPUT_PATH/TTGJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wz       $NTUPLE_PATH/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG          $OUTPUT_PATH/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY zz       $NTUPLE_PATH/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/       $OUTPUT_PATH/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY ww       $NTUPLE_PATH/WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/    $OUTPUT_PATH/WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wwg      $NTUPLE_PATH/WWGJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                            $OUTPUT_PATH/WWGJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY www      $NTUPLE_PATH/WWWJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                            $OUTPUT_PATH/WWWJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wzz      $NTUPLE_PATH/WZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                     $OUTPUT_PATH/WZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wwz      $NTUPLE_PATH/WWZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                     $OUTPUT_PATH/WWZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY zzz      $NTUPLE_PATH/ZZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                     $OUTPUT_PATH/ZZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wgstar2e $NTUPLE_PATH/WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/    $OUTPUT_PATH/WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wgstar2m $NTUPLE_PATH/WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wgstar2t $NTUPLE_PATH/WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/  $OUTPUT_PATH/WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY ww_ds    $NTUPLE_PATH/WW_DoubleScattering_8TeV-pythia8_${CAMPAIGN}-v1/$TAG/                 $OUTPUT_PATH/WW_DoubleScattering_8TeV-pythia8_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wmwmqq   $NTUPLE_PATH/WmWmqq_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                             $OUTPUT_PATH/WmWmqq_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wpwpqq   $NTUPLE_PATH/WpWpqq_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                             $OUTPUT_PATH/WpWpqq_8TeV-madgraph_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY wjets    $NTUPLE_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v1/$TAG/      $OUTPUT_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY t_tw     $NTUPLE_PATH/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/    $OUTPUT_PATH/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY t_tw     $NTUPLE_PATH/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY t_schan  $NTUPLE_PATH/T_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/        $OUTPUT_PATH/T_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY t_schan  $NTUPLE_PATH/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/     $OUTPUT_PATH/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY t_tchan  $NTUPLE_PATH/T_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/        $OUTPUT_PATH/T_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY t_tchan  $NTUPLE_PATH/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/     $OUTPUT_PATH/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY lm6      $NTUPLE_PATH/SUSY_LM6_sftsht_8TeV-pythia6_${CAMPAIGN}-v1/$TAG/                     $OUTPUT_PATH/SUSY_LM6_sftsht_8TeV-pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY lm9      $NTUPLE_PATH/SUSY_LM9_sftsht_8TeV-pythia6_${CAMPAIGN}-v1/$TAG/                     $OUTPUT_PATH/SUSY_LM9_sftsht_8TeV-pythia6_${CAMPAIGN}-v1

# QCD
#TAG=V05-03-18_slim
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/   $OUTPUT_PATH/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/  $OUTPUT_PATH/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3/$TAG/     $OUTPUT_PATH/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/                  $OUTPUT_PATH/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/                 $OUTPUT_PATH/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/                 $OUTPUT_PATH/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/                 $OUTPUT_PATH/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3/$TAG/                $OUTPUT_PATH/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3/$TAG/               $OUTPUT_PATH/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3
#./writeConfig.sh $ATYPE $SUSY qcd  $NTUPLE_PATH/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/               $OUTPUT_PATH/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2

#TAG="V05-03-18_slim"
#CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
#./writeConfig.sh $ATYPE $SUSY ttjets   $NTUPLE_PATH/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/${TAG} $OUTPUT_PATH/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
#./writeConfig.sh $ATYPE $SUSY dy       $NTUPLE_PATH/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v1/${TAG}       $OUTPUT_PATH/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v1
#
#TAG="V05-03-21_slim"
#CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
#./writeConfig.sh $ATYPE $SUSY ttw $NTUPLE_PATH/TTWJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/TTWJets_8TeV-madgraph_${CAMPAIGN}-v1

TAG="V05-03-20"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7C
./writeConfig.sh $ATYPE $SUSY tbz   $NTUPLE_PATH/TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/${TAG} $OUTPUT_PATH/TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1

TAG="V05-03-20_slim"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
./writeConfig.sh $ATYPE $SUSY ttdil $NTUPLE_PATH/TTJets_FullLeptMGDecays_8TeV-madgraph_${CAMPAIGN}-v2/$TAG/SingleOrDiLepton     $OUTPUT_PATH/TTJets_FullLeptMGDecays_8TeV-madgraph_${CAMPAIGN}-v2
./writeConfig.sh $ATYPE $SUSY ttslq $NTUPLE_PATH/TTJets_SemiLeptMGDecays_8TeV-madgraph_${CAMPAIGN}_ext-v1/$TAG/SingleOrDiLepton $OUTPUT_PATH/TTJets_SemiLeptMGDecays_8TeV-madgraph_${CAMPAIGN}_ext-v1
./writeConfig.sh $ATYPE $SUSY ttotr $NTUPLE_PATH/TTJets_HadronicMGDecays_8TeV-madgraph_${CAMPAIGN}_ext-v1/$TAG                  $OUTPUT_PATH/TTJets_HadronicMGDecays_8TeV-madgraph_${CAMPAIGN}_ext-v1


# MC Tag V05-02-X (signal)
# ---------------------------------------------------------#

#VER=v14_highpt
#GOODRUNLIST="\\\"\\\""
#ATYPE=1
#NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Summer12MC/
#OUTPUT_PATH=babies/ss2012/53X/$VER

# fastsim
#SUSY=1
#FASTSIM=1

#./writeConfig.sh $ATYPE $SUSY t1tttt     $NTUPLE_PATH/SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1/V05-02-28/ $OUTPUT_PATH/SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1
#./writeConfig.sh $ATYPE $SUSY glustop    $NTUPLE_PATH/GluinoStop_cgeorge_8Tev/V05-02-28/    $OUTPUT_PATH/GluinoStop_cgeorge_8Tev
#./writeConfig.sh $ATYPE $SUSY glusbottom $NTUPLE_PATH/GluinoSbottom_cgeorge_8Tev/V05-02-28/ $OUTPUT_PATH/GluinoSbottom_cgeorge_8Tev
#./writeConfig.sh $ATYPE $SUSY sbottomtop /hadoop/cms/store/user/kelley/CMS2_V05-03-18/SbottomTop_msb450-510_mch140-320_mlsp50_8TeV_FS_v1_fgolf-SbottomTop_msb450-510_mch140-320_mlsp50_8TeV_FS_v1-800d6ac945c15e195cbd98c0883f9d09 babies/ss2012/53X/$VER/SbottomTop_msb450-510_mch140-320_mlsp50_8TeV_FS_v1_fgolf-SbottomTop_msb450-510_mch140-320_mlsp50_8TeV_FS_v1
#./writeConfig.sh $ATYPE $SUSY sbottomtop $NTUPLE_PATH/SbottomTopv6_macneill_8TeV/V05-02-28/ $OUTPUT_PATH/SbottomTopv6_macneill_8TeV
