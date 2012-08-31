// quick check of the isolation variables for SS
#include "TChain.h"
#include "TH1F.h"
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithHist.h"
#include <stdexcept>
#include "CMS2.h"
#include "ssSelections.h"
#include "electronSelections.h"

using namespace at;
using namespace std;
using namespace rt;
using namespace tas;

class QuickAnalysis : public AnalysisWithHist
{
	public:
		QuickAnalysis(const std::string& file_name); 
		int operator() (long event);
		void BookHists();
};

QuickAnalysis::QuickAnalysis(const std::string& file_name)
: AnalysisWithHist(file_name)
{
	BookHists();
}

void QuickAnalysis::BookHists()
{
	TH1Container& hc = m_hist_container;
	hc.Add(new TH1F("h_iso_fullid_orig"   , "electron iso (full ID, orig);iso"                       , 100, 0, 5));
	hc.Add(new TH1F("h_iso_fullid_fix"    , "electron iso (full ID, after fix);iso"                  , 100, 0, 5));
	hc.Add(new TH1F("h_iso_nomhitcut_orig", "electron iso (# missing hit #geq 1, orig);iso"          , 100, 0, 5));
	hc.Add(new TH1F("h_iso_nomhitcut_fix" , "electron iso (# missing hit #geq 1, after_fix);iso"     , 100, 0, 5));

	hc.Add(new TH1F("h_iso_fullid_diff"   , "electron iso diff (full ID - after fix);iso"            , 100, -0.1, 0.5));
	hc.Add(new TH1F("h_iso_nomhitcut_diff", "electron iso diff (# missing hit #geq 1, after_fix);iso", 100, -0.1, 0.5));
}

// relax the 0 hit cut on the electron ID 
static const cuts_t electronSelection_ssV7_noIso_relaxmhit = //(electronSelection_ssV7_noIso & ~(1ll<<ELENOTCONV_HITPATTERN_0MHITS));
                       electronSelectionFO_SS_baselineV2    |
                       (1ll<<ELEID_WP2012_MEDIUM_NOISO)     |
                       //(0ll<<ELENOTCONV_HITPATTERN_0MHITS)  |
                       (1ll<<ELE_NOT_TRANSITION)            |
                       (1ll<<ELECHARGE_NOTFLIP3AGREE);

bool isGoodLeptonRelaxHitCut(int idx)
{
	// electrons
	if (!pass_electronSelection(idx, electronSelection_ssV7_noIso_relaxmhit, false, false))
		return false;
	if ((cms2.els_fiduciality().at(idx) & (1<<ISEB)) == (1<<ISEB))
		return (cms2.els_hOverE().at(idx) < 0.10);
	else
		return (cms2.els_hOverE().at(idx) < 0.075);
}


int QuickAnalysis::operator() (long event)
{
	TH1Container& hc = m_hist_container;

	try
	{
		// electron loop
		for (size_t idx = 0; idx != els_p4().size(); idx++)
		{
			const LorentzVector& el_p4 = els_p4().at(idx);	

			// pt > 20 && |eta| < 2.4
			if (el_p4.pt() < 20.0 || fabs(el_p4.eta()) > 2.4)
			{
				continue;
			}

            float iso_orig = electronIsoValuePF2012_FastJetEffArea(idx);
            float iso_fix  = electronIsoValuePF2012_FastJetEffArea_v2(idx);

			// if passes ID with no missing hits relaxed
			//if (isGoodLepton1MHitCut(idx) && not samesign::isGoodLepton(11, idx))
			if (isGoodLeptonRelaxHitCut(idx) && els_exp_innerlayers().at(idx) >= 1)
            {
                rt::Fill(hc["h_iso_nomhitcut_orig"], iso_orig);
                rt::Fill(hc["h_iso_nomhitcut_fix" ], iso_fix );
                rt::Fill(hc["h_iso_nomhitcut_diff"], iso_orig - iso_fix);
            }

			// if passes full ID 
			if (samesign::isGoodLepton(11, idx))
            {
                rt::Fill(hc["h_iso_fullid_orig"], iso_orig);
                rt::Fill(hc["h_iso_fullid_fix" ], iso_fix );
                rt::Fill(hc["h_iso_fullid_diff"], iso_orig - iso_fix);
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

int main()
{
	TChain chain("Events");
	//chain.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-13/SingleOrDiLepton/merged_ntuple_1.root");
	//chain.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-13/SingleOrDiLepton/merged_ntuple_2.root");
	//chain.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-13/SingleOrDiLepton/merged_ntuple_3.root");
	chain.Add("~/Data/dy_cms2.root");
	rt::PrintFilesFromTChain(chain);

	//ScanChainCMS2(&chain, ScanChainTestAnalysis, 100);
	ScanChainCMS2(&chain, QuickAnalysis("plots/quick_analysis/iso_plots_v2.root"), 100000);
	return 0;
}
