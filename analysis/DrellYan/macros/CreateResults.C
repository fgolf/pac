#include "rt/RootTools.h"
#include "CTable.h"
#include "TChain.h"
#include "TCut.h"
#include <iostream> 
#include "at/Sample.h"


TChain* GetTChain(const at::Sample::value_type sample)
{
    TChain* chain_ptr = new TChain("tree");
    chain_ptr->Add(Form("babies/%s.root", at::GetSampleInfo(sample).name.c_str()));
    return chain_ptr;
}

// Print the generator acceptance
// akin to table 10 from AN-12-067
// http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2012_067_v6.pdf
void PrintAcceptance()
{
    TChain& ch_dy = *GetTChain(at::Sample::dy);

    // aliases
    ch_dy.SetAlias("z_mass"  , "gen_z_p4.mass()"); 

    // acceptance selections
    TCut is_ee       = "is_z_ee";
    TCut is_mm       = "is_z_mm";
    TCut is_tt       = "is_z_tt";
    TCut mass_window = "!is_gen_z || (60 < z_mass && z_mass < 120)";
    TCut is_reco_ee  = "is_ee";
    TCut is_reco_mm  = "is_mm";

    // total acceptance
    TCut gen_acc_den            = (is_ee || is_mm) && mass_window;
    TCut gen_acc_num            = gen_acc_den && "is_acc";
    TCut reco_acc_num           = gen_acc_num && (is_reco_ee || is_reco_mm); 
    const double gen_den_count  = ch_dy.GetEntries(gen_acc_den);
    const double gen_num_count  = ch_dy.GetEntries(gen_acc_num);
    const double reco_num_count = ch_dy.GetEntries(reco_acc_num);
    const double gen_acc        = gen_num_count/gen_den_count;
    const double reco_acc       = reco_num_count/gen_den_count;

    // mumu
    TCut gen_acc_den_mm            = is_mm && mass_window;
    TCut gen_acc_num_mm            = gen_acc_den_mm && "is_acc_mm";
    TCut reco_acc_num_mm           = gen_acc_num_mm && is_reco_mm; 
    const double gen_den_count_mm  = ch_dy.GetEntries(gen_acc_den_mm);
    const double gen_num_count_mm  = ch_dy.GetEntries(gen_acc_num_mm);
    const double reco_num_count_mm = ch_dy.GetEntries(reco_acc_num_mm);
    const double gen_acc_mm        = gen_num_count_mm/gen_den_count_mm;
    const double reco_acc_mm       = reco_num_count_mm/gen_den_count_mm;

    // ee
    TCut gen_acc_den_ee            = is_ee && mass_window;
    TCut gen_acc_num_ee            = gen_acc_den_ee && "is_acc_ee";
    TCut reco_acc_num_ee           = gen_acc_num_ee && is_reco_ee; 
    const double gen_den_count_ee  = ch_dy.GetEntries(gen_acc_den_ee);
    const double gen_num_count_ee  = ch_dy.GetEntries(gen_acc_num_ee);
    const double reco_num_count_ee = ch_dy.GetEntries(reco_acc_num_ee);
    const double gen_acc_ee        = gen_num_count_ee/gen_den_count_ee;
    const double reco_acc_ee       = reco_num_count_ee/gen_den_count_ee;

    // check: ee+mm
    const double gen_den_check  = gen_den_count_ee + gen_den_count_mm;
    const double gen_num_check  = gen_num_count_ee + gen_num_count_mm;
    const double reco_num_check = reco_num_count_ee + reco_num_count_mm;
    const double gen_acc_check  = gen_num_check/gen_den_check;
    const double reco_acc_check = reco_num_check/gen_den_check;

    CTable t1;
    t1.useTitle();
    t1.setTitle("Drell-Yan generator acceptance");
    t1.setTable() (                            "ee",             "mm",         "ll",    "check = ee+mm")
                  ( "den"      , gen_den_count_ee  , gen_den_count_mm  , gen_den_count , gen_den_check )
                  ( "gen num"  , gen_num_count_ee  , gen_num_count_mm  , gen_num_count , gen_num_check )
                  ( "gen acc"  , gen_acc_ee        , gen_acc_mm        , gen_acc       , gen_acc_check )
                  ( "reco num" , reco_num_count_ee , reco_num_count_mm , reco_num_count, reco_acc_check)
                  ( "reco acc" , reco_acc_ee       , reco_acc_mm       , reco_acc      , reco_acc_check)
                  ;
    std::cout << t1 << std::endl;

    // done
    return;
}

// samples for the yield:
at::Sample::value_type s_Samples[] =
{
    at::Sample::data,
    at::Sample::dy,
    at::Sample::wjets,
    at::Sample::ttjets
};
const size_t s_SamplesCount = 4;//sizeof(s_Samples)/sizeof(s_SamplesCount);

struct Channel
{
    enum enum_type 
    {
        ee,
        mm,
        ll,
        static_size
    };
};

struct Yield
{
    unsigned int raw;
    double scaled;
};

struct DrellYanYield
{
    Yield yield[Channel::static_size];
};


DrellYanYield GetYield
(
    TChain& chain,
    const double lumi
)
{
    DrellYanYield y;
    y.yield[Channel::ee].raw = chain.GetEntries("is_ee");
    y.yield[Channel::mm].raw = chain.GetEntries("is_mm");
    y.yield[Channel::ll].raw = chain.GetEntries("(is_ee || is_mm)");

    const double scale1fb      = chain.GetMaximum("scale1fb");
    const double nevts_full    = chain.GetMaximum("nevts");
    const double nevts_actual  = chain.GetEntries();
    const double scale_entries = nevts_actual/nevts_full; 

    y.yield[Channel::ee].scaled = scale1fb * lumi * scale_entries * y.yield[Channel::ee].raw;
    y.yield[Channel::mm].scaled = scale1fb * lumi * scale_entries * y.yield[Channel::mm].raw;
    y.yield[Channel::ll].scaled = scale1fb * lumi * scale_entries * y.yield[Channel::ll].raw;

    return y;
}

void PrintYield()
{
    const double lumi = 0.082; //fb^-1
    const bool verbose = true;

    std::map<at::Sample::value_type, TChain*> chain_map;
    for (size_t sidx = 0; sidx != s_SamplesCount; sidx++)
    {
        const at::Sample::value_type sample = s_Samples[sidx];
        chain_map[sample] = GetTChain(sample);
        if (verbose) {rt::PrintFilesFromTChain(chain_map[sample]);}
    }

    // get the yields
    std::map<at::Sample::value_type, DrellYanYield> yield_map;
    for (size_t sidx = 0; sidx != s_SamplesCount; sidx++)
    {
        const at::Sample::value_type sample = s_Samples[sidx];
        const std::string& name = at::GetSampleInfo(sample).name;
        yield_map[sample] = GetYield(*chain_map[sample], lumi); 

        if (verbose)
        {
        cout << Form("%s has raw yield: %u %u %u", 
            name.c_str(),
            yield_map[sample].yield[Channel::ee].raw,
            yield_map[sample].yield[Channel::mm].raw,
            yield_map[sample].yield[Channel::ll].raw) << endl;

        cout << Form("%s has scaled yield: %1.3f %1.3f %1.3f", 
            name.c_str(),
            yield_map[sample].yield[Channel::ee].scaled,
            yield_map[sample].yield[Channel::mm].scaled,
            yield_map[sample].yield[Channel::ll].scaled) << endl;
        }
    }
}
