#include "Sample.h"
#include <string>
#include <vector>
#include "TChain.h"
#include "rt/MiscTools.h"
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
            "~/Data/babies/fr/FakeRate20May2012_5p098ifb/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root," 
            "~/Data/babies/fr/FakeRate20May2012_5p098ifb/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root," 
            "~/Data/babies/fr/FakeRate20May2012_5p098ifb/SingleMu_Run2012A-PromptReco-v1_AOD/*.root," 
            "~/Data/babies/fr/FakeRate20May2012_5p098ifb/SingleMu_Run2012B-PromptReco-v1_AOD/*.root", 
            // output file 
            "plots/data/data.root",
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
            "~/Data/babies/fr/FakeRate20May2012_5p098ifb/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1/*.root", 
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
            "~/Data/babies/fr/FakeRate20May2012_5p098ifb/TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1/*.root", 
            // output file
            "plots/ttbar/ttbar.root",
            // SampleType
            SampleType::bkgd,
            // color
            kBlue
        },
        {
            // name
            "qcd11", 
            // title,
            "QCD", 
            // baby_path
            //"~/Data/fr2/QCD_Pt-15to20_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root,"
            //"~/Data/fr2/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root,"
            "~/Data/fr2/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root,"
            //"~/Data/fr2/QCD_Pt-20to30_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root,"
            //"~/Data/fr2/QCD_Pt-30to50_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root,"
            //"~/Data/fr2/QCD_Pt-50to80_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root,"
            //"~/Data/fr2/QCD_Pt-80to120_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root",
			,
            // output file
            "plots/qcd11/qcd11.root",
            // SampleType
            SampleType::bkgd,
            // color
            kRed
        },
        {
            // name
            "ttbar11", 
            // title,
            "t\\bar{t}", 
            // baby_path
            "/Users/rwk7t/Data/fr2/TTJets_TuneZ2_7TeV-madgraph-tauola_Fall11-PU_S6_START42_V14B-v2_frbaby/merged_output_files/*.root", 
            // output file
            "plots/ttbar11/ttbar11.root",
            // SampleType
            SampleType::bkgd,
            // color
            kBlue
        }
    };

    // check that the SampleInfoArray is the same size as the enum
    // fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char static_assert[(expr) ? 1 : -1]
    STATIC_ASSERT(ARRAY_SIZE(s_SampleInfos) == Sample::static_size);

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

