#include "fr/Sample.h"
#include <string>
#include <vector>
#include "TChain.h"
#include "rt/RootTools.h"
#include <stdexcept>

namespace fr
{
    // Array of SampleInfo's with the relevant metadata
    SampleInfo s_SampleInfos[] = 
    {
        {
            // name
            "data", 
            // title,
            "2012 data", 
            // baby_path
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyDM*.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyA.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyB.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyC.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyD.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/DoubleElectronSmallFRbaby.root",
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012C-PromptReco-v2_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012D-PromptReco-v1_AOD/*.root",
            // output file 
            "plots/data/data.root",
            // SampleType
            SampleType::data,
            // color
            kBlack
        },
        {
            // name
            "data_mu", 
            // title,
            "2012 data", 
            // baby_path
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyDM*.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyA.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyB.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyC.root,"
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/SingleMuonSmallFRbabyD.root",
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012C-PromptReco-v2_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012D-PromptReco-v1_AOD/*.root",
            // output file 
            "plots/data/data_mu.root",
            // SampleType
            SampleType::data,
            // color
            kBlack
        },
        {
            // name
            "data_el", 
            // title,
            "2012 data", 
            // baby_path
	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/miniFRbabies/DoubleElectronSmallFRbaby.root",
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root",
            // output file 
            "plots/data/data_el.root",
            // SampleType
            SampleType::data,
            // color
            kBlack
        },
        {
            // name
            "data_mu_D", 
            // title,
            "2012 data", 
            // baby_path
            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root,"
            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/SingleMu_Run2012D-PromptReco-v1_AOD/*.root",
            // output file 
            "plots/data/data_mu_D.root",
            // SampleType
            SampleType::data,
            // color
            kBlack
        },
        {
            // name
            "data_el_D", 
            // title,
            "2012 data", 
            // baby_path
            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root",
            // output file 
            "plots/data/data_el_D.root",
            // SampleType
            SampleType::data,
            // color
            kBlack
        },
        {
            // name
            "qcd", 
            // title,
            "QCD", 
            // baby_path
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root," 
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root,"
//            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root",
            "/nfs-7/userdata/gzevi/babies/fr/FakeRateSynch11Mar2014/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root" ,
            // output file
            "plots/qcd/qcd.root",
            // SampleType
            SampleType::bkgd,
            // color
            kRed
        },
        {
            // name
            "ttbar", 
            // title,
            "t\\bar{t}", 
            // baby_path
            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root", 
            // output file
            "plots/ttbar/ttbar.root",
            // SampleType
            SampleType::bkgd,
            // color
            kBlue
        },
        {
            // name
            "tthad", 
            // title,
            "t\\bar{t} hadronic", 
            // baby_path
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate19March2013/TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/*.root", 
            // output file
            "plots/tthad/tthad.root",
            // SampleType
            SampleType::bkgd,
            // color
            kBlue
        },
        {
            // name
            "wjets", 
            // title,
            "$W+jets$", 
            // baby_path
	    //            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root", 
            "/nfs-7/userdata/gzevi/babies/fr/FakeRateSynch11Mar2014/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root", 
            // output file
            "plots/wjets/wjets.root",
            // SampleType
            SampleType::bkgd,
            // color
            kBlue
        },
        {
            // name
            "dy", 
            // title,
            "$DY \\rightarrow \\ell\\ell$", 
            // baby_path
	    //            "/nfs-7/userdata/fgolf/babies/fr/FakeRate14May2013/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root", 
            "/nfs-7/userdata/gzevi/babies/fr/FakeRateSynch11Mar2014/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root", 
            // output file
            "plots/dy/dy.root",
            // SampleType
            SampleType::bkgd,
            // color
            kBlue
        },
        {
            // name
            "synch", 
            // title,
	    //            "Muon Synchronization", 
	    //            "Muon Data Synchronization", 
            "Ele Synchronization", 
            // baby_path
	    //            "/home/users/gzevi/FakeLepton/pac/analysis/FakeRateBabyMaker/SynchMuNtupleJEC*.root", 
	    //            "/home/users/gzevi/FakeLepton/pac/analysis/FakeRateBabyMaker/SynchTestDataNtuple.root", 
	    //"/home/users/gzevi/FakeLepton/pac/analysis/FakeRateBabyMaker/SynchEleNtupleMC.root", 
            "/home/users/gzevi/FakeLepton/pac/analysis/FakeRateBabyMaker/SynchEleNtupleData.root", 
	    //	    "/nfs-7/userdata/gzevi/babies/fr/FakeRateSynch11Mar2014/DoubleMu_Run2012D-PromptReco-v1_AOD/merged_frbaby*.root",
	    //	    "/home/users/gzevi/FakeLepton/pac/analysis/ss2012/macros/SyncMuonSmallFRbaby.root",
	    // output file
            "plots/synch/synch.root",
            // SampleType
            //SampleType::bkgd,
	    SampleType::data,
            // color
            kBlue
        },
    };

    // check that the SampleInfoArray is the same size as the enum
    // fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char static_assert[(expr) ? 1 : -1]
    STATIC_ASSERT(ARRAY_SIZE(s_SampleInfos) == fr::Sample::static_size);

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
            throw std::domain_error("ERROR: fr::GetSampleInfo(std::string): sample not found!");
        }

        return sample; 
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
    TChain* GetSampleTChain(const Sample::value_type& sample)
    {
        using namespace std;
        SampleInfo info = GetSampleInfo(sample);
        return rt::CreateTChainFromCommaSeperatedList(info.baby_path, "tree");
    }

} // namespace fr

