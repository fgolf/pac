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
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012C-PromptReco-v2_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012D-PromptReco-v1_AOD/*.root",
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
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleMu_Run2012D-PromptReco-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012C-PromptReco-v2_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/SingleMu_Run2012D-PromptReco-v1_AOD/*.root",
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
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root,"
			"/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DoubleElectron_Run2012D-PromptReco-v1_AOD/*.root",
            // output file 
            "plots/data/data_el.root",
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
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root," 
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-15to20_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-20to30_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-30to50_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-80to120_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-120to170_MuEnrichedPt5_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-5to15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3/*.root,"
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root",
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
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2/*.root", 
            // output file
            "plots/ttbar/ttbar.root",
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
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root", 
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
            "/nfs-7/userdata/rwkelley/babies/fr/FakeRate21Jan2013v2/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root", 
            // output file
            "plots/dy/dy.root",
            // SampleType
            SampleType::bkgd,
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

