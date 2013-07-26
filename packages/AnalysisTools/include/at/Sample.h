#ifndef AT_SAMPLE_H
#define AT_SAMPLE_H

#include "TChain.h"
#include "TColor.h"
#include <string>

namespace at
{
    // list of available samples
    struct Sample
    {
        enum value_type
        {
            data,
            data2e,
            data2m,
            datame,
            dy,
            wjets,
            t_tw,
            t_schan,
            t_tchan,
            ttw,
            ttz,
            ttg,
            tbz,
            ttww,
            ttjets,
            ttdil,
            ttotr,
            ttslq,
            ttslb,
            ttslo,
            tttt,
            zz,
            wz,
            ww,
            wwg,
            www,
            wwz,
            wzz,
            zzz,
            t1tttt,
            t1tttt_scans,
            t6ttww_x05,
            t6ttww_x08,
            t5tttt,
            t5lnu,
            t5vv,
            t7btw,
            t6tthh,
            sbottomtop,
            glusbottom,
            glustop,
            wgstar2e,
            wgstar2m,
            wgstar2t,
            wgstar,
            wmwmqq,
            wpwpqq,
            wwqq,
            ww_ds,
            lm6,
            lm9,
            dy4jets,
            w3jets,
            w4jets,
            wz2l,
            zz2l,
            ttpowheg,
            qcd,
            qcd_mu15,
            tchiwh,
            wh_zh_tth_hzz,
            wh_zh_tth_hww,
            wh_zh_tth_htt,
            dy1j,
            dy2j,
            dy3j,
            dy4j,
            dyjets,
            static_size
        };
    };

    // list of available sample types
    struct SampleType
    {
        enum value_type
        {
            data,
            susy,
            rare,
            bkgd,
            static_size
        };
    };

    // Sample Infomation
    struct SampleInfo
    {
        std::string name;            // short name
        std::string title;           // ROOT TLatex title
        std::string latex;           // real latex title
        std::string ntuple_path;     // logical name for path
        std::string tag;             // cms2 tag
        SampleType::value_type type; // classification
        Sample::value_type process;  // redundant process enum
        Color_t color; 
    };

    // list of available ntuples
    struct NtupleType
    {
        enum value_type
        {
            cms2,
            trilepz_skim,
            static_size
        };
    };

    // Get the Sample from a string
    Sample::value_type GetSampleFromName(const std::string& sample_name);

    // test if a string is on of the samples
    bool IsSample(const std::string& sample_name);

    // wrapper function to get the SampleInfo
    SampleInfo GetSampleInfo(const Sample::value_type& sample);
    SampleInfo GetSampleInfo(const std::string& sample_name);

    // get the chain from the Sample
    // NOTE: user in charge of deleting the TChain*
    TChain* GetSampleTChain
    (
        const Sample::value_type& sample, 
        const NtupleType::value_type& ntuple = NtupleType::cms2
    ); 

    // function to filter samples by process
    bool FilterByProcess(const Sample::value_type& sample);

    // check if the sampe is real data
    bool SampleIsData(const Sample::value_type& sample);

    // samlpe type from name
    SampleType::value_type GetSampleTypeFromName(const std::string& sample_type_name);

    // get path to ntuple
    std::string GetNtuplePath(const std::string& ntuple_type_name, const std::string& sample_type_name);
    std::string GetNtuplePath(const NtupleType::value_type& ntuple, const SampleType::value_type sample_type);
    NtupleType::value_type GetNtupleTypeFromName(const std::string& ntuple_type_name);

    // function to test the cms2 ntuple paths
    void test_paths();

} // namespace at

#endif // AT_SAMPLE_H
