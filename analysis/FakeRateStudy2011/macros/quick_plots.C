{
	if (!gDirectory->FindObject("tree"))
	{
		gROOT->Macro("macros/get_samples.C");
	}
	long num_entries = 1000000;

	// dphi (no away cut)
	TH1F* h_dphi_data = new TH1F("h_dphi_data", "h_dphi_data", 20, 0, 3.5); h_dphi_data.Sumw2();
	TH1F* h_dphi_qcd  = new TH1F("h_dphi_qcd" , "h_dphi_qcd" , 20, 0, 3.5); h_dphi_qcd.Sumw2();
	//c_data->Draw("dphipfcL1Fj1res>>h_dphi_data", trig && btag_no_w, "goff", num_entries);
	//c_qcd->Draw("dphipfcL1Fj1res>>h_dphi_qcd"  , btag_no_w        , "goff", num_entries);
	//rt::TH1Overlay p_dphi("#Delta#Phi(#mu, bjet);#Delta#Phi", "sb::top_left dt::norm");
	//p_dphi.Add(h_dphi_data, "data", kBlack, 2);
	//p_dphi.Add(h_dphi_qcd , "qcd" , kRed  , 2);

	//// dphi (c20)
	//c_data->Draw("dphipfcL1Fj1res>>h_dphi_data", j20 && trig && btag_no_w, "goff", num_entries);
	//c_qcd->Draw("dphipfcL1Fj1res>>h_dphi_qcd"  , j20 && btag_no_w        , "goff", num_entries);
	//rt::TH1Overlay p_dphi_20c("#Delta#Phi(#mu, bjet) (away jet > 20);#Delta#Phi", "sb::top_left dt::norm");
	//p_dphi_20c.Add(h_dphi_data, "data", kBlack, 2);
	//p_dphi_20c.Add(h_dphi_qcd , "qcd" , kRed  , 2);

	// dphi (c40)
	c_data->Draw("dphipfcL1Fj1res>>h_dphi_data", j40 && trig, "goff", num_entries);
	c_qcd->Draw("dphipfcL1Fj1res>>h_dphi_qcd"  , j40        , "goff", num_entries);
	rt::TH1Overlay p_dphi_40c("#Delta#Phi(#mu, away jet) (away jet > 40);#Delta#Phi", "sb::top_left dt::norm");
	p_dphi_40c.Add(h_dphi_data, "data", kBlack, 2);
	p_dphi_40c.Add(h_dphi_qcd , "qcd" , kRed  , 2);

	//// dphi (c60)
	//c_data->Draw("dphipfcL1Fj1res>>h_dphi_data", j60 && trig && btag_no_w, "goff", num_entries);
	//c_qcd->Draw("dphipfcL1Fj1res>>h_dphi_qcd"  , j60 && btag_no_w        , "goff", num_entries);
	//rt::TH1Overlay p_dphi_60c("#Delta#Phi(#mu, bjet) (away jet > 60);#Delta#Phi", "sb::top_left dt::norm");
	//p_dphi_60c.Add(h_dphi_data, "data", kBlack, 2);
	//p_dphi_60c.Add(h_dphi_qcd , "qcd" , kRed  , 2);

	//TCanvas* c1 = new TCanvas("c1", "c1", 1600, 400);
	//c1->Divide(4,1);
	//c1->cd(1); p_dphi.Draw();
	//c1->cd(2); p_dphi_20c.Draw();
	//c1->cd(3); p_dphi_40c.Draw();
	//c1->cd(4); p_dphi_60c.Draw();
	
	//TH1F* h_dpt_data = new TH1F("h_mt_data", "h_mt_data", 50, 0, 100); h_mt_data.Sumw2();
	//TH1F* h_dpt_qcd  = new TH1F("h_mt_qcd" , "h_mt_qcd" , 50, 0, 100); h_mt_qcd.Sumw2();
	//c_data.Draw("pfmt>>h_mt_data", fo40 && trig, "goff", num_entries);
	//c_qcd.Draw ("pfmt>>h_mt_qcd" , fo40        , "goff", num_entries);
	//rt::TH1Overlay p_mt("m_{T} (no btag);m_{T}", "sb::right dt::norm");
	//p_mt.Add(h_mt_data, "data", kBlack, 2);
	//p_mt.Add(h_mt_qcd , "qcd" , kRed  , 2);
	//p_mt.Draw();
}
