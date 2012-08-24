{
    //rt::TH1Container hc_qcd("plots/FakeRateMaker/qcd/fakerate.root");
    //rt::TH1Container hc_ttb("plots/FakeRateMaker/ttbar/fakerate.root");

    //rt::TH1Overlay p1("FO's matched heavy flavor parton's p_{T};hf parton p_{T}", "dt::norm");
    //p1.Add(hc_ttb["h_fo_mc3_hf_pt"], "t#bar{t}", kBlue, 2);
    //p1.Add(hc_qcd["h_fo_mc3_hf_pt"], "QCD"     , kRed , 2);
    //p1.Draw();
    /////c1->Print("plots/FakeRateMaker/04042012/h_fo_mc3_b_pt.eps");
    //c1->Print("plots/FakeRateMaker/04042012/h_fo_mc3_hf_pt.eps");
    ////c1->Print("plots/FakeRateMaker/04042012/h_fo_mc3_pt.eps");

    rt::TH1Container hc_qcd("plots/FakeRateMaker/qcd/fakerate_vtx3_8_directb.root");
    rt::TH1Container hc_ttb("plots/FakeRateMaker/ttbar/fakerate_vtx3_8_directb.root");

    for (int i = 3; i < 8; i++)
    {
        int min = 10*i;
        int max = 10*(i+1);
        std::string p1_title = Form("FO's p_{T} (%d < p_{T}^{b} < %d);p_{T}", min, max);
        std::string p1_name  = Form("p_fo_pt_mc3bin%d_%d.eps", min, max);

        rt::TH1Overlay p1(p1_title, "dt::norm");
        p1.Add(hc_ttb[Form("h_fo_matched_pt_mc3bin%d_%d", min, max)], "t#bar{t}", kBlue, 2);
        p1.Add(hc_qcd[Form("h_fo_matched_pt_mc3bin%d_%d", min, max)], "QCD"     , kRed , 2);
        p1.Draw();
        c1->Print(("plots/FakeRateMaker/04042012/"+p1_name).c_str());

        std::string p2_title = Form("FO's #eta (%d < p_{T}^{b} < %d);|#eta|", min, max);
        std::string p2_name  = Form("p_fo_eta_mc3bin%d_%d.eps", min, max);
        rt::TH1Overlay p2(p2_title, "dt::norm sb::off lg::bottom");
        p2.Add(hc_ttb[Form("h_fo_matched_eta_mc3bin%d_%d", min, max)], "t#bar{t}", kBlue, 2);
        p2.Add(hc_qcd[Form("h_fo_matched_eta_mc3bin%d_%d", min, max)], "QCD"     , kRed , 2);
        p2.Draw();
        c1->Print(("plots/FakeRateMaker/04042012/"+p2_name).c_str());
    }

    //c1->Print("plots/FakeRateMaker/04042012/p_fo_pt_mc3bin40_42.eps");
    //rt::TH1Overlay p1("FO's p_{T} (40 < p_{T}^{b} < 42);p_{T}", "dt::norm");
    //p1.Add(hc_ttb["h_fo_matched_pt_mc3bin40_42"], "t#bar{t}", kBlue, 2);
    //p1.Add(hc_qcd["h_fo_matched_pt_mc3bin40_42"], "QCD"     , kRed , 2);
    //p1.Draw();
    //c1->Print("plots/FakeRateMaker/04042012/p_fo_pt_mc3bin40_42.eps");

    //rt::TH1Overlay p1("FO's p_{T} (60 < p_{T}^{b} < 62);p_{T}", "dt::norm");
    //p1.Add(hc_ttb["h_fo_matched_pt_mc3bin60_62"], "t#bar{t}", kBlue, 2);
    //p1.Add(hc_qcd["h_fo_matched_pt_mc3bin60_62"], "QCD"     , kRed , 2);
    //p1.Draw();
    //c1->Print("plots/FakeRateMaker/04042012/p_fo_pt_mc3bin60_62.eps");

    //rt::TH1Overlay p1("FO's #eta (40 < p_{T}^{b} < 42);#eta", "dt::norm sb::off lg::bottom");
    //p1.Add(hc_ttb["h_fo_matched_eta_mc3bin40_42"], "t#bar{t}", kBlue, 2);
    //p1.Add(hc_qcd["h_fo_matched_eta_mc3bin40_42"], "QCD"     , kRed , 2);
    //p1.Draw();
    //c1->Print("plots/FakeRateMaker/04042012/p_fo_eta_mc3bin40_42.eps");

    //rt::TH1Overlay p1("FO's #eta (60 < p_{T}^{b} < 62);#eta", "dt::norm sb::off lg::bottom");
    //p1.Add(hc_ttb["h_fo_matched_eta_mc3bin60_62"], "t#bar{t}", kBlue, 2);
    //p1.Add(hc_qcd["h_fo_matched_eta_mc3bin60_62"], "QCD"     , kRed , 2);
    //p1.Draw();
    //c1->Print("plots/FakeRateMaker/04042012/p_fo_eta_mc3bin60_62.eps");

    //gROOT->ProcessLine(".x macros/quick_setup.C");

    //// ttbar derived FR
    //TH1F fo_pt1("fo_pt1", "t#bar{t} derived", 100, 0, 200); fo_pt1.Sumw2();
    //TH1F fo_pt2("fo_pt2", "qcd derived"     , 100, 0, 200); fo_pt2.Sumw2();
    //e3.Draw("fo_pt>>fo_pt1", cut_mm_pred);
    //e4.Draw("fo_pt>>fo_pt2", cut_mm_pred);
    //cout << rt::pm(rt::IntegralAndError(&fo_pt1, 1, 1000)) << endl;
    //cout << rt::pm(rt::IntegralAndError(&fo_pt2, 1, 1000)) << endl;
    //rt::TH1Overlay p0("FO p_{T} with FR(p_{T}, #eta) applied;FO p_{T}");
    //p0.Add(&fo_pt1);
    //p0.Add(&fo_pt2);
    //p0.Draw();
    //c1->Print("plots/FakeRateMaker/h_fo_pt.png");
    
    //TH1* fo_eta1 = new TH1F("fo_eta1", "mc3 matched"     , 40, -2.5, 2.5); fo_eta1.Sumw2();
    //TH1* fo_eta2 = new TH1F("fo_eta2", "mc3 p_{T} binned", 40, -2.5, 2.5); fo_eta2.Sumw2();
    //e1.Draw("fo_eta>>fo_eta1", cut_mm_pred);
    //e2.Draw("fo_eta>>fo_eta2", cut_mm_pred);
    //rt::TH1Overlay p1("FO's #eta;#eta");
    //p1.Add(fo_eta1);
    //p1.Add(fo_eta2);
    //p1.Draw();
    //c1->Print("plots/FakeRateMaker/h_fo_eta_compare.png");

    //TH1* fo_fr1 = new TH1F("fo_fr1", "mc3 matched"     , 100, 0, 0.3);
    //TH1* fo_fr2 = new TH1F("fo_fr2", "mc3 p_{T} binned", 100, 0, 0.3);
    //e1.Draw("fo_fr>>fo_fr1", cut_mm_pred);
    //e2.Draw("fo_fr>>fo_fr2", cut_mm_pred);
    //rt::TH1Overlay p2("Fake Rate;FR");
    //p2.Add(fo_fr1);
    //p2.Add(fo_fr2);
    //p2.Draw();
    //c1->Print("plots/FakeRateMaker/h_fo_fr_compare.png");

    //TH1* fo_fr_vs_eta1 = new TH2F("fo_fr_vs_eta1", "mc3 matched"     , 40, -2.5, 2.5, 100, 0, 0.3);
    //TH1* fo_fr_vs_eta2 = new TH2F("fo_fr_vs_eta2", "mc3 p_{T} binned", 40, -2.5, 2.5, 100, 0, 0.3);
    //e1.Draw("fo_fr:fo_eta>>fo_fr_vs_eta1", cut_mm_pred);
    //e2.Draw("fo_fr:fo_eta>>fo_fr_vs_eta2", cut_mm_pred);
    //rt::TH1Overlay p3("Fake Rate vs #eta;#eta;FR", "sb::off");
    //p3.Add(fo_fr_vs_eta1);
    //p3.Add(fo_fr_vs_eta2);
    //p3.Draw("box");
    //c1->Print("plots/FakeRateMaker/h_fo_fr_vs_eta_compare.png");
}
