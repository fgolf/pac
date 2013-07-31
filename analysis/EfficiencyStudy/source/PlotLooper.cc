#include "PlotLooper.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <tr1/array>
#include "mcSelections.h"
#include "ESB.h"
#include "rt/RootTools.h"
#include "rt/is_equal.h"
#include "TRandom.h"
//#include "at/Predicates.h"
//#include "at/VtxReweight.h"
//#include "CTable.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace esb;

// construct:
PlotLooper::PlotLooper
(
    const std::string& root_file_name,
    Sample::value_type sample,
    const std::string& pdf_hist_file_name,
	float iso_cut,
	bool derive_pdf,
    bool verbose
)
    : at::AnalysisWithHist(root_file_name)
    , m_verbose(verbose)
	, m_iso_cut(iso_cut)
	, m_derive_pdf(derive_pdf)
	, m_sample(sample)
    //, h_pdf(rt::GetHistFromRootFile<TH1D>(pdf_hist_file_name, "h_pdf_abs_pfiso_3050"))
{
    // set the fake rate histograms
    std::auto_ptr<TFile> pdf_hist_file(rt::OpenRootFile(pdf_hist_file_name));
	pdf_hist_file->ls();
    cout << "using PDF file : " << pdf_hist_file->GetName() << endl;
    h_pdf.reset(dynamic_cast<TH1F*>(pdf_hist_file->Get("h_pdf_abs_pfiso_3050")));
    h_pdf->SetDirectory(NULL);

    // begin job
    BeginJob();
}

// destroy:
PlotLooper::~PlotLooper()
{
}
		
// methods:
void PlotLooper::BeginJob()
{
	// book the histograms
    BookHists();
}


const std::tr1::array<float, 6> mu_pt_bins = {{5.0, 10.0, 20.0, 30.0, 50.0, 100.0}};

// end job
void PlotLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

	// combined
	if (not m_derive_pdf)
	{
		TH1F* h_eff_vs_pt = new TH1F("h_eff_vs_pt", "muon eff vs p_{T}; muon p_{T} (GeV)", mu_pt_bins.size()-1, mu_pt_bins.data());
		h_eff_vs_pt->SetBinContent(1, hc["h_eff_0510" ]->GetMean()); h_eff_vs_pt->SetBinError(1, hc["h_eff_0510" ]->GetRMS());
		h_eff_vs_pt->SetBinContent(2, hc["h_eff_1020" ]->GetMean()); h_eff_vs_pt->SetBinError(2, hc["h_eff_1020" ]->GetRMS());
		h_eff_vs_pt->SetBinContent(3, hc["h_eff_2030" ]->GetMean()); h_eff_vs_pt->SetBinError(3, hc["h_eff_2030" ]->GetRMS());
		h_eff_vs_pt->SetBinContent(4, hc["h_eff_3050" ]->GetMean()); h_eff_vs_pt->SetBinError(4, hc["h_eff_3050" ]->GetRMS());
		h_eff_vs_pt->SetBinContent(5, hc["h_eff_50100"]->GetMean()); h_eff_vs_pt->SetBinError(5, hc["h_eff_50100"]->GetRMS());
		hc.Add(h_eff_vs_pt);

		hc.Add(rt::MakeEfficiencyPlot(hc["h_num_05100"], hc["h_den_05100"], "h_eff_vs_pt_mctruth"));
		hc.Add(rt::MakeEfficiencyPlot(hc["h_num_05100_tap"], hc["h_den_05100_tap"], "h_eff_vs_pt_tap"));
	}
	else
	{
		rt::Scale(hc["h_pdf_abs_pfiso_3050"    ], 1.0);
		rt::Scale(hc["h_pdf_abs_pfiso_3050_tap"], 1.0);
	}

    hc.SetMarkerStyle(20);
    hc.SetMarkerSize(0.8);

    if (m_verbose)
    {
        hc.List();
    }
}

// book hists 
void PlotLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        // book
		if (m_derive_pdf)
		{
			hc.Add(new TH1F("h_pdf_abs_pfiso_3050"    , "normalized abs pfiso (30 < p_{T} < 50);abs pfiso"    , 500, 0, 10.0));
			hc.Add(new TH1F("h_pdf_abs_pfiso_3050_tap", "normalized abs pfiso tap (30 < p_{T} < 50);abs pfiso", 500, 0, 10.0));
			return;
		}
        hc.Add(new TH1F("h_eff"       , "efficiency using PDF;#epsilon"                            , 100, 0 , 1.00));
        hc.Add(new TH1F("h_eff_0510"  , "efficiency using PDF (5 GeV < p_{T} < 10 GeV);#epsilon"   , 100, 0 , 1.00));
        hc.Add(new TH1F("h_eff_1020"  , "efficiency using PDF (10 GeV < p_{T} < 20 GeV);#epsilon"  , 100, 0 , 1.00));
        hc.Add(new TH1F("h_eff_2030"  , "efficiency using PDF (20 GeV < p_{T} < 40 GeV);#epsilon"  , 100, 0 , 1.00));
        hc.Add(new TH1F("h_eff_3050"  , "efficiency using PDF (40 GeV < p_{T} < 50 GeV);#epsilon"  , 100, 0 , 1.00));
        hc.Add(new TH1F("h_eff_50100" , "efficiency using PDF (50 GeV < p_{T} < 100 GeV);#epsilon" , 100, 0 , 1.00));

        hc.Add(new TH1F("h_dilep_mass"       , "dilepton mass;m_{#mu#mu} (GeV)"                            , 60, 60 , 120));
        hc.Add(new TH1F("h_dilep_mass_0510"  , "dilepton mass (5 GeV < p_{T} < 10 GeV);m_{#mu#mu} (GeV)"   , 60, 60 , 120));
        hc.Add(new TH1F("h_dilep_mass_1020"  , "dilepton mass (10 GeV < p_{T} < 20 GeV);m_{#mu#mu} (GeV)"  , 60, 60 , 120));
        hc.Add(new TH1F("h_dilep_mass_2030"  , "dilepton mass (20 GeV < p_{T} < 40 GeV);m_{#mu#mu} (GeV)"  , 60, 60 , 120));
        hc.Add(new TH1F("h_dilep_mass_3050"  , "dilepton mass (40 GeV < p_{T} < 50 GeV);m_{#mu#mu} (GeV)"  , 60, 60 , 120));
        hc.Add(new TH1F("h_dilep_mass_50100" , "dilepton mass (50 GeV < p_{T} < 100 GeV);m_{#mu#mu} (GeV)" , 60, 60 , 120));

        hc.Add(new TH1F("h_num_05100"     , "numerator;muon p_{T} (GeV)"  , mu_pt_bins.size()-1, mu_pt_bins.data()));
        hc.Add(new TH1F("h_den_05100"     , "denominator;muon p_{T} (GeV)", mu_pt_bins.size()-1, mu_pt_bins.data()));
        hc.Add(new TH1F("h_num_05100_tap" , "numerator (T&P);muon p_{T} (GeV)"  , mu_pt_bins.size()-1, mu_pt_bins.data()));
        hc.Add(new TH1F("h_den_05100_tap" , "denominator (T&P);muon p_{T} (GeV)", mu_pt_bins.size()-1, mu_pt_bins.data()));

        hc.Add(new TH1F("h_abs_pfiso", "absolute pf iso;#pfiso", 100, 0, 10.0));
        hc.Add(new TH1F("h_rel_pfiso", "relative pf iso;#pfiso", 100, 0, 0.20));
        hc.Add(new TH1F("h_abs_pfiso_3035", "absolute pf iso (30 < p^{#mu}_{T} < 35);pfiso", 100, 0, 10.0));
        hc.Add(new TH1F("h_abs_pfiso_3540", "absolute pf iso (35 < p^{#mu}_{T} < 40);pfiso", 100, 0, 10.0));
        hc.Add(new TH1F("h_abs_pfiso_4045", "absolute pf iso (40 < p^{#mu}_{T} < 45);pfiso", 100, 0, 10.0));
        hc.Add(new TH1F("h_abs_pfiso_4550", "absolute pf iso (45 < p^{#mu}_{T} < 50);pfiso", 100, 0, 10.0));

        hc.Add((TH1D*)h_pdf->Clone());

        return;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

// main analysis function operator 
int PlotLooper::operator()(long event)
{
    using namespace std;
    using namespace esb;

    try
	{
		// base analysis
		at::AnalysisWithHist::operator()(event);

		// convenience alias
		rt::TH1Container& hc = m_hist_container;

		// create a random instance
		TRandom random(static_cast<unsigned int>(event));

		// selection
		// --------------------------------------------------------------- //

		const float l1_pt        = lep1_p4().pt();
		const float l2_pt        = lep2_p4().pt();
		const float l1_abs_pfiso = lep1_pfiso()*l1_pt;
		const float l2_abs_pfiso = lep2_pfiso()*l2_pt;
		const float l1_rel_pfiso = lep1_pfiso();
		const float l2_rel_pfiso = lep2_pfiso();

		bool mm = (lep1_pdgid()*lep2_pdgid()==-169);
		if (not mm)
		{
			return 0;	
		}

		bool zwin = (76 < dilep_mass() && dilep_mass() < 106);
		if (not zwin)
		{
			return 0;
		}

		// fill plots
		// --------------------------------------------------------------- //

		// derive pdf
		bool mc_matched = is_real_data() ? true : (lep1_mc3_momid()==23 && lep2_mc3_momid()==23);
		if (m_derive_pdf)
		{
			if (mc_matched and 30 < l1_pt and l1_pt < 50)
			{
				hc["h_pdf_abs_pfiso_3050"]->Fill(l1_abs_pfiso);
			}
			if (mc_matched and 30 < l2_pt and l2_pt < 50)
			{
				hc["h_pdf_abs_pfiso_3050"]->Fill(l2_abs_pfiso);
			} 		

			bool l1_is_tag = (random.Uniform(1.0) < 0.5);
			bool tag_id    = true; 
			float tag_iso  = l1_is_tag ? lep1_pfiso()     : lep2_pfiso();

			float probe_pt  = l1_is_tag ? lep2_p4().pt()   : lep1_p4().pt();
			bool probe_id   = true; 
			float probe_iso = l1_is_tag ? lep2_pfiso()     : lep1_pfiso();

			// test if tag passed ID+iso
			if (tag_id && tag_iso < m_iso_cut)
			{
				// if the tag passes ID --> denomintor
				if (not probe_id)
				{
					return 0;
				}
				hc["h_pdf_abs_pfiso_3050_tap"]->Fill(probe_iso*probe_pt);
			}

			// done with pdf
			return 0;
		}


		// MC truth matching 
		if (mc_matched)
		{
			if (30 < l1_pt and l1_pt < 50)
			{
				hc["h_abs_pfiso"]->Fill(l1_abs_pfiso);
				hc["h_eff"      ]->Fill(GetEffFromPDF(0.1*l1_pt));
			}
			if (30 < l2_pt and l2_pt < 50)
			{
				hc["h_abs_pfiso"]->Fill(l2_abs_pfiso);
				hc["h_eff"      ]->Fill(GetEffFromPDF(0.1*l2_pt));
			} 		

			// lep1
			if (l1_rel_pfiso < m_iso_cut) {hc["h_num_05100"]->Fill(l1_pt);}
			{hc["h_den_05100"]->Fill(l1_pt);}

			if (30 < l1_pt and l1_pt < 35) {rt::Fill(hc["h_abs_pfiso_3035"], l1_abs_pfiso);}
			if (35 < l1_pt and l1_pt < 40) {rt::Fill(hc["h_abs_pfiso_3540"], l1_abs_pfiso);}
			if (40 < l1_pt and l1_pt < 45) {rt::Fill(hc["h_abs_pfiso_4045"], l1_abs_pfiso);}
			if (45 < l1_pt and l1_pt < 50) {rt::Fill(hc["h_abs_pfiso_4550"], l1_abs_pfiso);}

			if ( 5 < l1_pt and l1_pt < 10 ) {rt::Fill(hc["h_eff_0510" ], GetEffFromPDF(m_iso_cut*l1_pt));}
			if (10 < l1_pt and l1_pt < 20 ) {rt::Fill(hc["h_eff_1020" ], GetEffFromPDF(m_iso_cut*l1_pt));}
			if (20 < l1_pt and l1_pt < 30 ) {rt::Fill(hc["h_eff_2030" ], GetEffFromPDF(m_iso_cut*l1_pt));}
			if (30 < l1_pt and l1_pt < 50 ) {rt::Fill(hc["h_eff_3050" ], GetEffFromPDF(m_iso_cut*l1_pt));}
			if (50 < l1_pt and l1_pt < 100) {rt::Fill(hc["h_eff_50100"], GetEffFromPDF(m_iso_cut*l1_pt));}

			// lep2
			if (l2_rel_pfiso < m_iso_cut) {hc["h_num_05100"]->Fill(l2_pt);}
			{hc["h_den_05100"]->Fill(l2_pt);}

			if (30 < l2_pt and l2_pt < 35) {rt::Fill(hc["h_abs_pfiso_3035"], l2_abs_pfiso);}
			if (35 < l2_pt and l2_pt < 40) {rt::Fill(hc["h_abs_pfiso_3540"], l2_abs_pfiso);}
			if (40 < l2_pt and l2_pt < 45) {rt::Fill(hc["h_abs_pfiso_4045"], l2_abs_pfiso);}
			if (45 < l2_pt and l2_pt < 50) {rt::Fill(hc["h_abs_pfiso_4550"], l2_abs_pfiso);}

			if ( 5 < l2_pt and l2_pt < 10 ) {rt::Fill(hc["h_eff_0510" ], GetEffFromPDF(m_iso_cut*l2_pt));}
			if (10 < l2_pt and l2_pt < 20 ) {rt::Fill(hc["h_eff_1020" ], GetEffFromPDF(m_iso_cut*l2_pt));}
			if (20 < l2_pt and l2_pt < 30 ) {rt::Fill(hc["h_eff_2030" ], GetEffFromPDF(m_iso_cut*l2_pt));}
			if (30 < l2_pt and l2_pt < 50 ) {rt::Fill(hc["h_eff_3050" ], GetEffFromPDF(m_iso_cut*l2_pt));}
			if (50 < l2_pt and l2_pt < 100) {rt::Fill(hc["h_eff_50100"], GetEffFromPDF(m_iso_cut*l2_pt));}
		}
		
		// simple tag & probe
		//float tag_pt   = l1_pt;
		//float probe_pt = l2_pt;
		bool l1_is_tag = (random.Uniform(1.0) < 0.5);
		//float tag_pt   = l1_is_tag ? lep1_p4().pt()   : lep2_p4().pt();
		bool tag_id    = l1_is_tag ? lep1_passes_id() : lep2_passes_id();
		float tag_iso  = l1_is_tag ? lep1_pfiso()     : lep2_pfiso();
		//float tag_ciso = l1_is_tag ? lep1_corpfiso()  : lep2_corpfiso();

		float probe_pt   = l1_is_tag ? lep2_p4().pt()   : lep1_p4().pt();
		bool probe_id    = l1_is_tag ? lep2_passes_id() : lep1_passes_id();
		//bool probe_id   = true; 
		float probe_iso  = l1_is_tag ? lep2_pfiso()     : lep1_pfiso();
		//float probe_ciso = l1_is_tag ? lep2_corpfiso()  : lep1_corpfiso();

		// test if tag passed ID+iso
		if (tag_id && tag_iso < m_iso_cut)
		{
			// if the tag passes ID --> denomintor
			if (not probe_id)
			{
				return 0;
			}
			hc["h_den_05100_tap"]->Fill(probe_pt);

			// if the tab passes ID+iso --> numerator
			if (not (probe_id && probe_iso < m_iso_cut))
            {
                if ( 5 < probe_pt and probe_pt < 100) {rt::Fill(hc["h_dilep_mass"      ], dilep_mass());}
                if ( 5 < probe_pt and probe_pt < 10 ) {rt::Fill(hc["h_dilep_mass_0510" ], dilep_mass());}
                if (10 < probe_pt and probe_pt < 20 ) {rt::Fill(hc["h_dilep_mass_1020" ], dilep_mass());}
                if (20 < probe_pt and probe_pt < 30 ) {rt::Fill(hc["h_dilep_mass_2030" ], dilep_mass());}
                if (30 < probe_pt and probe_pt < 50 ) {rt::Fill(hc["h_dilep_mass_3050" ], dilep_mass());}
                if (50 < probe_pt and probe_pt < 100) {rt::Fill(hc["h_dilep_mass_50100"], dilep_mass());}
                return 0;
            }
			hc["h_num_05100_tap"]->Fill(probe_pt);
		}


	}
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 


float PlotLooper::GetEffFromPDF(float x)
{
    return rt::Integral(h_pdf.get(), 0.0, x);
}
