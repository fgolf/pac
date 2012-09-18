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
            // title,
            "2012 data", 
            // ntuple_path
            "DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root," 
            "DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root," 
            "DoubleMu_Run2012A-PromptReco-v1_AOD/*.root," 
            "DoubleMu_Run2012B-PromptReco-v1_AOD/*.root," 
            "MuEG_Run2012A-PromptReco-v1_AOD/*.root," 
            "MuEG_Run2012B-PromptReco-v1_AOD/*.root", 
            // SampleType 
            SampleType::data,
            // Sample
            Sample::data,
            // color
            kBlack
        },
        {
            // name
            "dy", 
            // title,
            "DY \\rightarrow \\ell \\ell", 
            // ntuple_path
            "DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12-PU_S7_START52_V9-v2/V05-02-27/*.root", 
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::dy,
            // color
            kBlue
        },
        {
            // name
            "ttw", 
            // title,
            "t\\overline{t}W", 
            // ntuple_path
            "TTWJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1/V05-02-28/*.root", 
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttw,
            // color
            kBlue
        },
        {
            // name
            "ttw_53X", 
            // title,
            "t\\overline{t}W", 
            // ntuple_path
            "TTWJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1/*.root", 
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttw_53X,
            // color
            kBlue
        },
        {
            // name
            "ttw_fastsim", 
            // title,
            "t\\overline{t}W", 
            // ntuple_path
            "8TeV_TTWJets_FastSim_525_Summer12-v1_InTimePU_START52_V9-v1/*.root",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttw_fastsim,
            // color
            kBlue
        },
        {
            // name
            "ttz", 
            // title,
            "t\\overline{t}Z", 
            // ntuple_path
            "TTZJets_8TeV-madgraph_v2_Summer12-PU_S7_START52_V9-v1/V05-02-28/*.root", 
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
            // title,
            "t\\overline{t}\\gamma", 
            // ntuple_path
            "TTGJets_8TeV-madgraph_Summer12-PU_S7_START52_V9-v1/V05-02-28/V05-02-28/*.root",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::ttg,
            // color
            kBlue
        },
        {
            // name
            "ttww", 
            // title,
            "t\\overline{t}WW", 
            // ntuple_path
            "8TeV_TTWWJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3/V05-02-28/*.root",
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
            // title,
            "t\\overline{t}+jets", 
            // ntuple_path
            "TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1/V05-02-27/*.root",
            // SampleType 
            SampleType::bkgd,
            // Sample
            Sample::ttjets,
            // color
            kBlue
        },
        {
            // name
            "zz", 
            // title,
            "ZZ", 
            // ntuple_path
            "ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v3/V05-02-27/*.root",
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
            // title,
            "WZ", 
            // ntuple_path
            "WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v2/V05-02-27/*.root",
            // SampleType 
            SampleType::rare,
            // Sample
            Sample::wz,
            // color
            kBlue
        },
        {
            // name
            "wwg", 
            // title,
            "WW\\gamma", 
            // ntuple_path
            "8TeV_WWGJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3/V05-02-28/*.root",
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
            // title,
            "WWW", 
            // ntuple_path
            "8TeV_WWWJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3/V05-02-28/*.root",
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
            // title,
            "WWZ", 
            // ntuple_path
            "8TeV_WWZNoGstarJets_FastSim_525_Summer12-v3_StoreResults-InTimePU_START52_V9-v3/V05-02-28/*.root",
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
            // title,
            "WZZ", 
            // ntuple_path
            "/*.root",
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
            // title,
            "ZZZ", 
            // ntuple_path
            "/*.root",
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
            // title,
            "T1tttt", 
            // ntuple_path
            "SMS-T1ttttProtoScan_Mgluino-350to1200_mLSP-0to400_8TeV-Pythia6Z_StoreResults-PU_START52_V5_FullSim-v1/*.root", 
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
            // title,
            "T1tttt", 
            // ntuple_path
            "SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z_StoreResults-PU_START52_V9_FastSim-v1/*.root",
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
            // title,
            "SbottomTop", 
            // ntuple_path
            "SbottomTopv6_macneill_8TeV/V05-02-28/*.root",
            // SampleType 
            SampleType::susy,
            // Sample
            Sample::sbottomtop,
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
            throw std::domain_error("ERROR: at::GetSampleInfo(std::string): sample not found!");
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
    TChain* GetSampleTChain(const Sample::value_type& sample, const NtupleType::value_type& ntuple)
    {
        using namespace std;
        string path = GetSampleInfo(sample).ntuple_path;
        std::string prefix = GetNtuplePath(ntuple);
		if (sample == Sample::data && ntuple == NtupleType::cms2)
		{
			path = rt::string_replace_all(path, "*.root", "merged/*.root");	
		}
        // special case since T1tttt isn't in the standard location
		if 
        (
            (sample == Sample::t1tttt && ntuple == NtupleType::cms2) ||
            (sample == Sample::t1tttt_fastsim && ntuple == NtupleType::cms2)
        )
		{
            prefix = "/hadoop/cms/store/user/cwelke/CMS2_V05-02-27/";
			path = rt::string_replace_all(path, "*.root", "merged/*.root");	
		}
        if (sample != Sample::data && ntuple != NtupleType::cms2 && ntuple != NtupleType::cms2mc)
        {
            path = rt::string_remove_all(path, "V05-02-27/");
            path = rt::string_remove_all(path, "V05-02-28/");
        }
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
    std::string GetNtuplePath(const NtupleType::value_type& ntuple)
    {
        switch (ntuple) 
        {
            case NtupleType::cms2:            return "/hadoop/cms/store/user/yanjuntu/CMSSW_5_2_3_patch4_V05-02-27/";
            case NtupleType::cms2mc:          return "/hadoop/cms/store/group/snt/papers2012/Summer12MC/";
            case NtupleType::cms2mc_53X:      return "/nfs-3/userdata/rwkelley/postprocessed/";
            case NtupleType::ss_skim_data:    return "/nfs-7/userdata/rwkelley/skims/ss2012/23Jun/nobtag/";
            case NtupleType::ss_skim_mc:      return "/nfs-7/userdata/rwkelley/skims/ss2012/22May/nobtag/";
            case NtupleType::ss_skim_mc_53X:  return "/nfs-7/userdata/rwkelley/skims/ss2012/53X/";
            case NtupleType::tensor:          return "/Users/rwk7t/Data/2012/";
            default:                          return "/hadoop/cms/store/group/snt/papers2012/Summer12MC/";
        };

        return "/hadoop/cms/store/group/snt/papers2012/Summer12MC/";
    }

	NtupleType::value_type GetNtupleTypeFromName(const std::string& ntuple_type_name)
	{
		if (ntuple_type_name == "cms2"          ) return NtupleType::cms2;
		if (ntuple_type_name == "cms2mc"        ) return NtupleType::cms2mc;
		if (ntuple_type_name == "cms2mc_53X"    ) return NtupleType::cms2mc_53X;
		if (ntuple_type_name == "ss_skim_data"  ) return NtupleType::ss_skim_data;
		if (ntuple_type_name == "ss_skim_mc"    ) return NtupleType::ss_skim_mc;
		if (ntuple_type_name == "ss_skim_mc_53X") return NtupleType::ss_skim_mc_53X;
		if (ntuple_type_name == "tensor"        ) return NtupleType::tensor;

        // throw string is not valid 
        throw std::domain_error("ERROR: at::GetNtupleTypeFromName(std::string): ntuple type name not found!");
	}

	std::string GetNtuplePath(const std::string& ntuple_type_name)
	{
		return GetNtuplePath(GetNtupleTypeFromName(ntuple_type_name));
	}


} // namespace at
