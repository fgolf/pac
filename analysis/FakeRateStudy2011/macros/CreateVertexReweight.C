#include "rt/RootTools.hpp"

void CreateVertexReweight()
{
    TH1* h_qcd = rt::GetHistFromRootFile<TH1>("plots/qcd/qcd_orig.root", "h_nvtxs");
    TH1* h_ttb = rt::GetHistFromRootFile<TH1>("plots/ttbar/ttbar_orig.root", "h_nvtxs");
	TH1* h_vtx_weight = (TH1*)h_ttb->Clone("hratio");
	h_vtx_weight->Divide(h_qcd);

	TCanvas* c1 = new TCanvas("c1", "c1");
	rt::TH1Overlay* p1 = new rt::TH1Overlay("", "dt::norm");
	p1->Add(h_qcd);
	p1->Add(h_ttb);
	p1->Draw();

	TCanvas* c2 = new TCanvas("c2", "c2");
	h_vtx_weight->Draw();

	TFile f("data/vtxreweight.root", "RECREATE");
	h_vtx_weight->Write();
	f.Close();
}
