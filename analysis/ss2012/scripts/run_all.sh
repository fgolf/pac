#/bin/bash

mkdir -p $PAC/analysis/ss2012/logs
nev=${1:--1}

# data (3.95 /fb -- ICHEP)
#ss2012_analysis --nev $nev --sample data --ntuple_type ss_skim_data  --run_list json/Cert_190456-195947_8TeV_PromptReco_Collisions12_v2_cms2.txt > logs/data.log 2>&1 &

# background
# specifiying the sample
#ss2012_analysis --nev $nev --sample zz     --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/ZZJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root"          > logs/zz.log     2>&1 &
#ss2012_analysis --nev $nev --sample wz     --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"               > logs/wz.log     2>&1 &
#ss2012_analysis --nev $nev --sample ttjets --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root" > logs/ttjets.log 2>&1 &
#ss2012_analysis --nev $nev --sample ttg    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                                  > logs/ttg.log    2>&1 &
#ss2012_analysis --nev $nev --sample ttw    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                                  > logs/ttw.log    2>&1 &
#ss2012_analysis --nev $nev --sample ttz    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                               > logs/ttz.log    2>&1 &
#ss2012_analysis --nev $nev --sample www    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                                  > logs/www.log    2>&1 &
#ss2012_analysis --nev $nev --sample wwz    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                           > logs/wwz.log    2>&1 &
#ss2012_analysis --nev $nev --sample wzz    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                           > logs/wzz.log    2>&1 &
#ss2012_analysis --nev $nev --sample zzz    --input "/nfs-7/userdata/rwkelley/skims/ss2012/53X/ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root"                           > logs/zzz.log    2>&1 &

# specifiying the paths specifically since Sample.cc doesn't point to old MC (they point to v3) (used for ICHEP)
#ss2012_analysis --nev $nev --sample ttg  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_TTGJets_FastSim_525_Summer12-v2_InTimePU_START52_V9-v2/*.root"         > logs/ttg.log    2>&1 &
#ss2012_analysis --nev $nev --sample ttw  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_TTWJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"         > logs/ttw.log    2>&1 &
#ss2012_analysis --nev $nev --sample ttww --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_TTWWJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"        > logs/ttww.log   2>&1 &
#ss2012_analysis --nev $nev --sample ttz  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_TTZJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"         > logs/ttz.log    2>&1 &
#ss2012_analysis --nev $nev --sample wwg  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_WWGJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"         > logs/wwg.log    2>&1 &
#ss2012_analysis --nev $nev --sample www  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_WWWJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"         > logs/www.log    2>&1 &
#ss2012_analysis --nev $nev --sample wwz  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_WWZJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"         > logs/wwz.log    2>&1 & #(merge file corrupt)
#ss2012_analysis --nev $nev --sample wzz  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_WZZNoGstarJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"  > logs/wzz.log    2>&1 &
#ss2012_analysis --nev $nev --sample zzz  --input "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/8TeV_ZZZNoGstarJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root"  > logs/zzz.log    2>&1 &

# specifiying the paths specifically since Sample.cc doesn't point to old MC (they point to v3) (used for ICHEP)

# SUSY
#ss2012_analysis --nev -1 --sample t1tttt --output babies/t1tttt_skim.root --sparms 1 --ntuple_type ss_skim_mc > logs/t1tttt_skim.log 2>&1 &
ss2012_analysis --nev -1 --sample t1tttt_fastsim --output babies2/t1tttt_fastsim.root --sparms 1 --ntuple_type ss_skim_mc --njets 0 > logs/t1tttt_fastsim.log 2>&1 &
ss2012_analysis --nev -1 --sample sbottomtop     --output babies2/sbottomtop.root     --sparms 1 --ntuple_type cms2mc     --njets 0 > logs/sbottomtop.log     2>&1 &
#ss2012_analysis --nev -1 --sample t1tttt_fastsim --output babies/t1tttt_fastsim_cms2.root --sparms 1 --ntuple_type cms2 > logs/t1tttt_fastsim_cms2.log 2>&1 &
#ss2012_analysis --nev 100 --sample t1tttt_fastsim --output output/test.root --sparms 1 --ntuple_type cms2 > logs/test.log 2>&1 &


