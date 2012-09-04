#include "PlotLooper.h"
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
#include "SignalRegion.h"
#include "SSB2012.h"
//#include "CTable.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;

// construct:
PlotLooper::PlotLooper
(
    const std::string& root_file_name,
    at::Sample::value_type sample,
    SignalRegion::value_type signal_region,
    const std::string& vtxreweight_file_name,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    unsigned int num_btags,
    bool do_scale_factors,
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
    , m_do_scale_factors(do_scale_factors)
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

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_mufr40c")->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_elfr40c")->Clone()));
    if (not h_mufr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_mufr40c doesn't exist");}
    h_mufr->SetDirectory(0);
    if (not h_elfr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_elfr40c doesn't exist");}
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: SSAnalysisLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

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

    hc.Add(new TH1F("h_lumi"   , "integrated lumi used for these plots", 10000, 0, 100));

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

            // name and title suffixes
            string ns = Form("_%s_%s"   ,  chn.c_str(), qn.c_str());
            string ts = Form(" (%s, %s)",  cht.c_str(), qn.c_str());

            //cout << Form("%s %s %s %s", ch_name.c_str(), ch_title.c_str(), q_name.c_str(), q_title.c_str()) << endl;
            hc.Add(new TH1F(Form("h_yield%s"   , ns.c_str()), Form("yields%s;yield;Events"                      , ts.c_str()), 3 ,  0      , 3   ));
            //hc.Add(new TH1F(Form("h_nvtxs%s"   , ns.c_str()), Form("# vtxs%s; #vtxs;Events"                     , ts.c_str()), 20 , 0     ,  40  ));
            //hc.Add(new TH1F(Form("h_pt1%s"     , ns.c_str()), Form("Higher p_{T} lepton%s;p_{T} (GeV);Events"   , ts.c_str()), 25 , 0     , 250  ));
            //hc.Add(new TH1F(Form("h_pt2%s"     , ns.c_str()), Form("Lower p_{T} lepton%s;p_{T} (GeV);Events"    , ts.c_str()), 25 , 0     , 250  ));
            //hc.Add(new TH1F(Form("h_eta1%s"    , ns.c_str()), Form("Higher p_{T} lepton%s;#eta;Events"          , ts.c_str()), 10 , -2.5  , 2.5  ));
            //hc.Add(new TH1F(Form("h_eta2%s"    , ns.c_str()), Form("Lower p_{T} lepton%s;#eta;Events"           , ts.c_str()), 10 , -2.5  , 2.5  ));
            //hc.Add(new TH1F(Form("h_phi1%s"    , ns.c_str()), Form("Higher p_{T} lepton%s;#phi;Events"          , ts.c_str()),  5 , -3.5  , 3.5  ));
            //hc.Add(new TH1F(Form("h_phi2%s"    , ns.c_str()), Form("Lower p_{T} lepton%s;#phi;Events"           , ts.c_str()),  5 , -3.5  , 3.5  ));
            //hc.Add(new TH1F(Form("h_d01%s"     , ns.c_str()), Form("Higher p_{T} lepton%s;d_{0} (cm);Events"    , ts.c_str()), 25 , -0.05 , 0.05 ));
            //hc.Add(new TH1F(Form("h_d02%s"     , ns.c_str()), Form("Lower p_{T} lepton%s;d_{0} (cm);Events"     , ts.c_str()), 25 , -0.05 , 0.05 ));
            //hc.Add(new TH1F(Form("h_dz1%s"     , ns.c_str()), Form("Higher p_{T} lepton%s;d_{z} (cm);Events"    , ts.c_str()), 25 , -0.1  , 0.1  ));
            //hc.Add(new TH1F(Form("h_dz2%s"     , ns.c_str()), Form("Lower p_{T} lepton%s;d_{z} (cm);Events"     , ts.c_str()), 25 , -0.1  , 0.1  ));
            //hc.Add(new TH1F(Form("h_pt1_mu%s"  , ns.c_str()), Form("Higher p_{T} muon%s;p_{T} (GeV);Events"     , ts.c_str()), 25 , 0     , 250  ));
            //hc.Add(new TH1F(Form("h_pt2_mu%s"  , ns.c_str()), Form("Lower p_{T} muon%s;p_{T} (GeV);Events"      , ts.c_str()), 25 , 0     , 250  ));
            //hc.Add(new TH1F(Form("h_eta1_mu%s" , ns.c_str()), Form("Higher p_{T} muon%s;#eta;Events"            , ts.c_str()), 10 , -2.5  , 2.5  ));
            //hc.Add(new TH1F(Form("h_eta2_mu%s" , ns.c_str()), Form("Lower p_{T} muon%s;#eta;Events"             , ts.c_str()), 10 , -2.5  , 2.5  ));
            //hc.Add(new TH1F(Form("h_phi1_mu%s" , ns.c_str()), Form("Higher p_{T} muon%s;#phi;Events"            , ts.c_str()),  5 , -3.5  , 3.5  ));
            //hc.Add(new TH1F(Form("h_phi2_mu%s" , ns.c_str()), Form("Lower p_{T} muon%s;#phi;Events"             , ts.c_str()),  5 , -3.5  , 3.5  ));
            //hc.Add(new TH1F(Form("h_d01_mu%s"  , ns.c_str()), Form("Higher p_{T} muon%s;d_{0} (cm);Events"      , ts.c_str()), 25 , -0.05 , 0.05 ));
            //hc.Add(new TH1F(Form("h_d02_mu%s"  , ns.c_str()), Form("Lower p_{T} muon%s;d_{0} (cm);Events"       , ts.c_str()), 25 , -0.05 , 0.05 ));
            //hc.Add(new TH1F(Form("h_dz1_mu%s"  , ns.c_str()), Form("Higher p_{T} muon%s;d_{z} (cm);Events"      , ts.c_str()), 25 , -0.1  , 0.1  ));
            //hc.Add(new TH1F(Form("h_dz2_mu%s"  , ns.c_str()), Form("Lower p_{T} muon%s;d_{z} (cm);Events"       , ts.c_str()), 25 , -0.1  , 0.1  ));
            //hc.Add(new TH1F(Form("h_iso1_mu%s" , ns.c_str()), Form("Higher p_{T} muon%s;Iso;Events"             , ts.c_str()), 10 , 0     , 1.0  ));
            //hc.Add(new TH1F(Form("h_iso2_mu%s" , ns.c_str()), Form("Lower p_{T} muon%s;Iso;Events"              , ts.c_str()), 10 , 0     , 1.0  ));
            //hc.Add(new TH1F(Form("h_pt1_el%s"  , ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events" , ts.c_str()), 25 , 0     , 250  ));
            //hc.Add(new TH1F(Form("h_pt2_el%s"  , ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events"  , ts.c_str()), 25 , 0     , 250  ));
            //hc.Add(new TH1F(Form("h_eta1_el%s" , ns.c_str()), Form("Higher p_{T} electron%s;#eta;Events"        , ts.c_str()), 10 , -2.5  , 2.5  ));
            //hc.Add(new TH1F(Form("h_eta2_el%s" , ns.c_str()), Form("Lower p_{T} electron%s;#eta;Events"         , ts.c_str()), 10 , -2.5  , 2.5  ));
            //hc.Add(new TH1F(Form("h_phi1_el%s" , ns.c_str()), Form("Higher p_{T} electron%s;#phi;Events"        , ts.c_str()),  5 , -3.5  , 3.5  ));
            //hc.Add(new TH1F(Form("h_phi2_el%s" , ns.c_str()), Form("Lower p_{T} electron%s;#phi;Events"         , ts.c_str()),  5 , -3.5  , 3.5  ));
            //hc.Add(new TH1F(Form("h_d01_el%s"  , ns.c_str()), Form("Higher p_{T} electron%s;d_{0} (cm);Events"  , ts.c_str()), 25 , -0.05 , 0.05 ));
            //hc.Add(new TH1F(Form("h_d02_el%s"  , ns.c_str()), Form("Lower p_{T} electron%s;d_{0} (cm);Events"   , ts.c_str()), 25 , -0.05 , 0.05 ));
            //hc.Add(new TH1F(Form("h_dz1_el%s"  , ns.c_str()), Form("Higher p_{T} electron%s;d_{z} (cm);Events"  , ts.c_str()), 25 , -0.1  , 0.1  ));
            //hc.Add(new TH1F(Form("h_dz2_el%s"  , ns.c_str()), Form("Lower p_{T} electron%s;d_{z} (cm);Events"   , ts.c_str()), 25 , -0.1  , 0.1  ));
            //hc.Add(new TH1F(Form("h_iso1_el%s" , ns.c_str()), Form("Higher p_{T} electron%s;Iso;Events"         , ts.c_str()), 10 , 0     , 1.0  ));
            //hc.Add(new TH1F(Form("h_iso2_el%s" , ns.c_str()), Form("Lower p_{T} electron%s;Iso;Events"          , ts.c_str()), 10 , 0     , 1.0  ));
            //hc.Add(new TH1F(Form("h_ht%s"      , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"                 , ts.c_str()), 20 , 0     , 1000 ));
            //hc.Add(new TH1F(Form("h_mt%s"      , ns.c_str()), Form("m_{T}%s;m_{T} (GeV);Events"                 , ts.c_str()), 16 , 0     , 800  ));
            //hc.Add(new TH1F(Form("h_met%s"     , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events"            , ts.c_str()), 16 , 0     , 800  ));
            //hc.Add(new TH1F(Form("h_nbtags%s"  , ns.c_str()), Form("# btags%s;# btags;Events"                   , ts.c_str()), 10 , 0     , 10   ));
            //hc.Add(new TH1F(Form("h_njets%s"   , ns.c_str()), Form("# jets%s;# jets;Events"                     , ts.c_str()), 10 , 0     , 10   ));
        }
    }

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

        if (is_real_data() && !is_good_lumi())
        {
            return 0;
        }
        {
            hc["h_lumi"]->Fill(m_lumi);
        }
       
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

        // apply scale factors
        if (m_do_scale_factors && !is_real_data())
        {
            evt_weight *= sf_lepeff();
            if (m_nbtags>=2)
            {
                if (m_signal_region == SignalRegion::sr7)
                {
                    evt_weight *= (nbtags() >= 3 ? sf_nbtag3() : 1.0);
                }
                else
                {
                    evt_weight *= (nbtags() >= 2 ? sf_nbtag() : 1.0);
                }
            }
        }

        // fake/flip weight
        float fr1 = 1.0;
        float fr2 = 1.0;
        float fl1 = 1.0;
        float fl2 = 1.0;
        switch (charge_type)
        {
            case DileptonChargeType::SF: 
                fr1 = lep1_is_fo() * GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                fr2 = lep2_is_fo() * GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                evt_weight *= fr1/(1.0 - fr1) + fr2/(1.0 - fr2); 
                break;
            case DileptonChargeType::DF: 
                fr1 = GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                fr2 = GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                evt_weight *= fr1/(1.0 - fr1) * fr2/(1.0 - fr2); 
                break;
            case DileptonChargeType::OS: 
                fl1 = GetFlipRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                fl2 = GetFlipRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                evt_weight *= fl1/(1.0 - fl1) + fl2/(1.0 - fl2); 
                break;
            default:
                break;
        }
       
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

float PlotLooper::GetFakeRateValue(int lep_id, float pt, float eta) const 
{
    using namespace tas;

    if (!h_mufr)
    {
        if (m_verbose) {std::cout << "h_mufr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (!h_elfr)
    {
        if (m_verbose) {std::cout << "h_elfr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (abs(lep_id)==13) 
    {
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinContent(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinContent(eta_bin, pt_bin);
    }
    return 0.0;
}

float PlotLooper::GetFlipRateValue(int lep_id, float pt, float eta) const 
{
    using namespace tas;

    // only applies to electrons
    if (abs(lep_id) != 11)
    {
        return 0.0;
    }

    if (!h_flip)
    {
        if (m_verbose) {std::cout << "h_flip is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinContent(eta_bin, pt_bin);
}
