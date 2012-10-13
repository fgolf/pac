{
    TCanvas c1("c1", "c1", 700, 500);
    rt::TH1Container hc1("plots/outreach/closure/sbottomtop.root");
    hc1["h_sparm_ratio_v1"]->SetStats(false);
    hc1["h_sparm_ratio_v1"]->Draw("colz");
    rt::mkdir("plots/outreach/preapproval/");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_sbottomtop.pdf");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_sbottomtop.png");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_sbottomtop.eps");

    rt::TH1Container hc2("plots/outreach/closure/glustop.root");
    hc2["h_sparm_ratio_v2"]->SetStats(false);
    hc2["h_sparm_ratio_v2"]->Draw("colz");
    //hc2["h_sparm_ratio_v2"]->SetMinimum(0.8);
    //hc2["h_sparm_ratio_v2"]->SetMaximum(1.2);
    rt::mkdir("plots/outreach/preapproval/");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_glustop.pdf");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_glustop.png");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_glustop.eps");

    rt::TH1Container hc3("plots/outreach/closure/glusbottom.root");
    hc3["h_sparm_ratio_v3"]->SetStats(false);
    hc3["h_sparm_ratio_v3"]->Draw("colz");
    rt::mkdir("plots/outreach/preapproval/");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_glusbottom.pdf");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_glusbottom.png");
    c1->Print("plots/outreach/preapproval/h_outreach_ratio_glusbottom.eps");

    rt::CopyIndexPhp("plots/outreach/preapproval/");
}
