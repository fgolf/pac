#include "PlotLooper.new.h"
#include <iostream>
#include <algorithm>
#include <tr1/array>
#include <cmath>
#include "mcSelections.h"
#include "SSB2012.h"
#include "rt/MiscTools.h"
#include "rt/is_equal.h"
#include "at/Predicates.h"
#include "at/VtxReweight.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "SSB2012.h"
//#include "CTable.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;

bool PassesSignalRegion(SignalRegion::value_type signal_region)
{
    using namespace ssb;
    switch (signal_region)
    {
        case SignalRegion::sr0 : return (ht() > 80.0  && pfmet() >  0.0);
        case SignalRegion::sr1 : return (ht() > 80.0  && pfmet() > 30.0);
        //case 10: return (njets() >= 4);
        //case 11: return (ht() > 300   && pfmet() > 150  && njets() >= 4 && nbtags() >= 3) || (ht() > 450.0 && pfmet() > 150.0 && njets() >= 4 && nbtags() == 2);
        //case 12: return (ht() > 240.0 && pfmet() > 150  && njets() >= 4 && nbtags() >= 3) || (ht() > 240.0 && pfmet() > 200.0 && njets() >= 5 && nbtags() == 2);
        //case 13: return (ht() > 240.0 && pfmet() > 150  && njets() >= 4 && nbtags() >= 3) || (ht() > 400.0 && pfmet() > 200.0 && njets() >= 4 && nbtags() == 2);
        //case 20: return (ht() > 80.0  && pfmet() > 0.0  && nbtags() == 2);
        //case 21: return (ht() > 80.0  && pfmet() > 0.0  && nbtags() >= 3);
        //case 22: return (njets() >= 4 && nbtags() == 2);
        //case 23: return (njets() >= 4 && nbtags() >= 3);
        //case 24: return (njets() >= 5 && nbtags() == 2);
        //case 25: return (njets() >= 5 && nbtags() >= 3);
        //case 26: return (pfmet() > 200.0 && njets() >= 4 && nbtags() == 2);
        //case 27: return (pfmet() > 150.0 && njets() >= 4 && nbtags() >= 3);
        //case 28: return (pfmet() > 200.0 && njets() >= 5 && nbtags() == 2);
        //case 29: return (pfmet() > 150.0 && njets() >= 5 && nbtags() >= 3);
        //case 30: return (ht() > 400.0 && pfmet() > 200.0 && njets() >= 4 && nbtags() == 2);
        //case 31: return ((njets() >= 4 && nbtags() == 2) || (njets() >= 4 && nbtags() >= 3));
        //case 32: return ((njets() >= 5 && nbtags() == 2) || (njets() >= 5 && nbtags() >= 3));
        //case 33: return ((pfmet() > 200.0 && njets() >= 4 && nbtags() == 2) || (pfmet() > 150.0 && njets() >= 4 && nbtags() >= 3));
        //case 34: return ((pfmet() > 200.0 && njets() >= 5 && nbtags() == 2) || (pfmet() > 150.0 && njets() >= 5 && nbtags() >= 3));
        //case 35: return ((ht() > 400.0 && pfmet() > 200.0 && njets() >= 4 && nbtags() == 2) || (pfmet() > 150.0 && njets() >= 4 && nbtags() >= 3));
        //case 40 : return (ht() > 80.0  && pfmet() >  0.0 && nbtags() == 2);
        default: return false;
    }
    return false;
}

// construct:
PlotLooper::PlotLooper
(
    const std::string& root_file_name,
    at::Sample::value_type sample,
    SignalRegion::value_type signal_region,
    const std::string& vtxreweight_file_name,
    const std::string& fr_file_name,
    const std::string& fr_hist_name,
    unsigned int num_btags,
    float mass_glu,
    float mass_lsp,
    float lumi,
    bool verbose,
    bool print,
    const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_vtx_reweight(not vtxreweight_file_name.empty())
    , m_nbtags(num_btags)
    , m_mass_glu(mass_glu)
    , m_mass_lsp(mass_lsp)
    , m_sample(sample)
    , m_signal_region(signal_region)
{
    // set vertex weight file
    if (m_do_vtx_reweight)
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

    // begin job
    BeginJob();
}

// destroy:
PlotLooper::~PlotLooper()
{
    // end  job
    EndJob();
}

// methods:
void PlotLooper::BeginJob()
{
    BookHists();
}

// end job
void PlotLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        hc.List();
    }
}

// binning contants
//std::tr1::array<float, 9> mu_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
//std::tr1::array<float, 9> el_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
//std::tr1::array<float, 7> vtx_bins = {{ 0.0, 10.0, 15, 20, 25, 30.0, 40.0}};

// book hists 
 void PlotLooper::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;
    TH1::SetDefaultSumw2(true);

    // Fake Counts
    //hc.Add(new TH1F("h_vtx_eff_den", "# vtxs (denominator); #vtxs;Events", vtx_bins.size()-1, vtx_bins.data()));
    //hc.Add(new TH1F("h_vtx_eff_num", "# vtxs (numerator); #vtxs;Events"  , vtx_bins.size()-1, vtx_bins.data()));

    for (size_t i = 0; i != at::DileptonHypType::static_size; i++)
    {
        for (size_t j = 0; j != at::DileptonChargeType::static_size; j++)
        {
            at::DileptonHypType::value_type hyp_type       = static_cast<at::DileptonHypType::value_type>(i);
            at::DileptonChargeType::value_type charge_type = static_cast<at::DileptonChargeType::value_type>(j);

            // channel names
            string chn = GetDileptonHypTypeName(hyp_type);
            string cht = GetDileptonHypTypeTitle(hyp_type);

            // charge names
            string qn = GetDileptonChargeTypeName(charge_type);
            string qt = GetDileptonChargeTypeTitle(charge_type);

            //cout << Form("%s %s %s %s", ch_name.c_str(), ch_title.c_str(), q_name.c_str(), q_title.c_str()) << endl;
            hc.Add(new TH1F(Form("h_yield_%s_%s", chn.c_str(), qn.c_str()), Form("yields (%s, %s);yield;Events", cht.c_str(), qt.c_str()), 3, 0, 3));
        }
    }

    //hc.Add(new TH1F("h_nvtxs"   , "# vtxs; #vtxs;Events"                     , 20 , 0     ,  40  ));
    //hc.Add(new TH1F("h_pt1"     , "Higher p_{T} lepton;p_{T} (GeV);Events"   , 25 , 0     , 250  ));
    //hc.Add(new TH1F("h_pt2"     , "Lower p_{T} lepton;p_{T} (GeV);Events"    , 25 , 0     , 250  ));
    //hc.Add(new TH1F("h_eta1"    , "Higher p_{T} lepton;#eta;Events"          , 10 , -2.5  , 2.5  ));
    //hc.Add(new TH1F("h_eta2"    , "Lower p_{T} lepton;#eta;Events"           , 10 , -2.5  , 2.5  ));
    //hc.Add(new TH1F("h_phi1"    , "Higher p_{T} lepton;#phi;Events"          ,  5 , -3.5  , 3.5  ));
    //hc.Add(new TH1F("h_phi2"    , "Lower p_{T} lepton;#phi;Events"           ,  5 , -3.5  , 3.5  ));
    //hc.Add(new TH1F("h_d01"     , "Higher p_{T} lepton;d_{0} (cm);Events"    , 25 , -0.05 , 0.05 ));
    //hc.Add(new TH1F("h_d02"     , "Lower p_{T} lepton;d_{0} (cm);Events"     , 25 , -0.05 , 0.05 ));
    //hc.Add(new TH1F("h_dz1"     , "Higher p_{T} lepton;d_{z} (cm);Events"    , 25 , -0.1  , 0.1  ));
    //hc.Add(new TH1F("h_dz2"     , "Lower p_{T} lepton;d_{z} (cm);Events"     , 25 , -0.1  , 0.1  ));
    //hc.Add(new TH1F("h_pt1_mu"  , "Higher p_{T} muon;p_{T} (GeV);Events"     , 25 , 0     , 250  ));
    //hc.Add(new TH1F("h_pt2_mu"  , "Lower p_{T} muon;p_{T} (GeV);Events"      , 25 , 0     , 250  ));
    //hc.Add(new TH1F("h_eta1_mu" , "Higher p_{T} muon;#eta;Events"            , 10 , -2.5  , 2.5  ));
    //hc.Add(new TH1F("h_eta2_mu" , "Lower p_{T} muon;#eta;Events"             , 10 , -2.5  , 2.5  ));
    //hc.Add(new TH1F("h_phi1_mu" , "Higher p_{T} muon;#phi;Events"            ,  5 , -3.5  , 3.5  ));
    //hc.Add(new TH1F("h_phi2_mu" , "Lower p_{T} muon;#phi;Events"             ,  5 , -3.5  , 3.5  ));
    //hc.Add(new TH1F("h_d01_mu"  , "Higher p_{T} muon;d_{0} (cm);Events"      , 25 , -0.05 , 0.05 ));
    //hc.Add(new TH1F("h_d02_mu"  , "Lower p_{T} muon;d_{0} (cm);Events"       , 25 , -0.05 , 0.05 ));
    //hc.Add(new TH1F("h_dz1_mu"  , "Higher p_{T} muon;d_{z} (cm);Events"      , 25 , -0.1  , 0.1  ));
    //hc.Add(new TH1F("h_dz2_mu"  , "Lower p_{T} muon;d_{z} (cm);Events"       , 25 , -0.1  , 0.1  ));
    //hc.Add(new TH1F("h_iso1_mu" , "Higher p_{T} muon;Iso;Events"             , 10 , 0     , 1.0  ));
    //hc.Add(new TH1F("h_iso2_mu" , "Lower p_{T} muon;Iso;Events"              , 10 , 0     , 1.0  ));
    //hc.Add(new TH1F("h_pt1_el"  , "Higher p_{T} electron;p_{T} (GeV);Events" , 25 , 0     , 250  ));
    //hc.Add(new TH1F("h_pt2_el"  , "Lower p_{T} electron;p_{T} (GeV);Events"  , 25 , 0     , 250  ));
    //hc.Add(new TH1F("h_eta1_el" , "Higher p_{T} electron;#eta;Events"        , 10 , -2.5  , 2.5  ));
    //hc.Add(new TH1F("h_eta2_el" , "Lower p_{T} electron;#eta;Events"         , 10 , -2.5  , 2.5  ));
    //hc.Add(new TH1F("h_phi1_el" , "Higher p_{T} electron;#phi;Events"        ,  5 , -3.5  , 3.5  ));
    //hc.Add(new TH1F("h_phi2_el" , "Lower p_{T} electron;#phi;Events"         ,  5 , -3.5  , 3.5  ));
    //hc.Add(new TH1F("h_d01_el"  , "Higher p_{T} electron;d_{0} (cm);Events"  , 25 , -0.05 , 0.05 ));
    //hc.Add(new TH1F("h_d02_el"  , "Lower p_{T} electron;d_{0} (cm);Events"   , 25 , -0.05 , 0.05 ));
    //hc.Add(new TH1F("h_dz1_el"  , "Higher p_{T} electron;d_{z} (cm);Events"  , 25 , -0.1  , 0.1  ));
    //hc.Add(new TH1F("h_dz2_el"  , "Lower p_{T} electron;d_{z} (cm);Events"   , 25 , -0.1  , 0.1  ));
    //hc.Add(new TH1F("h_iso1_el" , "Higher p_{T} electron;Iso;Events"         , 10 , 0     , 1.0  ));
    //hc.Add(new TH1F("h_iso2_el" , "Lower p_{T} electron;Iso;Events"          , 10 , 0     , 1.0  ));
    //hc.Add(new TH1F("h_ht"      , "H_{T};H_{T} (GeV);Events"                 , 20 , 0     , 1000 ));
    //hc.Add(new TH1F("h_mt"      , "m_{T};m_{T} (GeV);Events"                 , 16 , 0     , 800  ));
    //hc.Add(new TH1F("h_met"     , "MET;E_{T}^{miss} (GeV);Events"            , 16 , 0     , 800  ));
    //hc.Add(new TH1F("h_nbtags"  , "# btags;# btags;Events"                   , 10 , 0     , 10   ));
    //hc.Add(new TH1F("h_njets"   , "# jets;# jets;Events"                     , 10 , 0     , 10   ));
        
    return;
}

    // main analysis function operator 
int PlotLooper::operator()(long event)
{
    using namespace std;
    using namespace ssb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // which dataset

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //
       
        // mm events for now
        //if (type() != 1)
        //{
        //    return 0;
        //}

        // only keep good lumi (data only)
        //if (is_real_data() && not is_good_lumi())
        //{
        //    return 0;
        //}

        // charge type
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (is_ss()) {charge_type = DileptonChargeType::SS;}
        if (is_sf()) {charge_type = DileptonChargeType::SF;}
        if (is_df()) {charge_type = DileptonChargeType::DF;}
        if (is_os()) {charge_type = DileptonChargeType::OS;}
        if (charge_type == DileptonChargeType::static_size)
        {
            return 0;
        }

        // dilepton hyp type: 1 mm, 2 em, 3ee
        DileptonHypType::value_type hyp_type = static_cast<DileptonHypType::value_type>(dilep_type());

        // two jet events
        if (njets() < 2)
        {
            return 0;
        }

        // two btagged jets
        if (nbtags() < static_cast<int>(m_nbtags))
        {
            return 0;
        }

        // passes signal region
        if (not PassesSignalRegion(m_signal_region))
        {
            return 0;
        }

        // require both leptons to be truth matched
        //if (not (leptru1() && leptru2()))
        //{
        //    return 0;
        //}

        // select m_gluino and m_lsp
        if (m_sample == at::Sample::t1tttt)
        {
            if (!rt::is_equal(m_mass_glu, sparm0()) || !rt::is_equal(m_mass_lsp, sparm1()))
            {
                return 0;
            }
            //cout << Form("sparm0 %f m_glu %f", sparm0(), m_mass_glu) << endl;;
            //cout << Form("sparm1 %f m_lsp %f", sparm1(), m_mass_lsp) << endl;;
        }

        // Fill Hists 
        // ----------------------------------------------------------------------------------------------------------------------------//

        // charge names
        string qn = GetDileptonChargeTypeName(charge_type);

        // scale
        float vtxw = 1.0;
        if (m_do_vtx_reweight)
        {
            vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        }
        m_lumi = is_real_data() ? 1.0 : m_lumi;
        float evt_weight = m_lumi * scale1fb() * vtxw;
       
        // basic yields       
        rt::Fill(hc[Form("h_yield_ll_%s", qn.c_str())], 1, evt_weight);

        // indididual channels
        string chn = GetDileptonHypTypeName(hyp_type);

        rt::Fill(hc[Form("h_yield_%s_%s", chn.c_str(), qn.c_str())], 1, evt_weight);

        //const LorentzVector& p41 = lep1_p4();
        //const LorentzVector& p42 = lep2_p4();
        ////const LorentzVector& p41 = std::max(lep1_p4(),lep2_p4(), at::SortByPt<LorentzVector>());
        ////const LorentzVector& p42 = std::min(lep1_p4(),lep2_p4(), at::SortByPt<LorentzVector>());

        //rt::Fill(hc["h_nvtxs" ], nvtxs()   , evt_weight);
        //rt::Fill(hc["h_pt1"   ], p41.pt()  , evt_weight);
        //rt::Fill(hc["h_pt2"   ], p42.pt()  , evt_weight);
        //rt::Fill(hc["h_eta1"  ], p41.eta() , evt_weight);
        //rt::Fill(hc["h_eta2"  ], p42.eta() , evt_weight);
        //rt::Fill(hc["h_phi1"  ], p41.phi() , evt_weight);
        //rt::Fill(hc["h_phi2"  ], p42.phi() , evt_weight);
        //rt::Fill(hc["h_d01"   ], lep1_d0() , evt_weight);
        //rt::Fill(hc["h_d02"   ], lep2_d0() , evt_weight);
        //rt::Fill(hc["h_dz1"   ], lep1_dz() , evt_weight);
        //rt::Fill(hc["h_dz2"   ], lep2_dz() , evt_weight);
        //rt::Fill(hc["h_ht"    ], ht()      , evt_weight);
        //rt::Fill(hc["h_mt"    ], lep1_mt() , evt_weight);
        //rt::Fill(hc["h_met"   ], pfmet()   , evt_weight);
        //rt::Fill(hc["h_nbtags"], nbtags()  , evt_weight);
        //rt::Fill(hc["h_njets" ], njets()   , evt_weight);

        //if (abs(lep1_pdgid())==13) 
        //{
        //    rt::Fill(hc["h_pt1_mu" ], p41.pt()       , evt_weight);
        //    rt::Fill(hc["h_eta1_mu"], p41.eta()      , evt_weight);
        //    rt::Fill(hc["h_phi1_mu"], p41.phi()      , evt_weight);
        //    rt::Fill(hc["h_d01_mu" ], lep1_d0()      , evt_weight);
        //    rt::Fill(hc["h_dz1_mu" ], lep1_dz()      , evt_weight);
        //    rt::Fill(hc["h_iso1_mu"], lep1_corpfiso(), evt_weight);
        //}
        //if (abs(lep2_pdgid())==13) 
        //{
        //    rt::Fill(hc["h_pt2_mu" ], p42.pt()       , evt_weight);
        //    rt::Fill(hc["h_eta2_mu"], p42.eta()      , evt_weight);
        //    rt::Fill(hc["h_phi2_mu"], p42.phi()      , evt_weight);
        //    rt::Fill(hc["h_d02_mu" ], lep2_d0()      , evt_weight);
        //    rt::Fill(hc["h_dz2_mu" ], lep2_dz()      , evt_weight);
        //    rt::Fill(hc["h_iso2_mu"], lep2_corpfiso(), evt_weight);
        //}
        //if (abs(lep1_pdgid())==11)
        //{
        //    rt::Fill(hc["h_pt1_el" ], p41.pt()       , evt_weight);
        //    rt::Fill(hc["h_eta1_el"], p41.eta()      , evt_weight);
        //    rt::Fill(hc["h_phi1_el"], p41.phi()      , evt_weight);
        //    rt::Fill(hc["h_d01_el" ], lep1_d0()      , evt_weight);
        //    rt::Fill(hc["h_dz1_el" ], lep1_dz()      , evt_weight);
        //    rt::Fill(hc["h_iso1_el"], lep1_corpfiso(), evt_weight);
        //}
        //if (abs(lep2_pdgid())==11)
        //{
        //    rt::Fill(hc["h_pt2_el" ], p42.pt()       , evt_weight);
        //    rt::Fill(hc["h_eta2_el"], p42.eta()      , evt_weight);
        //    rt::Fill(hc["h_phi2_el"], p42.phi()      , evt_weight);
        //    rt::Fill(hc["h_d02_el" ], lep2_d0()      , evt_weight);
        //    rt::Fill(hc["h_dz2_el" ], lep2_dz()      , evt_weight);
        //    rt::Fill(hc["h_iso2_el"], lep2_corpfiso(), evt_weight);
        //}
        //const LorentzVector& p41 = std::max(lep1_p4(),lep2_p4(), at::SortByPt<LorentzVector>());
        //const LorentzVector& p42 = std::min(lep1_p4(),lep2_p4(), at::SortByPt<LorentzVector>());
        //float pt1 = p41.pt();
        //float pt2 = p42.pt();
        //float l1_id  = pt1 > pt2 ? lep1_pdgid()    : lep2_pdgid();
        //float l2_id  = pt1 > pt2 ? lep2_pdgid()    : lep1_pdgid();
        //float l1_iso = pt1 > pt2 ? lep1_corpfiso() : lep2_corpfiso();
        //float l2_iso = pt2 > pt1 ? lep2_corpfiso() : lep1_corpfiso(); 
        //float l1_d0  = pt1 > pt2 ? lep1_d0()       : lep2_d0();      
        //float l2_d0  = pt2 > pt1 ? lep2_d0()       : lep1_d0();      
        //float l1_dz  = pt1 > pt2 ? lep1_dz()       : lep2_dz();      
        //float l2_dz  = pt2 > pt1 ? lep2_dz()       : lep1_dz();      

        //rt::Fill(hc["h_nvtxs" ], nvtxs()   , evt_weight);
        //rt::Fill(hc["h_pt1"   ], p41.pt()  , evt_weight);
        //rt::Fill(hc["h_pt2"   ], p42.pt()  , evt_weight);
        //rt::Fill(hc["h_eta1"  ], p41.eta() , evt_weight);
        //rt::Fill(hc["h_eta2"  ], p42.eta() , evt_weight);
        //rt::Fill(hc["h_phi1"  ], p41.phi() , evt_weight);
        //rt::Fill(hc["h_phi2"  ], p42.phi() , evt_weight);
        //rt::Fill(hc["h_d01"   ], l1_d0     , evt_weight);
        //rt::Fill(hc["h_d02"   ], l2_d0     , evt_weight);
        //rt::Fill(hc["h_dz1"   ], l1_dz     , evt_weight);
        //rt::Fill(hc["h_dz2"   ], l2_dz     , evt_weight);
        //rt::Fill(hc["h_ht"    ], ht()      , evt_weight);
        //rt::Fill(hc["h_mt"    ], lep1_mt() , evt_weight);
        //rt::Fill(hc["h_met"   ], pfmet()   , evt_weight);
        //rt::Fill(hc["h_nbtags"], nbtags()  , evt_weight);
        //rt::Fill(hc["h_njets" ], njets()   , evt_weight);

        //if (abs(l1_id)==13) 
        //{
        //    rt::Fill(hc["h_pt1_mu" ], p41.pt()  , evt_weight);
        //    rt::Fill(hc["h_eta1_mu"], p41.eta() , evt_weight);
        //    rt::Fill(hc["h_phi1_mu"], p41.phi() , evt_weight);
        //    rt::Fill(hc["h_d01_mu" ], l1_d0     , evt_weight);
        //    rt::Fill(hc["h_dz1_mu" ], l1_dz     , evt_weight);
        //    rt::Fill(hc["h_iso1_mu"], l1_iso    , evt_weight);
        //}
        //if (abs(l2_id)==13) 
        //{
        //    rt::Fill(hc["h_pt2_mu" ] , p42.pt()  , evt_weight);
        //    rt::Fill(hc["h_eta2_mu"] , p42.eta() , evt_weight);
        //    rt::Fill(hc["h_phi2_mu"] , p42.phi() , evt_weight);
        //    rt::Fill(hc["h_d02_mu" ] , l2_d0     , evt_weight);
        //    rt::Fill(hc["h_dz2_mu" ] , l2_dz     , evt_weight);
        //    rt::Fill(hc["h_iso2_mu"] , l2_iso    , evt_weight);
        //}
        //if (abs(l1_id)==11)
        //{
        //    rt::Fill(hc["h_pt1_el" ], p41.pt()  , evt_weight);
        //    rt::Fill(hc["h_eta1_el"], p41.eta() , evt_weight);
        //    rt::Fill(hc["h_phi1_el"], p41.phi() , evt_weight);
        //    rt::Fill(hc["h_d01_el" ], l1_d0     , evt_weight);
        //    rt::Fill(hc["h_dz1_el" ], l1_dz     , evt_weight);
        //    rt::Fill(hc["h_iso1_el"], l1_iso    , evt_weight);
        //}
        //if (abs(l2_id)==11)
        //{
        //    rt::Fill(hc["h_pt2_el" ] , p42.pt()  , evt_weight);
        //    rt::Fill(hc["h_eta2_el"] , p42.eta() , evt_weight);
        //    rt::Fill(hc["h_phi2_el"] , p42.phi() , evt_weight);
        //    rt::Fill(hc["h_d02_el" ] , l2_d0     , evt_weight);
        //    rt::Fill(hc["h_dz2_el" ] , l2_dz     , evt_weight);
        //    rt::Fill(hc["h_iso2_el"] , l2_iso    , evt_weight);
        //}

    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 
