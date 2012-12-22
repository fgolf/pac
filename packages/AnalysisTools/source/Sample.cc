#include "at/Sample.h"

#include <string>
#include <vector>
#include <iostream>
#include "TChain.h"
#include "TColor.h"

//#include "CORE/mcSelections.h"
#include "rt/MiscTools.h"

namespace at
{
    // Array of SampleInfo's with the relevant metadata
    SampleInfo s_SampleInfos[] = 
    {
        {
            // name
            "data", 
            // title
            "2012 data", 
            // latex
            "data",
            // ntuple_path
            "DoubleMu_Run2012B-13Jul2012-v4_AOD,"
            "DoubleMu_Run2012A-13Jul2012-v1_AOD,"
            "DoubleMu_Run2012A-recover-06Aug2012-v1_AOD,"
            "DoubleMu_Run2012C-24Aug2012-v1_AOD,"
            "DoubleMu_Run2012C-PromptReco-v2_AOD,"
            "DoubleElectron_Run2012B-13Jul2012-v1_AOD,"
            "DoubleElectron_Run2012A-13Jul2012-v1_AOD,"
            "DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD,"
            "DoubleElectron_Run2012C-24Aug2012-v1_AOD,"
            "DoubleElectron_Run2012C-PromptReco-v2_AOD,"
            "MuEG_Run2012B-13Jul2012-v1_AOD,"
            "MuEG_Run2012A-13Jul2012-v1_AOD,"
            "MuEG_Run2012A-recover-06Aug2012-v1_AOD,"
            "MuEG_Run2012C-24Aug2012-v1_AOD,"
            "MuEG_Run2012C-PromptReco-v2_AOD",
            // SampleType 
            SampleType::data,
            // Sample
            Sample::data,
            // color
            kBlack
        },
        {
            // name
            "data2e", 
            // title
            "2012 data DoubleElectron", 
            // latex
            "data DoubleEl",
            // ntuple_path
            "DoubleElectron_Run2012B-13Jul2012-v1_AOD,"
            "DoubleElectron_Run2012A-13Jul2012-v1_AOD,"
            "DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD,"
            "DoubleElectron_Run2012C-24Aug2012-v1_AOD,"
            "DoubleElectron_Run2012C-PromptReco-v2_AOD",
            // SampleType 
            SampleType::data,
            // Sample
            Sample::data2e,
            // color
            kBlack
        },
        {
            // name
            "data2m", 
            // title
            "2012 data DoubleMu", 
            // latex
            "data DoubleMu",
            // ntuple_path
            "DoubleMu_Run2012B-13Jul2012-v4_AOD,"
            "DoubleMu_Run2012A-13Jul2012-v1_AOD,"
            "DoubleMu_Run2012A-recover-06Aug2012-v1_AOD,"
            "DoubleMu_Run2012C-24Aug2012-v1_AOD,"
            "DoubleMu_Run2012C-PromptReco-v2_AOD",
            // SampleType 
            SampleType::data,
            // Sample
            Sample::datame,
            // color
            kBlack
        },
        {
            // name
            "datame", 
            // title
            "2012 data MuEG", 
            // latex
            "data MuEG",
            // ntuple_path
            "MuEG_Run2012B-13Jul2012-v1_AOD,"
            "MuEG_Run2012A-13Jul2012-v1_AOD,"
            "MuEG_Run2012A-recover-06Aug2012-v1_AOD,"
            "MuEG_Run2012C-24Aug2012-v1_AOD,"
            "MuEG_Run2012C-PromptReco-v2_AOD",
            // SampleType 
            SampleType::data,
            // Sample
            Sample::datame,
            // color
            kBlack
        },
        {
            // name
            "dy", 
            // title,
            "DY #rightarrow ll", 
            // latex
            "$DY \\rightarrow \\ell \\ell$", 
            // ntuple_path
            "DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1", 
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::dy,
            // color
            kBlue
        },
        {
            // name
            "wjets", 
            // title,
            "W+jets #rightarrow l#nu", 
            // latex
            "$W+jets \\rightarrow \\ell \\nu$", 
            // ntuple_path
            "WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1", 
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::wjets,
            // color
            kBlue
        },
        {
            // name
            "t_tw", 
            // title,
            "tW", 
            // latex
            "tW", 
            // ntuple_path
            "T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1,"
            "Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::t_tw,
            // color
            kBlue
        },
        {
            // name
            "t_schan", 
            // title,
            "t, s-channel", 
            // latex
            "t, s-channel", 
            // ntuple_path
            "T_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1,"
            "Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::t_schan,
            // color
            kBlue
        },
        {
            // name
            "t_tchan", 
            // title,
            "t, t-channel", 
            // latex
            "t, t-channel", 
            // ntuple_path
            "T_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1,"
            "Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::t_tchan,
            // color
            kBlue
        },
        {
            // name
            "ttw", 
            // title
            "t#bar{t}W", 
            // latex
            "$t\\overline{t}W$", 
            // ntuple_path
            "TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1", 
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttw,
            // color
            kBlue
        },
        {
            // name
            "ttz", 
            // title
            "t#bar{t}Z", 
            // latex
            "$t\\overline{t}Z$", 
            // ntuple_path
            "TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1", 
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttz,
            // color
            kBlue
        },
        {
            // name
            "ttg", 
            // title
            "t#bar{t}#gamma", 
            // latex
            "$t\\overline{t}\\gamma$", 
            // ntuple_path
            "TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttg,
            // color
            kBlue
        },
        {
            // name
            "tbz", 
            // title
            "tbZ (Z #rightarrow ll)", 
            // latex
            "$tbZ (Z \\rightarrow \\ell \\ell)$", 
            // ntuple_path
            "TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::tbz,
            // color
            kBlue
        },
        {
            // name
            "ttww", 
            // title
            "t#bar{t}WW", 
            // latex
            "$t\\overline{t}WW$", 
            // ntuple_path
            "TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttww,
            // color
            kBlue
        },
        {
            // name
            "ttjets", 
            // title
            "t#bar{t}+jets", 
            // latex
            "$t\\overline{t}+jets$", 
            // ntuple_path
            "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttjets,
            // color
            kBlue
        },
        {
            // name
            "ttdil", 
            // title
            "t#bar{t} #rightarrow llX", 
            // latex
            "$t\\overline{t} \\rightarrow \\ell \\ell X$", 
            // ntuple_path
            "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttdil,
            // color
            kBlue
        },
        {
            // name
            "ttotr", 
            // title
            "t#bar{t} other", 
            // latex
            "$t\\overline{t}\\ \\rm{other}$", 
            // ntuple_path
            "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttotr,
            // color
            kBlue
        },
        {
            // name
            "ttslb", 
            // title
            "t#bar{t} #rightarrow l(b #rightarrow l)X", 
            // latex
            "$t\\overline{t} \\rightarrow \\ell (b \\rightarrow \\ell) X$", 
            // ntuple_path
            "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttslb,
            // color
            kBlue
        },
        {
            // name
            "ttslo", 
            // title
            "t#bar{t} #rightarrow l(#slash{b} #rightarrow l)X", 
            // latex
            "$t\\overline{t} \\rightarrow \\ell (\\slashed b \\rightarrow \\ell) X$", 
            // ntuple_path
            "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttslo,
            // color
            kBlue
        },
        {
            // name
            "zz", 
            // title
            "ZZ", 
            // latex
            "ZZ", 
            // ntuple_path
            "ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::zz,
            // color
            kBlue
        },
        {
            // name
            "wz", 
            // title
            "WZ", 
            // latex 
            "WZ",
            // ntuple_path
            "WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wz,
            // color
            kBlue
        },
        {
            // name
            "ww", 
            // title
            "WW", 
            // latex
            "WW", 
            // ntuple_path
            "WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ww,
            // color
            kBlue
        },
        {
            // name
            "wwg", 
            // title
            "WW#gamma", 
            // latex 
            "$WW\\gamma$", 
            // ntuple_path
            "WWGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wwg,
            // color
            kBlue
        },
        {
            // name
            "www", 
            // title
            "WWW", 
            // latex
            "WWW", 
            // ntuple_path
            "WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::www,
            // color
            kBlue
        },
        {
            // name
            "wwz", 
            // title
            "WWZ", 
            // latex
            "WWZ", 
            // ntuple_path
            "WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wwz,
            // color
            kBlue
        },
        {
            // name
            "wzz", 
            // title
            "WZZ", 
            // latex
            "WZZ", 
            // ntuple_path
            "WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wzz,
            // color
            kBlue
        },
        {
            // name
            "zzz", 
            // title
            "ZZZ", 
            // latex
            "ZZZ", 
            // ntuple_path
            "ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::zzz,
            // color
            kBlue
        },
        {
            // name
            "t1tttt", 
            // title
            "T1tttt", 
            // latex
            "T1tttt", 
            // ntuple_path
            "SMS-T1ttttProtoScan_Mgluino-350to1200_mLSP-0to400_8TeV-Pythia6Z_StoreResults-PU_START52_V5_FullSim-v1", 
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::t1tttt,
            // color
            kBlue
        },
        {
            // name
            "t1tttt_fastsim", 
            // title
            "T1tttt", 
            // latex 
            "T1tttt", 
            // ntuple_path
            "SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::t1tttt_fastsim,
            // color
            kBlue
        },
        {
            // name
            "sbottomtop", 
            // title
            "#tilde{b}t", 
            // latex 
            "$\\tilde{b}t$", 
            // ntuple_path
            "SbottomTopv6_macneill_8TeV",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::sbottomtop,
            // color
            kBlue
        },
        {
            // name
            "glusbottom", 
            // title
            "#tilde{g}#tilde{b}", 
            // latex 
            "$t\\tidle{g}\\tilde{b}$", 
            // ntuple_path
            "GluinoSbottom_cgeorge_8Tev",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::glusbottom,
            // color
            kBlue
        },
        {
            // name
            "glustop", 
            // title
            "#tilde{g}#tilde{t}", 
            // latex 
            "$t\\tidle{g}\\tilde{t}$", 
            // ntuple_path
            "GluinoStop_cgeorge_8Tev",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::glustop,
            // color
            kBlue
        },
        {
            // name
            "wgstar2e", 
            // title
            "W#gamma^{*} #rightarrow l#nuee", 
            // latex 
            "$W\\gamma^{*} \\rightarrow \\ell \\nu ee$", 
            // ntuple_path
            "WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wgstar2e,
            // color
            kBlue
        },
        {
            // name
            "wgstar2m", 
            // title
            "W#gamma^{*} #rightarrow l#nu#mu#mu", 
            // latex 
            "$W\\gamma^{*} \\rightarrow \\ell \\nu \\mu\\mu$", 
            // ntuple_path
            "WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wgstar2m,
            // color
            kBlue
        },
        {
            // name
            "wgstar2t", 
            // title
            "W#gamma^{*} #rightarrow l#nu#tau#tau", 
            // latex 
            "$W\\gamma^{*} \\rightarrow \\ell \\nu \\tau\\tau$",
            // ntuple_path
            "WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wgstar2t,
            // color
            kBlue
        },
        {
            // name
            "wmwmqq", 
            // title
            "W^{-}W^{-}qq", 
            // latex
            "$W^-W^-qq$", 
            // ntuple_path
            "WmWmqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wmwmqq,
            // color
            kBlue
        },
        {
            // name
            "wpwpqq", 
            // titlej
            "W^{+}W^{+}qq", 
            // latex
            "$W^+W^+qq$", 
            // ntuple_path
            "WpWpqq_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wpwpqq,
            // color
            kBlue
        },
        {
            // name
            "ww_ds", 
            // title
            "WW(DPS)", 
            // latex
            "WW(DPS)", 
            // ntuple_path
            "WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ww_ds,
            // color
            kBlue
        },
        {
            // name
            "lm6", 
            // title
            "SUSY LM6", 
            // latex
            "SUSY LM6",
            // ntuple_path
            "SUSY_LM6_sftsht_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::lm6,
            // color
            kBlue
        },
        {
            // name
            "lm9", 
            // title
            "SUSY LM9", 
            // latex
            "SUSY LM9", 
            // ntuple_path
            "SUSY_LM9_sftsht_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::lm9,
            // color
            kBlue
        },
        {
            // name
            "dy4jets", 
            // title,
            "DY #rightarrow ll + 4j", 
            // latex
            "$DY \\rightarrow \\ell \\ell$ + 4j", 
            // ntuple_path
            "DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::dy4jets,
            // color
            kBlue
        },
        {
            // name
            "w3jets", 
            // title,
            "W #rightarrow l#nu + 3j", 
            // latex
            "$W \\rightarrow \\ell \\ny$ + 3j", 
            // ntuple_path
            "W3JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::w3jets,
            // color
            kBlue
        },
        {
            // name
            "w4jets", 
            // title,
            "W #rightarrow l#nu + 4j", 
            // latex
            "$W \\rightarrow \\ell \\ny$ + 4j", 
            // ntuple_path
            "W4JetsToLNu_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::w4jets,
            // color
            kBlue
        },
        {
            // name
            "wz2l", 
            // title,
            "WZ #rightarrow 2l", 
            // latex
            "$WZ \\rightarrow 2\\ell", 
            // ntuple_path
            "WZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::wz2l,
            // color
            kBlue
        },
        {
            // name
            "zz2l", 
            // title,
            "ZZ #rightarrow 2l", 
            // latex
            "$ZZ \\rightarrow 2\\ell", 
            // ntuple_path
            "ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::zz2l,
            // color
            kBlue
        },
        {
            // name
            "ttpowheg", 
            // title
            "t#bar{t}+jets", 
            // latex
            "$t\\overline{t}+jets$", 
            // ntuple_path
            "TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttpowheg,
            // color
            kBlue
        },
        {
            // name
            "qcd", 
            // title
            "QCD", 
            // latex
            "QCD", 
            // ntuple_path
            "QCD_Pt-*to*_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::qcd,
            // color
            kBlue
        },
        {
            // name
            "qcd_mu15", 
            // title
            "QCD (#mu15 enriched)", 
            // latex
            "QCD (\\mu15 enriched)", 
            // ntuple_path
            "QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::lm9,
            // color
            kBlue
        }
    };

    // check that the SampleInfoArray is the same size as the enum
    // fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
    STATIC_ASSERT(ARRAY_SIZE(s_SampleInfos) == at::Sample::static_size);

    // wrapper function to get the SampleInfo
    Sample::value_type GetSampleFromName(const std::string& sample_name)
    {
        using namespace std;
        Sample::value_type sample = Sample::static_size;
        for (size_t i = 0; i != Sample::static_size; i++)
        {
            if (string(s_SampleInfos[i].name) == sample_name)
            {
                sample = static_cast<Sample::value_type>(i);
                break;
            }
        }

        // throw if not found
        if (sample == Sample::static_size)
        {
            throw std::domain_error(Form("ERROR: at::GetSampleInfo(std::string): sample %s not found!", sample_name.c_str()));
        }

        return sample; 
    }

    // test if a string is a sample name 
    bool IsSample(const std::string& sample_name)
    {
        for (size_t i = 0; i != Sample::static_size; i++)
        {
            if (std::string(s_SampleInfos[i].name) == sample_name)
            {
                return true; 
            }
        }
        return false;
    }

    // wrapper function to get the SampleInfo
    SampleInfo GetSampleInfo(const Sample::value_type& sample)
    {
        return s_SampleInfos[sample]; 
    }

    SampleInfo GetSampleInfo(const std::string& sample_name)
    {
        Sample::value_type sample = GetSampleFromName(sample_name); 
        return GetSampleInfo(sample); 
    }

    // wrapper function to get the SampleInfo
    // NOTE: user in charge of deleting
    TChain* GetSampleTChain(const Sample::value_type& sample, const NtupleType::value_type& ntuple)
    {
        using namespace std;
        string path = GetSampleInfo(sample).ntuple_path;
        SampleType::value_type sample_type = GetSampleInfo(sample).type;
        std::string prefix = GetNtuplePath(ntuple, sample_type);

        // special case since T1tttt/SbottomTop are still 52X 
        if ( (sample == Sample::t1tttt)         || 
             (sample == Sample::t1tttt_fastsim) || 
             (sample == Sample::sbottomtop)     || 
             (sample == Sample::glusbottom)     || 
             (sample == Sample::glustop)
            )
        {
            if (ntuple == NtupleType::cms2)
            {
                prefix = "/hadoop/cms/store/group/snt/papers2012/Summer12MC/";
                path = rt::string_replace_all(path, ",", "/V05-02-28,");	
                path.append("/V05-02-28");
            }
            else if (ntuple == NtupleType::ss_skim)
            {
                prefix = "/nfs-7/userdata/rwkelley/skims/ss2012/52X/";
                path = rt::string_replace_all(path, ",", "/V05-02-28,");
                path.append("/V05-02-28");
            }
        }
		//else if (sample == Sample::qcd_mu15)
        //{
        //    if (ntuple == NtupleType::cms2)
        //    {
        //        prefix = "/hadoop/cms/store/group/snt/papers2012/Summer12MC/";
        //        path = rt::string_replace_all(path, ",", "/V05-02-27,");	
        //        path.append("/V05-02-27");
        //    }
        //}
		else if (sample == Sample::data && ntuple == NtupleType::cms2)
		{
			path = rt::string_replace_all(path, ",", "/merged,");	
            path.append("/merged");
        }
        else if (sample == Sample::qcd && ntuple == NtupleType::cms2)
        {
            path = rt::string_replace_all(path, ",", "/V05-03-18_slim,");
            path.append("/V05-03-18_slim");
        }
        else if (sample == Sample::dy && ntuple == NtupleType::cms2)
        {
            path = rt::string_replace_all(path, ",", "/V05-03-18_slim,");
            path.append("/V05-03-18_slim");
        }
        else if (sample != Sample::tbz && ntuple == NtupleType::cms2)
        {
            path = rt::string_replace_all(path, ",", "/V05-03-20");
            path.append("/V05-03-20");
        }
        else if (sample != Sample::data && ntuple == NtupleType::cms2)
        {
            path = rt::string_replace_all(path, ",", "/V05-03-13_slim,");
            path.append("/V05-03-13_slim");
        }

        // append *.root at the end
        path = rt::string_replace_all(path, ",", "/*.root,");
        path.append("/*.root");

        return rt::CreateTChainFromCommaSeperatedList(path, "Events", prefix);
    }

    // function to filter samples by process
    bool FilterByProcess(const Sample::value_type& sample)
    {
        switch (sample) 
        {
        case Sample::data:
            return true;
            //case dyee: 
            //    return isDYee();
            //case dymm:
            //    return isDYmm();
            //case dytt:
            //    return isDYtt();
            //case we: 
            //    return isWe();
            //case wm:
            //    return isWm();
            //case wt:
            //    return isWt();
        default:
            return true;
        };

        return true;
    }

    // check if the sampe is real data
    bool SampleIsData(const Sample::value_type& sample)
    {
        return (GetSampleInfo(sample).type == SampleType::data);
    }

    // get path to ntuple
    std::string GetNtuplePath(const NtupleType::value_type& ntuple, const SampleType::value_type sample_type)
    {
        if (sample_type == SampleType::data)
        {
            switch (ntuple) 
            {
            case NtupleType::cms2:         return "/hadoop/cms/store/user/yanjuntu/CMSSW_5_3_2_patch4_V05-03-13/";
            case NtupleType::ss_skim:      return "/nfs-7/userdata/rwkelley/skims/ss2012/53X/v1/";
            case NtupleType::trilepz_skim: return "/hadoop/cms/store/user/imacneill/TTZ_8TeV_LooseTrilepSkim/gsfglobaliso/";
            default: {/*do nothing*/}
            };
        }
        else
        {
            switch (ntuple) 
            {
            case NtupleType::cms2:         return "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/";
            case NtupleType::ss_skim:      return "/nfs-7/userdata/rwkelley/skims/ss2012/53X/v1/";
            case NtupleType::trilepz_skim: return "/hadoop/cms/store/user/imacneill/TTZ_8TeV_LooseTrilepSkim/gsfglobaliso/";
            default: {/*do nothing*/}
            };
        }
        
        return "";
    }

    SampleType::value_type GetSampleTypeFromName(const std::string& sample_type_name)
    {
        if (sample_type_name == "data") return SampleType::data;
        if (sample_type_name == "susy") return SampleType::susy;
        if (sample_type_name == "rare") return SampleType::rare;
        if (sample_type_name == "bkgd") return SampleType::bkgd;

        // throw string is not valid 
        throw std::domain_error("ERROR: at::GetSampleTypeFromName(std::string): ntuple type name not found!");
    }


    NtupleType::value_type GetNtupleTypeFromName(const std::string& ntuple_type_name)
    {
        if (ntuple_type_name == "cms2"   )      return NtupleType::cms2;
        if (ntuple_type_name == "ss_skim")      return NtupleType::ss_skim;
        if (ntuple_type_name == "trilepz_skim") return NtupleType::trilepz_skim;

        // throw string is not valid 
        throw std::domain_error("ERROR: at::GetNtupleTypeFromName(std::string): ntuple type name not found!");
    }

    std::string GetNtuplePath(const std::string& ntuple_type_name, const std::string& sample_type_name)
    {
        return GetNtuplePath(GetNtupleTypeFromName(ntuple_type_name), GetSampleTypeFromName(sample_type_name));
    }


} // namespace at
