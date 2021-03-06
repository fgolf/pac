// quick check of the isolation variables for SS
#include "TChain.h"
#include "TH1F.h"
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithHist.h"
#include "at/Predicates.h"
#include "at/Status3EventIdentifier.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include <stdexcept>
#include "CMS2Wrapper.h"
#include "ssSelections.h"
#include "electronSelections.h"

// BOOST
#include <boost/program_options.hpp>

using namespace at;
using namespace std;
using namespace rt;
using namespace tas;

class LeptonEff : public AnalysisWithHist
{
	public:
		LeptonEff(const std::string& file_name, const bool verbose); 
		int operator() (long event);
		void BookHists();
		virtual void EndJob();
    private:
        const bool m_verbose;
};

LeptonEff::LeptonEff(const std::string& file_name, const bool verbose)
	: AnalysisWithHist(file_name, true, "png")
    , m_verbose(verbose)
{
	BookHists();
}

void LeptonEff::EndJob()
{
	TH1Container& hc = m_hist_container;

    // make some efficiency plots

    // electrons
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_reco_el"    ], hc["h_mc_el"], "h_eff_el"    , "electron efficiency;|#eta|;p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_reco_el_id" ], hc["h_mc_el"], "h_eff_el_id" , "electron ID efficiency;|#eta|;p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_reco_el_iso"], hc["h_mc_el"], "h_eff_el_iso", "electron ISO efficiency;|#eta|;p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_vs_pt"    ], hc["h_mc_el_vs_pt"], "h_eff_el_vs_pt"    , "electron efficiency;p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_id_vs_pt" ], hc["h_mc_el_vs_pt"], "h_eff_el_id_vs_pt" , "electron ID efficiency;p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_iso_vs_pt"], hc["h_mc_el_vs_pt"], "h_eff_el_iso_vs_pt", "electron ISO efficiency;p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_vs_pt_barrel"    ], hc["h_mc_el_vs_pt_barrel"], "h_eff_el_vs_pt_barrel"    , "electron efficiency (|#eta| < 1.4);p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_id_vs_pt_barrel" ], hc["h_mc_el_vs_pt_barrel"], "h_eff_el_id_vs_pt_barrel" , "electron ID efficiency (|#eta| < 1.4);p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_iso_vs_pt_barrel"], hc["h_mc_el_vs_pt_barrel"], "h_eff_el_iso_vs_pt_barrel", "electron ISO efficiency (|#eta| < 1.4);p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_vs_pt_endcap"    ], hc["h_mc_el_vs_pt_endcap"], "h_eff_el_vs_pt_endcap"    , "electron efficiency (|#eta| > 1.6);p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_id_vs_pt_endcap" ], hc["h_mc_el_vs_pt_endcap"], "h_eff_el_id_vs_pt_endcap" , "electron ID efficiency (|#eta| > 1.6);p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_iso_vs_pt_endcap"], hc["h_mc_el_vs_pt_endcap"], "h_eff_el_iso_vs_pt_endcap", "electron ISO efficiency (|#eta| > 1.6);p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_vs_eta"    ], hc["h_mc_el_vs_eta"], "h_eff_el_vs_eta"    , "electron efficiency;|#eta|"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_id_vs_eta" ], hc["h_mc_el_vs_eta"], "h_eff_el_id_vs_eta" , "electron ID efficiency;|#eta|" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_el_iso_vs_eta"], hc["h_mc_el_vs_eta"], "h_eff_el_iso_vs_eta", "electron ISO efficiency;|#eta|"));

    // muons
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_reco_mu"    ], hc["h_mc_mu"], "h_eff_mu"    , "#mu efficiency;|#eta|;p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_reco_mu_id" ], hc["h_mc_mu"], "h_eff_mu_id" , "#mu ID efficiency;|#eta|;p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_reco_mu_iso"], hc["h_mc_mu"], "h_eff_mu_iso", "#mu ISO efficiency;|#eta|;p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_vs_pt"    ], hc["h_mc_mu_vs_pt"], "h_eff_mu_vs_pt"    , "#mu efficiency;p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_id_vs_pt" ], hc["h_mc_mu_vs_pt"], "h_eff_mu_id_vs_pt" , "#mu ID efficiency;p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_iso_vs_pt"], hc["h_mc_mu_vs_pt"], "h_eff_mu_iso_vs_pt", "#mu ISO efficiency;p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_vs_pt_barrel"    ], hc["h_mc_mu_vs_pt_barrel"], "h_eff_mu_vs_pt_barrel"    , "#mu efficiency (|#eta| < 1.2);p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_id_vs_pt_barrel" ], hc["h_mc_mu_vs_pt_barrel"], "h_eff_mu_id_vs_pt_barrel" , "#mu ID efficiency (|#eta| < 1.2);p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_iso_vs_pt_barrel"], hc["h_mc_mu_vs_pt_barrel"], "h_eff_mu_iso_vs_pt_barrel", "#mu ISO efficiency (|#eta| < 1.2);p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_vs_pt_endcap"    ], hc["h_mc_mu_vs_pt_endcap"], "h_eff_mu_vs_pt_endcap"    , "#mu efficiency (|#eta| > 1.2);p_{T} (GeV)"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_id_vs_pt_endcap" ], hc["h_mc_mu_vs_pt_endcap"], "h_eff_mu_id_vs_pt_endcap" , "#mu ID efficiency (|#eta| > 1.2);p_{T} (GeV)" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_iso_vs_pt_endcap"], hc["h_mc_mu_vs_pt_endcap"], "h_eff_mu_iso_vs_pt_endcap", "#mu ISO efficiency (|#eta| > 1.2);p_{T} (GeV)"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_vs_eta"    ], hc["h_mc_mu_vs_eta"], "h_eff_mu_vs_eta"    , "#mu efficiency;|#eta|"    ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_id_vs_eta" ], hc["h_mc_mu_vs_eta"], "h_eff_mu_id_vs_eta" , "#mu ID efficiency;|#eta|" ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_reco_mu_iso_vs_eta"], hc["h_mc_mu_vs_eta"], "h_eff_mu_iso_vs_eta", "#mu ISO efficiency;|#eta|"));
}

const size_t el_npt_bins  = 7; const float el_pt_bins [] = {10, 20, 30, 40, 50, 70, 100, 200};
//const size_t el_neta_bins = 3; const float el_eta_bins[] = {0, 1.4442, 1.566, 2.5};
const size_t el_neta_bins = 3; const float el_eta_bins[] = {0, 1.4, 1.6, 2.5};

const size_t mu_npt_bins  = 7; const float mu_pt_bins [] = {10, 20, 30, 40, 50, 70, 100, 200};
const size_t mu_neta_bins = 2; const float mu_eta_bins[] = {0, 1.2, 2.5};

void LeptonEff::BookHists()
{
	TH1Container& hc = m_hist_container;

    // electrons
	hc.Add(new TH2F("h_mc_el"      , "MC electron;|#eta|;p_{T} (GeV)"         , el_neta_bins, el_eta_bins, el_npt_bins, el_pt_bins));
	hc.Add(new TH2F("h_reco_el"    , "matched electron;|#eta|;p_{T} (GeV)"    , el_neta_bins, el_eta_bins, el_npt_bins, el_pt_bins));
	hc.Add(new TH2F("h_reco_el_iso", "matched electron iso;|#eta|;p_{T} (GeV)", el_neta_bins, el_eta_bins, el_npt_bins, el_pt_bins));
	hc.Add(new TH2F("h_reco_el_id" , "matched electron id;|#eta|;p_{T} (GeV)" , el_neta_bins, el_eta_bins, el_npt_bins, el_pt_bins));

    hc.Add(new TH1F("h_mc_el_vs_pt"             , "electron MC;p_{T} (GeV)"                       , el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_vs_pt"           , "matched electron MC;p_{T} (GeV)"               , el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_iso_vs_pt"       , "matched electron MC;p_{T} (GeV)"               , el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_id_vs_pt"        , "matched electron MC;p_{T} (GeV)"               , el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_mc_el_vs_pt_barrel"      , "electron MC (|#eta| < 1.4);p_{T} (GeV)"        , el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_vs_pt_barrel"    , "matched electron MC (|#eta| < 1.4);p_{T} (GeV)", el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_iso_vs_pt_barrel", "matched electron MC (|#eta| < 1.4);p_{T} (GeV)", el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_id_vs_pt_barrel" , "matched electron MC (|#eta| < 1.4);p_{T} (GeV)", el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_mc_el_vs_pt_endcap"      , "electron MC (|#eta| > 1.6);p_{T} (GeV)"        , el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_vs_pt_endcap"    , "matched electron MC (|#eta| > 1.6);p_{T} (GeV)", el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_iso_vs_pt_endcap", "matched electron MC (|#eta| > 1.6);p_{T} (GeV)", el_npt_bins , el_pt_bins));
    hc.Add(new TH1F("h_reco_el_id_vs_pt_endcap" , "matched electron MC (|#eta| > 1.6);p_{T} (GeV)", el_npt_bins , el_pt_bins));

    hc.Add(new TH1F("h_mc_el_vs_eta"      , "electron MC;|#eta|"        , el_neta_bins, el_eta_bins));
    hc.Add(new TH1F("h_reco_el_vs_eta"    , "matched electron MC;|#eta|", el_neta_bins, el_eta_bins));
    hc.Add(new TH1F("h_reco_el_id_vs_eta" , "matched electron MC;|#eta|", el_neta_bins, el_eta_bins));
    hc.Add(new TH1F("h_reco_el_iso_vs_eta", "matched electron MC;|#eta|", el_neta_bins, el_eta_bins));

    // muons
	hc.Add(new TH2F("h_mc_mu"      , "MC #mu;|#eta|;p_{T} (GeV)"         , mu_neta_bins, mu_eta_bins, mu_npt_bins, mu_pt_bins));
	hc.Add(new TH2F("h_reco_mu"    , "matched #mu;|#eta|;p_{T} (GeV)"    , mu_neta_bins, mu_eta_bins, mu_npt_bins, mu_pt_bins));
	hc.Add(new TH2F("h_reco_mu_iso", "matched #mu iso;|#eta|;p_{T} (GeV)", mu_neta_bins, mu_eta_bins, mu_npt_bins, mu_pt_bins));
	hc.Add(new TH2F("h_reco_mu_id" , "matched #mu id;|#eta|;p_{T} (GeV)" , mu_neta_bins, mu_eta_bins, mu_npt_bins, mu_pt_bins));

    hc.Add(new TH1F("h_mc_mu_vs_pt"             , "#mu MC;p_{T} (GeV)"                       , mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_vs_pt"           , "matched #mu MC;p_{T} (GeV)"               , mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_iso_vs_pt"       , "matched #mu MC;p_{T} (GeV)"               , mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_id_vs_pt"        , "matched #mu MC;p_{T} (GeV)"               , mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_vs_pt_barrel"    , "matched #mu MC (|#eta| < 1.2);p_{T} (GeV)", mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_mc_mu_vs_pt_barrel"      , "#mu MC (|#eta| < 1.2);p_{T} (GeV)"        , mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_iso_vs_pt_barrel", "matched #mu MC (|#eta| < 1.2);p_{T} (GeV)", mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_id_vs_pt_barrel" , "matched #mu MC (|#eta| < 1.2);p_{T} (GeV)", mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_vs_pt_endcap"    , "matched #mu MC (|#eta| > 1.2);p_{T} (GeV)", mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_mc_mu_vs_pt_endcap"      , "#mu MC (|#eta| > 1.2);p_{T} (GeV)"        , mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_iso_vs_pt_endcap", "matched #mu MC (|#eta| > 1.2);p_{T} (GeV)", mu_npt_bins , mu_pt_bins));
    hc.Add(new TH1F("h_reco_mu_id_vs_pt_endcap" , "matched #mu MC (|#eta| > 1.2);p_{T} (GeV)", mu_npt_bins , mu_pt_bins));

    hc.Add(new TH1F("h_mc_mu_vs_eta"      , "#mu MC;|#eta|"        , mu_neta_bins, mu_eta_bins));
    hc.Add(new TH1F("h_reco_mu_vs_eta"    , "matched #mu MC;|#eta|", mu_neta_bins, mu_eta_bins));
    hc.Add(new TH1F("h_reco_mu_id_vs_eta" , "matched #mu MC;|#eta|", mu_neta_bins, mu_eta_bins));
    hc.Add(new TH1F("h_reco_mu_iso_vs_eta", "matched #mu MC;|#eta|", mu_neta_bins, mu_eta_bins));
}


int LeptonEff::operator() (long event)
{
	rt::TH1Container& hc = m_hist_container;

	try
	{

        std::pair<GenParticleStruct, GenParticleStruct> gen_hyp = efftools::getGenHyp(10.0, 10.0, at::DileptonChargeType::OS);
        if (gen_hyp.first.id_ == 0 || gen_hyp.second.id_ == 0)
        {
            if (m_verbose) {cout << "[ss2012_lepton_eff]: does not have a good gen hyp" << endl;} 
            return 0;
        }

        // sort by pt
        const GenParticleStruct& l1 = std::max(gen_hyp.first, gen_hyp.second, GenParticleStruct::SortByPt);
        const GenParticleStruct& l2 = std::min(gen_hyp.first, gen_hyp.second, GenParticleStruct::SortByPt);

        // lepton variables
        const bool l1_is_el  = (abs(l1.id_)==11);
        const bool l2_is_el  = (abs(l2.id_)==11);
        const bool l1_is_mu  = (abs(l1.id_)==13);
        const bool l2_is_mu  = (abs(l2.id_)==13);
        const bool l1_is_tau = (abs(l1.id_)==15);
        const bool l2_is_tau = (abs(l2.id_)==15);

        // get gen LorenzVectors
        const LorentzVector l1_p4 = (l1_is_tau  ? genps_lepdaughter_p4().at(l1.idx_).at(l1.didx_) : genps_p4().at(l1.idx_));
        const LorentzVector l2_p4 = (l2_is_tau  ? genps_lepdaughter_p4().at(l2.idx_).at(l2.didx_) : genps_p4().at(l2.idx_));
        const float l1_pt  = min(l1_p4.pt(), (l1_is_el ? el_pt_bins[el_npt_bins] : mu_pt_bins[mu_npt_bins]));
        const float l2_pt  = min(l2_p4.pt(), (l2_is_el ? el_pt_bins[el_npt_bins] : mu_pt_bins[mu_npt_bins]));
        const float l1_eta = fabs(l1_p4.eta());
        const float l2_eta = fabs(l2_p4.eta());
        const bool l1_is_crack = (1.4 < l1_eta && l1_eta < 1.6);
        const bool l2_is_crack = (1.4 < l2_eta && l2_eta < 1.6);
        const bool l1_is_barrel = (l1_eta < (l1_is_el ? 1.4 : 1.2));
        const bool l2_is_barrel = (l2_eta < (l2_is_el ? 1.4 : 1.2));
        const bool l1_is_endcap = (l1_eta > (l1_is_el ? 1.6 : 1.2));
        const bool l2_is_endcap = (l2_eta > (l2_is_el ? 1.6 : 1.2));

        if (l1_is_el && not l1_is_crack)
        {
            hc["h_mc_el"       ]->Fill(l1_eta, l1_pt);
            hc["h_mc_el_vs_pt" ]->Fill(l1_pt );
            hc["h_mc_el_vs_eta"]->Fill(l1_eta);
            if (l1_is_barrel) {hc["h_mc_el_vs_pt_barrel" ]->Fill(l1_pt);}
            if (l1_is_endcap) {hc["h_mc_el_vs_pt_endcap" ]->Fill(l1_pt);}
        }
        if (l2_is_el && not l2_is_crack)
        {
            hc["h_mc_el"       ]->Fill(l2_eta, l2_pt);
            hc["h_mc_el_vs_pt" ]->Fill(l2_pt );
            hc["h_mc_el_vs_eta"]->Fill(l2_eta);
            if (l2_is_barrel) {hc["h_mc_el_vs_pt_barrel" ]->Fill(l2_pt);}
            if (l2_is_endcap) {hc["h_mc_el_vs_pt_endcap" ]->Fill(l2_pt);}
        }
        if (l1_is_mu)
        {
            hc["h_mc_mu"       ]->Fill(l1_eta, l1_pt);
            hc["h_mc_mu_vs_pt" ]->Fill(l1_pt );
            hc["h_mc_mu_vs_eta"]->Fill(l1_eta);
            if (l1_is_barrel) {hc["h_mc_mu_vs_pt_barrel" ]->Fill(l1_pt);}
            if (l1_is_endcap) {hc["h_mc_mu_vs_pt_endcap" ]->Fill(l1_pt);}
        }
        if (l2_is_mu)
        {
            hc["h_mc_mu"       ]->Fill(l2_eta, l2_pt);
            hc["h_mc_mu_vs_pt" ]->Fill(l2_pt );
            hc["h_mc_mu_vs_eta"]->Fill(l2_eta);
            if (l2_is_barrel) {hc["h_mc_mu_vs_pt_barrel" ]->Fill(l2_pt);}
            if (l2_is_endcap) {hc["h_mc_mu_vs_pt_endcap" ]->Fill(l2_pt);}
        }
    
        // determine if matched to gen
        const std::pair<LorentzVector, int> reco_lep1 = efftools::getRecoLepton(l1);
        bool l1_reco_matched    = false;
        bool l1_reco_num        = false;
        bool l1_reco_passes_id  = false;
        bool l1_reco_passes_iso = false;
        LorentzVector l1_reco_p4;
        if (reco_lep1.second > -1 && reco_lep1.first.pt() > 10.0 && abs(reco_lep1.first.eta())<2.4) 
        {
            l1_reco_matched    = true; 
            l1_reco_p4         = reco_lep1.first;
            l1_reco_num        = samesign::isNumeratorLepton(l1.id_, reco_lep1.second);
            l1_reco_passes_id  = samesign::isGoodLepton(l1.id_, reco_lep1.second);
            l1_reco_passes_iso = samesign::isIsolatedLepton(l1.id_, reco_lep1.second);
            //l1_reco_iso        = samesign::leptonIsolation(l1.id_, reco_lep1.second);
        }

        const std::pair<LorentzVector, int> reco_lep2 = efftools::getRecoLepton(l2);
        bool l2_reco_matched    = false;
        bool l2_reco_num        = false;
        bool l2_reco_passes_id  = false;
        bool l2_reco_passes_iso = false;
        LorentzVector l2_reco_p4;
        if (reco_lep2.second > -1 && reco_lep2.first.pt() > 10.0 && abs(reco_lep2.first.eta())<2.4) 
        {
            l2_reco_matched    = true; 
            l2_reco_p4         = reco_lep2.first;
            l2_reco_num        = samesign::isNumeratorLepton(l2.id_, reco_lep2.second);
            l2_reco_passes_id  = samesign::isGoodLepton(l2.id_, reco_lep2.second);
            l2_reco_passes_iso = samesign::isIsolatedLepton(l2.id_, reco_lep2.second);
            //l2_reco_iso        = samesign::leptonIsolation(l2.id_, reco_lep2.second);
        }

//         const float l1_reco_pt  = min(l1_reco_p4.pt(), (l1_is_el ? el_pt_bins[el_npt_bins] : mu_pt_bins[mu_npt_bins]));
//         const float l2_reco_pt  = min(l2_reco_p4.pt(), (l2_is_el ? el_pt_bins[el_npt_bins] : mu_pt_bins[mu_npt_bins]));
//         const float l1_reco_eta = fabs(l1_reco_p4.eta());
//         const float l2_reco_eta = fabs(l2_reco_p4.eta());

        // reco electrons
        if (l1_is_el && l1_reco_matched && not l1_is_crack)
        {
            if (l1_reco_num)
            {
                hc["h_reco_el"       ]->Fill(l1_eta, l1_pt);
                hc["h_reco_el_vs_pt" ]->Fill(l1_pt );
                hc["h_reco_el_vs_eta"]->Fill(l1_eta);
                if (l1_is_barrel) {hc["h_reco_el_vs_pt_barrel" ]->Fill(l1_pt);}
                if (l1_is_endcap) {hc["h_reco_el_vs_pt_endcap" ]->Fill(l1_pt);}
            }
            if (l1_reco_passes_id)
            {
                hc["h_reco_el_id"       ]->Fill(l1_eta, l1_pt);
                hc["h_reco_el_id_vs_pt" ]->Fill(l1_pt );
                hc["h_reco_el_id_vs_eta"]->Fill(l1_eta);
                if (l1_is_barrel) {hc["h_reco_el_id_vs_pt_barrel" ]->Fill(l1_pt);}
                if (l1_is_endcap) {hc["h_reco_el_id_vs_pt_endcap" ]->Fill(l1_pt);}
            }
            if (l1_reco_passes_iso)
            {
                hc["h_reco_el_iso"       ]->Fill(l1_eta, l1_pt);
                hc["h_reco_el_iso_vs_pt" ]->Fill(l1_pt );
                hc["h_reco_el_iso_vs_eta"]->Fill(l1_eta);
                if (l1_is_barrel) {hc["h_reco_el_iso_vs_pt_barrel" ]->Fill(l1_pt);}
                if (l1_is_endcap) {hc["h_reco_el_iso_vs_pt_endcap" ]->Fill(l1_pt);}
            }
        }
        if (l2_is_el && l2_reco_matched && not l2_is_crack)
        {
            if (l2_reco_num)
            {
                hc["h_reco_el"       ]->Fill(l2_eta, l2_pt);
                hc["h_reco_el_vs_pt" ]->Fill(l2_pt );
                hc["h_reco_el_vs_eta"]->Fill(l2_eta);
                if (l2_is_barrel) {hc["h_reco_el_vs_pt_barrel" ]->Fill(l2_pt);}
                if (l2_is_endcap) {hc["h_reco_el_vs_pt_endcap" ]->Fill(l2_pt);}
            }
            if (l2_reco_passes_id)
            {
                hc["h_reco_el_id"       ]->Fill(l2_eta, l2_pt);
                hc["h_reco_el_id_vs_pt" ]->Fill(l2_pt );
                hc["h_reco_el_id_vs_eta"]->Fill(l2_eta);
                if (l2_is_barrel) {hc["h_reco_el_id_vs_pt_barrel" ]->Fill(l2_pt);}
                if (l2_is_endcap) {hc["h_reco_el_id_vs_pt_endcap" ]->Fill(l2_pt);}
            }
            if (l2_reco_passes_iso)
            {
                hc["h_reco_el_iso"       ]->Fill(l2_eta, l2_pt);
                hc["h_reco_el_iso_vs_pt" ]->Fill(l2_pt );
                hc["h_reco_el_iso_vs_eta"]->Fill(l2_eta);
                if (l2_is_barrel) {hc["h_reco_el_iso_vs_pt_barrel" ]->Fill(l2_pt);}
                if (l2_is_endcap) {hc["h_reco_el_iso_vs_pt_endcap" ]->Fill(l2_pt);}
            }
        }

        // reco muons
        if (l1_is_mu && l1_reco_matched)
        {
            if (l1_reco_num)
            {
                hc["h_reco_mu"       ]->Fill(l1_eta, l1_pt);
                hc["h_reco_mu_vs_pt" ]->Fill(l1_pt );
                hc["h_reco_mu_vs_eta"]->Fill(l1_eta);
                if (l1_is_barrel) {hc["h_reco_mu_vs_pt_barrel" ]->Fill(l1_pt);}
                if (l1_is_endcap) {hc["h_reco_mu_vs_pt_endcap" ]->Fill(l1_pt);}
            }
            if (l1_reco_passes_id)
            {
                hc["h_reco_mu_id"       ]->Fill(l1_eta, l1_pt);
                hc["h_reco_mu_id_vs_pt" ]->Fill(l1_pt );
                hc["h_reco_mu_id_vs_eta"]->Fill(l1_eta);
                if (l1_is_barrel) {hc["h_reco_mu_id_vs_pt_barrel" ]->Fill(l1_pt);}
                if (l1_is_endcap) {hc["h_reco_mu_id_vs_pt_endcap" ]->Fill(l1_pt);}
            }
            if (l1_reco_passes_iso)
            {
                hc["h_reco_mu_iso"       ]->Fill(l1_eta, l1_pt);
                hc["h_reco_mu_iso_vs_pt" ]->Fill(l1_pt );
                hc["h_reco_mu_iso_vs_eta"]->Fill(l1_eta);
                if (l1_is_barrel) {hc["h_reco_mu_iso_vs_pt_barrel" ]->Fill(l1_pt);}
                if (l1_is_endcap) {hc["h_reco_mu_iso_vs_pt_endcap" ]->Fill(l1_pt);}
            }
        }
        if (l2_is_mu && l2_reco_matched)
        {
            if (l2_reco_num)
            {
                hc["h_reco_mu"       ]->Fill(l2_eta, l2_pt);
                hc["h_reco_mu_vs_pt" ]->Fill(l2_pt );
                hc["h_reco_mu_vs_eta"]->Fill(l2_eta);
                if (l2_is_barrel) {hc["h_reco_mu_vs_pt_barrel" ]->Fill(l2_pt);}
                if (l2_is_endcap) {hc["h_reco_mu_vs_pt_endcap" ]->Fill(l2_pt);}
            }
            if (l2_reco_passes_id)
            {
                hc["h_reco_mu_id"       ]->Fill(l2_eta, l2_pt);
                hc["h_reco_mu_id_vs_pt" ]->Fill(l2_pt );
                hc["h_reco_mu_id_vs_eta"]->Fill(l2_eta);
                if (l2_is_barrel) {hc["h_reco_mu_id_vs_pt_barrel" ]->Fill(l2_pt);}
                if (l2_is_endcap) {hc["h_reco_mu_id_vs_pt_endcap" ]->Fill(l2_pt);}
            }
            if (l2_reco_passes_iso)
            {
                hc["h_reco_mu_iso"       ]->Fill(l2_eta, l2_pt);
                hc["h_reco_mu_iso_vs_pt" ]->Fill(l2_pt );
                hc["h_reco_mu_iso_vs_eta"]->Fill(l2_eta);
                if (l2_is_barrel) {hc["h_reco_mu_iso_vs_pt_barrel" ]->Fill(l2_pt);}
                if (l2_is_endcap) {hc["h_reco_mu_iso_vs_pt_endcap" ]->Fill(l2_pt);}
            }
        }
        
	}
    catch (std::exception& e)
    {
        cout << Form("Fatal error on run %d, ls %d, event %d", evt_run(), evt_lumiBlock(), evt_event()) << endl;
        cout << e.what() << endl;
        cout << "Exiting..." << endl;
        exit(1);
    }

    // done
    return 0;
}

int main(int argc, char* argv[])
try
{
    std::string output_file = "";
    std::string input_file  = "";
    std::string sample_name = "";
    int number_of_events    = -1;
    bool verbose            = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"  , "print this menu")
        ("sample", po::value<std::string>(&sample_name)->required(), "REQUIRED: input ntuple (default is determined by the sample used)" )
        ("output", po::value<std::string>(&output_file)            , "output ROOT file for baby tree (default: plots/<sample name>.root)")
        ("input" , po::value<std::string>(&input_file)             , "input ntuple (default is determined by the sample used)"           )
        ("nev"   , po::value<int>(&number_of_events)               , "number of events to run on (-1 == all)"                            )
        ;

    // parse it
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) 
        {
            cout << desc << "\n";
            return 1;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        cout << desc << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << "\n";
        return false;
    }

    cout << "inputs:" << endl;
    cout << "number_of_events   :\t" << number_of_events    << endl;
    cout << "sample_name        :\t" << sample_name         << endl;
    cout << "input_file         :\t" << input_file          << endl;
    cout << "output_file        :\t" << output_file         << endl;

    // do it
    // -------------------------------------------------------------------- //

    // input
    TChain* chain  = NULL;
    at::Sample::value_type sample = at::Sample::static_size; 
	if (not sample_name.empty())
	{
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
	}
	else
	{
        cout << "no sample name given." << endl;
	}
    if (input_file.empty())
    {
        if (output_file.empty())
        {
            output_file = Form("plots/mceff/%s/plots.root", sample_name.c_str());
        }
        chain = at::GetSampleTChain(sample, at::NtupleType::cms2);
    }
    else
    {
        if (output_file.empty())
        {
            output_file = "plots/mceff/test/plots.root";
        }
        chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
    }

    cout << "sample has " << chain->GetEntries() << " entries" << endl;
    cout << "sample has " << chain->GetListOfFiles()->GetEntries() << " files" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

	ScanChain(chain, LeptonEff(output_file, verbose), cms2, number_of_events, /*run_list=*/"", true, false);

    // cleanup
    delete chain;

	return 0;
}
catch (std::exception& e)
{
    cerr << "[ss2012_lepton_eff] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

