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
static const size_t s_SamplesCount = 7;//sizeof(s_Samples)/sizeof(s_SamplesCount);
static const at::Sample::value_type s_Samples[s_SamplesCount] =
{
    at::Sample::data,
    at::Sample::dy,
    at::Sample::wjets,
    at::Sample::ttjets,
    at::Sample::ww,
    at::Sample::wz,
    at::Sample::zz
};

//static const double s_SDEfficiency[s_SamplesCount] =
//{
//    /*data   =*/ (1.0                  ), 
//    /*dy     =*/ (27137253.0/30459500.0),
//    /*wjets  =*/ (14890630.0/18393090.0),
//    /*ttjets =*/ (6923750.0 /6923750.0 ),
//    /*ww     =*/ (1933235.0 /1933235.0 ), 
//    /*wz     =*/ (2937874.0 /3215990.0 ),
//    /*zz     =*/ (857982.0  /954911.0  )
//};

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
    const char* const fmt() const {return Form("%1.2f", scaled);}
};

struct DrellYanYield
{
    Yield yield[Channel::static_size];
};


DrellYanYield GetYield
(
    const at::Sample::value_type sample,
    const double lumi
)
{
    TChain& chain = *GetTChain(sample);

    DrellYanYield y;
    y.yield[Channel::ee].raw = chain.GetEntries("is_ee");
    y.yield[Channel::mm].raw = chain.GetEntries("is_mm");
    y.yield[Channel::ll].raw = chain.GetEntries("(is_ee || is_mm)");


    const double scale1fb     = chain.GetMaximum("scale1fb");
    const double nevts_full   = chain.GetMaximum("nevts");
    const double nevts_actual = chain.GetEntries();
    double scale_entries      = (nevts_full/nevts_actual);
    switch (sample)
    {
        case at::Sample::data   : scale_entries *= (1.0                  ); break; 
        case at::Sample::dy     : scale_entries *= (27137253.0/30459500.0); break;
        case at::Sample::wjets  : scale_entries *= (14890630.0/18393090.0); break;
        case at::Sample::ttjets : scale_entries *= (6923750.0 /6923750.0 ); break;
        case at::Sample::ww     : scale_entries *= (1933235.0 /1933235.0 ); break; 
        case at::Sample::wz     : scale_entries *= (2937874.0 /3215990.0 ); break;
        case at::Sample::zz     : scale_entries *= (857982.0  /954911.0  ); break;
        default: {/*do nothing*/}
    };

    y.yield[Channel::ee].scaled = scale1fb * lumi * scale_entries * y.yield[Channel::ee].raw;
    y.yield[Channel::mm].scaled = scale1fb * lumi * scale_entries * y.yield[Channel::mm].raw;
    y.yield[Channel::ll].scaled = scale1fb * lumi * scale_entries * y.yield[Channel::ll].raw;

    return y;
}

void PrintYield(const bool latex = false)
{
    using namespace at;
    const double lumi = 0.082; //fb^-1

    // get the yields
    std::map<at::Sample::value_type, DrellYanYield> yield_map;
    for (size_t sidx = 0; sidx != s_SamplesCount; sidx++)
    {
        const at::Sample::value_type sample = s_Samples[sidx];
        yield_map[sample] = GetYield(sample, lumi); 
    }

    CTable t1;
    t1.useTitle();
    t1.setTitle("Yields raw");
    t1.setTable() (                                                                           "$ee$",                                     "$\\mu\\mu$",                                    "$\\ell\\ell$")
                  ( "$DY \\rightarrow \\ell\\ell$", yield_map[Sample::dy    ].yield[Channel::ee].raw, yield_map[Sample::dy    ].yield[Channel::mm].raw, yield_map[Sample::dy    ].yield[Channel::ll].raw )
                  ( "W + jets"                    , yield_map[Sample::wjets ].yield[Channel::ee].raw, yield_map[Sample::wjets ].yield[Channel::mm].raw, yield_map[Sample::wjets ].yield[Channel::ll].raw )
                  ( "$t\\bar{t} + jets$"          , yield_map[Sample::ttjets].yield[Channel::ee].raw, yield_map[Sample::ttjets].yield[Channel::mm].raw, yield_map[Sample::ttjets].yield[Channel::ll].raw )
                  ( "WW"                          , yield_map[Sample::ww    ].yield[Channel::ee].raw, yield_map[Sample::ww    ].yield[Channel::mm].raw, yield_map[Sample::ww    ].yield[Channel::ll].raw )
                  ( "WZ"                          , yield_map[Sample::wz    ].yield[Channel::ee].raw, yield_map[Sample::wz    ].yield[Channel::mm].raw, yield_map[Sample::wz    ].yield[Channel::ll].raw )
                  ( "ZZ"                          , yield_map[Sample::zz    ].yield[Channel::ee].raw, yield_map[Sample::zz    ].yield[Channel::mm].raw, yield_map[Sample::zz    ].yield[Channel::ll].raw )
                  ( "data"                        , yield_map[Sample::data  ].yield[Channel::ee].raw, yield_map[Sample::data  ].yield[Channel::mm].raw, yield_map[Sample::data  ].yield[Channel::ll].raw )
                  ;

    CTable t2;
    t2.useTitle();
    t2.setTitle("Yields scaled");
    t2.setTable() (                                                                              "$ee$",                                        "$\\mu\\mu$",                                      "$\\ell\\ell$")
                  ( "$DY \\rightarrow \\ell\\ell$", yield_map[Sample::dy    ].yield[Channel::ee].fmt(), yield_map[Sample::dy    ].yield[Channel::mm].fmt(), yield_map[Sample::dy    ].yield[Channel::ll].fmt())
                  ( "W + jets"                    , yield_map[Sample::wjets ].yield[Channel::ee].fmt(), yield_map[Sample::wjets ].yield[Channel::mm].fmt(), yield_map[Sample::wjets ].yield[Channel::ll].fmt())
                  ( "$t\\bar{t} + jets$"          , yield_map[Sample::ttjets].yield[Channel::ee].fmt(), yield_map[Sample::ttjets].yield[Channel::mm].fmt(), yield_map[Sample::ttjets].yield[Channel::ll].fmt())
                  ( "WW"                          , yield_map[Sample::ww    ].yield[Channel::ee].fmt(), yield_map[Sample::ww    ].yield[Channel::mm].fmt(), yield_map[Sample::ww    ].yield[Channel::ll].fmt())
                  ( "WZ"                          , yield_map[Sample::wz    ].yield[Channel::ee].fmt(), yield_map[Sample::wz    ].yield[Channel::mm].fmt(), yield_map[Sample::wz    ].yield[Channel::ll].fmt())
                  ( "ZZ"                          , yield_map[Sample::zz    ].yield[Channel::ee].fmt(), yield_map[Sample::zz    ].yield[Channel::mm].fmt(), yield_map[Sample::zz    ].yield[Channel::ll].fmt())
                  ( "data"                        , yield_map[Sample::data  ].yield[Channel::ee].raw   , yield_map[Sample::data  ].yield[Channel::mm].raw   , yield_map[Sample::data  ].yield[Channel::ll].raw   )
                  ;
    // get TChains
    TChain& chain = *GetTChain(Sample::dy);
    const double lumi_nb = lumi * 1e6; // nb^-1

    // cross section
    const double acc_zmm   = (float)chain.GetEntries("is_mm")/
                             (float)chain.GetEntries("is_z_mm && (60 < gen_z_p4.mass() && gen_z_p4.mass() < 120)");
    const double N_bkg_zmm = yield_map[Sample::wjets ].yield[Channel::mm].scaled + 
                             yield_map[Sample::wjets ].yield[Channel::mm].scaled +
                             yield_map[Sample::ttjets].yield[Channel::mm].scaled +
                             yield_map[Sample::ww    ].yield[Channel::mm].scaled +
                             yield_map[Sample::wz    ].yield[Channel::mm].scaled;
    const double N_obs_zmm = yield_map[Sample::data].yield[Channel::mm].raw;
    const double N_sig_zmm = N_obs_zmm - N_bkg_zmm;
    const double sigma_zmm = N_sig_zmm / (lumi_nb * acc_zmm);

    const double acc_zee   = (float)chain.GetEntries("is_ee")/
                             (float)chain.GetEntries("is_z_ee && (60 < gen_z_p4.mass() && gen_z_p4.mass() < 120)");
    const double N_bkg_zee = yield_map[Sample::wjets ].yield[Channel::ee].scaled + 
                             yield_map[Sample::wjets ].yield[Channel::ee].scaled +
                             yield_map[Sample::ttjets].yield[Channel::ee].scaled +
                             yield_map[Sample::ww    ].yield[Channel::ee].scaled +
                             yield_map[Sample::wz    ].yield[Channel::ee].scaled;
    const double N_obs_zee = yield_map[Sample::data].yield[Channel::ee].raw;
    const double N_sig_zee = N_obs_zee - N_bkg_zee;
    const double sigma_zee = N_sig_zee / (lumi_nb * acc_zee);

    // print results
    if (latex)
    {
        t1.printTex();
        t2.printTex();

        cout << endl;
        cout << "\\sigma(pp \\rightarrow Z) \\times BR(Z \\rightarrow \\mu\\mu) = "
             << "\\frac{N_{obs} - N_{bkg}}{lumi \\times A} = "
             << Form("\\frac{%1.2f - %1.2f}{%1.2f \\times %1.2f}", N_obs_zmm, N_bkg_zmm, lumi_nb, acc_zmm)
             << " = " << std::setprecision(3) << sigma_zmm << "\\rm{\\ nb} \\\\" << endl;
        cout << "\\sigma(pp \\rightarrow Z) \\times BR(Z \\rightarrow ee) = "
             << "\\frac{N_{obs} - N_{bkg}}{lumi \\times A} = "
             << Form("\\frac{%1.2f - %1.2f}{%1.2f \\times %1.2f}", N_obs_zee, N_bkg_zee, lumi_nb, acc_zee)
             << " = " << std::setprecision(3) << sigma_zee << "\\rm{\\ nb} \\\\" << endl;
    }
    else
    {
        cout << t1 << endl;
        cout << endl;
        cout << t2 << endl;

        cout << endl;
        cout << "Sigma(pp --> Z) * BR(Z --> mm) = "
             << "(N_obs - N_bkg)/(lumi * A) = "
             << Form("(%1.2f - %1.2f)/(%1.2f * %1.2f)", N_obs_zmm, N_bkg_zmm, lumi_nb, acc_zmm)
             << " = " << std::setprecision(3) << sigma_zmm << " nb" << endl;
        cout << "Sigma(pp --> Z) * BR(Z --> ee) = "
             << "(N_obs - N_bkg)/(lumi * A) = "
             << Form("(%1.2f - %1.2f)/(%1.2f * %1.2f)", N_obs_zee, N_bkg_zee, lumi_nb, acc_zee)
             << " = " << std::setprecision(3) << sigma_zee << " nb" << endl;
    }
}
