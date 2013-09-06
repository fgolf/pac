#!/bin/bash

BABYTAG=v10 # 02-01-2013

#~/~/~/~~/~/~/~~/~/~/~~/~/~/~~/~/
# DATA TAG V05-03-24 (slimCMS2) # 
#~/~/~/~~/~/~/~~/~/~/~~/~/~/~~/~/

## high pT
# ---------------------------------------------------------#

RUNLIST="\"\"\"\""
SAMPLE=data
ATYPE=ss
#OPTIONS="--jet_pt_cut#20"
OPTIONS="\"\"\"\""
#OPTIONS="--apply_jec_unc#START52_V9#--switchSigns#1" 
NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24

# Double Mu
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged         babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleMu_Run2012B-13Jul2012-v4_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged         babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleMu_Run2012A-13Jul2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged         babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleMu_Run2012C-24Aug2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleMu_Run2012C-PromptReco-v2_AOD/merged        babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleMu_Run2012C-PromptReco-v2_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleMu_Run2012D-PromptReco-v1_AOD/merged        babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleMu_Run2012D-PromptReco-v1_AOD

# Double Ele
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged         babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleElectron_Run2012B-13Jul2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged         babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleElectron_Run2012A-13Jul2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged         babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleElectron_Run2012C-24Aug2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged        babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleElectron_Run2012C-PromptReco-v2_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged        babies/ewkino2012/ss/$BABYTAG/$ATYPE/DoubleElectron_Run2012D-PromptReco-v1_AOD

# MuEG
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/MuEG_Run2012B-13Jul2012-v1_AOD/merged            babies/ewkino2012/ss/$BABYTAG/$ATYPE/MuEG_Run2012B-13Jul2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/MuEG_Run2012A-13Jul2012-v1_AOD/merged            babies/ewkino2012/ss/$BABYTAG/$ATYPE/MuEG_Run2012A-13Jul2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/MuEG_Run2012A-recover-06Aug2012-v1_AOD/merged    babies/ewkino2012/ss/$BABYTAG/$ATYPE/MuEG_Run2012A-recover-06Aug2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/MuEG_Run2012C-24Aug2012-v1_AOD/merged            babies/ewkino2012/ss/$BABYTAG/$ATYPE/MuEG_Run2012C-24Aug2012-v1_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/MuEG_Run2012C-PromptReco-v2_AOD/merged           babies/ewkino2012/ss/$BABYTAG/$ATYPE/MuEG_Run2012C-PromptReco-v2_AOD
./writeConfig.sh $SAMPLE $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/MuEG_Run2012D-PromptReco-v1_AOD/merged           babies/ewkino2012/ss/$BABYTAG/$ATYPE/MuEG_Run2012D-PromptReco-v1_AOD

mkdir -p $ATYPE
mv *.cmd $ATYPE/.

# ---------------------------------------------------------#

#~/~/~/~~/~/~/~~/~/~/~~/~/~/~~/~/
# MC TAG V05-03-23 (slimCMS2)   # 
#~/~/~/~~/~/~/~~/~/~/~~/~/~/~~/~/

# note: I'm only going to do vlow pT cuts since we don't need to get 
#       the MC exactly right since there is 50% uncertainty on the xsec
#       This will give very slightly different yields in the high and low
#       pT analysis since the jet cleaning will affect the choice of hypothesis.

# ---------------------------------------------------------#

# full sim -- SM

RUNLIST="\"\"\"\""
ATYPE=ss
NTUPLE_PATH=/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC
OUTPUT_PATH=babies/ewkino2012/ss/$BABYTAG/mc
#OPTIONS="\"\"\"\""

TAG="V05-03-23"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
./writeConfig.sh ttww     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTWWJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                                  $OUTPUT_PATH/TTWWJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh ttz      $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTZJets_8TeV-madgraph_v2_${CAMPAIGN}-v1/$TAG/                                $OUTPUT_PATH/TTZJets_8TeV-madgraph_v2_${CAMPAIGN}-v1
./writeConfig.sh wz       $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG                 $OUTPUT_PATH/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_${CAMPAIGN}-v1
./writeConfig.sh zz       $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/              $OUTPUT_PATH/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
./writeConfig.sh ww       $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/           $OUTPUT_PATH/WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
./writeConfig.sh wgstar2e $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/           $OUTPUT_PATH/WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
./writeConfig.sh ww_ds    $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WW_DoubleScattering_8TeV-pythia8_${CAMPAIGN}-v1/$TAG/                        $OUTPUT_PATH/WW_DoubleScattering_8TeV-pythia8_${CAMPAIGN}-v1
./writeConfig.sh wmwmqq   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WmWmqq_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                                    $OUTPUT_PATH/WmWmqq_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh wpwpqq   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WpWpqq_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                                    $OUTPUT_PATH/WpWpqq_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh t_tw     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/           $OUTPUT_PATH/T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
./writeConfig.sh t_tw     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/        $OUTPUT_PATH/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
./writeConfig.sh t_schan  $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/T_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/               $OUTPUT_PATH/T_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
./writeConfig.sh t_schan  $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/            $OUTPUT_PATH/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
./writeConfig.sh t_tchan  $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/T_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/               $OUTPUT_PATH/T_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
./writeConfig.sh t_tchan  $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1/$TAG/            $OUTPUT_PATH/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v1
./writeConfig.sh ttjets   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1/${TAG} $OUTPUT_PATH/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_${CAMPAIGN}-v1
./writeConfig.sh dy       $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v1/${TAG}       $OUTPUT_PATH/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v1
./writeConfig.sh ttw      $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTWJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                                   $OUTPUT_PATH/TTWJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh tbz      $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1/$TAG $OUTPUT_PATH/TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1
./writeConfig.sh dy4j     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/$TAG $OUTPUT_PATH/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1

TAG="V05-03-24"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
./writeConfig.sh wwg $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WWGJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/        $OUTPUT_PATH/WWGJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh www $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WWWJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/        $OUTPUT_PATH/WWWJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh wzz $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/WZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh wwz $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WWZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/WWZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh zzz $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/ZZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/ZZZNoGstarJets_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh ttotr $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTJets_HadronicMGDecays_8TeV-madgraph_${CAMPAIGN}_ext-v1/$TAG                  $OUTPUT_PATH/TTJets_HadronicMGDecays_8TeV-madgraph_${CAMPAIGN}_ext-v1

TAG="V05-03-25"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
./writeConfig.sh ttjets   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TT_CT10_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v2/$TAG                    $OUTPUT_PATH/TT_CT10_TuneZ2star_8TeV-powheg-tauola_${CAMPAIGN}-v2
./writeConfig.sh dy1j     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/$TAG $OUTPUT_PATH/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
./writeConfig.sh dy2j     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1/$TAG $OUTPUT_PATH/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1
./writeConfig.sh dy3j     $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/$TAG $OUTPUT_PATH/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1
./writeConfig.sh wjets   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/W1JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1/$TAG   $OUTPUT_PATH/W1JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh wjets   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/W2JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1/$TAG   $OUTPUT_PATH/W2JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh wjets   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/W3JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1/$TAG   $OUTPUT_PATH/W3JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1
./writeConfig.sh wjets   $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/W4JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1/$TAG   $OUTPUT_PATH/W4JetsToLNu_TuneZ2Star_8TeV-madgraph_${CAMPAIGN}-v1

CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7C
./writeConfig.sh ttdil $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola_${CAMPAIGN}-v2/$TAG/ $OUTPUT_PATH/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola_${CAMPAIGN}-v2
./writeConfig.sh ttslq $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_${CAMPAIGN}-v1

TAG="V05-03-27"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
./writeConfig.sh wgstar2m $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/          $OUTPUT_PATH/WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1
./writeConfig.sh wgstar2t $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1/$TAG/         $OUTPUT_PATH/WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_${CAMPAIGN}-v1

TAG="V05-03-28"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
./writeConfig.sh wh_zh_tth_hww $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WH_ZH_TTH_HToWW_M-125_8TeV-pythia6_${CAMPAIGN}-v1/$TAG/                      $OUTPUT_PATH/WH_ZH_TTH_HToWW_M-125_8TeV-pythia6_${CAMPAIGN}-v1
./writeConfig.sh wh_zh_tth_hzz $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6_${CAMPAIGN}-v1/$TAG/                      $OUTPUT_PATH/WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6_${CAMPAIGN}-v1
./writeConfig.sh wh_zh_tth_htt $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola_${CAMPAIGN}-v1/$TAG/  $OUTPUT_PATH/WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola_${CAMPAIGN}-v1
./writeConfig.sh wjets $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v2/$TAG/ $OUTPUT_PATH/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_${CAMPAIGN}-v2

TAG="V05-03-30"
CAMPAIGN=Summer12_DR53X-PU_S10_START53_V19
./writeConfig.sh ttg      $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/TTGJets_8TeV-madgraph_${CAMPAIGN}-v1/$TAG/                $OUTPUT_PATH/TTGJets_8TeV-madgraph_${CAMPAIGN}-v1

## QCD
#TAG=V05-03-18_slim
#CAMPAIGN=Summer12_DR53X-PU_S10_START53_V7A
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/   $OUTPUT_PATH/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/   $OUTPUT_PATH/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/  $OUTPUT_PATH/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/ $OUTPUT_PATH/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3/$TAG/     $OUTPUT_PATH/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1/$TAG/                  $OUTPUT_PATH/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v1
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/                 $OUTPUT_PATH/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/                 $OUTPUT_PATH/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/                 $OUTPUT_PATH/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3/$TAG/                $OUTPUT_PATH/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3/$TAG/               $OUTPUT_PATH/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v3
#./writeConfig.sh qcd $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2/$TAG/               $OUTPUT_PATH/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_${CAMPAIGN}-v2

TAG="V05-03-31"
OPTIONS="--sparms#1#--isFastSim#1"
NTUPLE_PATH=/hadoop/cms/store/user/fgolf/CMS2_V05-03-31/WinoNLSP_WinoNLSP/postprocessed/
OUTPUT_PATH=babies/ewkino2012/ss/$BABYTAG/mc

./writeConfig.sh tchiwh $ATYPE $RUNLIST $OPTIONS $NTUPLE_PATH $OUTPUT_PATH/WinoNLSP_WinoNLSP

mkdir -p mc
mv *.cmd mc/.
