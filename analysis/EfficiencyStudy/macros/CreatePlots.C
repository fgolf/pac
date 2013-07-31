#include "rt/RootTools.h"
#include "at/Sample.h"
#include "TChain.h"
#include "TCut.h"
#include "TEventList.h"
#include <string> 

using namespace std;
using namespace rt;

struct iso_type_t
{
    iso_type_t(const string& v, const string& n, const string& t, int b, float x0, float x1) 
        : var(v)
        , name(n) 
        , title(t) 
        , nbins(b)
        , min(x0)
        , max(x1)
    {}
    string var;
    string name;
    string title;
    int nbins;
    float min;
    float max;
};

void CreatePlots(const long num_entries = 100000000)
{
    TChain e("tree");
    //e.Add("babies/data_dmu_19p47.root");
    e.Add("babies/dy.root");

    // book
    rt::TH1Container hc;
    hc.Add(new TH1D("h_mass"      , "invariant mass;mass (GeV)"                          ,  40, 70.0, 110.0));
    hc.Add(new TH1D("h_nvtxs"     , "# of vertices;# vertices"                           ,  40, -0.5,  39.5));
    hc.Add(new TH1D("h_mu1_pt"    , "pt of leading muon;p_{T} (GeV)"                     , 100,  0.0, 100.0));
    hc.Add(new TH1D("h_mu2_pt"    , "pt of training muons;p_{T} (GeV)"                   , 100,  0.0, 100.0));

    hc.Add(new TH1D("h_den", "pt of den muons;p_{T} (GeV)", 20, 30,50));
    hc.Add(new TH1D("h_num", "pt of num muons;p_{T} (GeV)", 20, 30,50));
    hc.Add(new TH1D("h_num2", "pt of num muons;p_{T} (GeV)", 20, 30,50));

    vector<iso_type_t> iso_types;
    iso_types.push_back(iso_type_t("pfiso"   , "abs_pfiso" , "absolute PF iso"                , 500, 0.0, 10.0)); 
    iso_types.push_back(iso_type_t("pfiso"   , "rel_pfiso" , "relative PF iso"                , 200, 0.0, 0.20)); 
    iso_types.push_back(iso_type_t("corpfiso", "abs_cpfiso", "absolute corr PF iso"           , 200, 0.0, 10.0)); 
    iso_types.push_back(iso_type_t("corpfiso", "rel_cpfiso", "relative corr PF iso"           , 200, 0.0, 0.20)); 
    iso_types.push_back(iso_type_t("chiso"   , "chiso"     , "absolute charge hadron PF iso"  , 200, 0.0, 10.0)); 
    iso_types.push_back(iso_type_t("emiso"   , "emiso"     , "absolute e&m PF iso"            , 200, 0.0, 10.0)); 
    iso_types.push_back(iso_type_t("nhiso"   , "nhiso"     , "absolute neutral hadron PF iso" , 200, 0.0, 10.0)); 

    for (size_t i = 0; i != iso_types.size(); i++)
    {
        //const char* var   = iso_types[i].var.c_str(); 
        const char* name  = iso_types[i].name.c_str();  
        const char* title = iso_types[i].title.c_str(); 
        int nbins         = iso_types[i].nbins;
        float min         = iso_types[i].min;
        float max         = iso_types[i].max;

        hc.Add(new TH1D(Form("h_%s"              , name), Form("%s;pfiso"                                              , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050"         , name), Form("%s (30 < p^{#mu}_{T} < 50);pfiso"                      , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3035"         , name), Form("%s (30 < p^{#mu}_{T} < 35);pfiso"                      , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3540"         , name), Form("%s (35 < p^{#mu}_{T} < 40);pfiso"                      , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_4045"         , name), Form("%s (40 < p^{#mu}_{T} < 45);pfiso"                      , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_4550"         , name), Form("%s (45 < p^{#mu}_{T} < 50);pfiso"                      , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_barrel"  , name), Form("%s (30 < p^{#mu}_{T} < 50, |#eta| < 1.1);pfiso"        , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_endcap"  , name), Form("%s (30 < p^{#mu}_{T} < 50, |#eta| > 1.1);pfiso"        , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_nvtx10"  , name), Form("%s (30 < p^{#mu}_{T} < 50, # vertices < 10);pfiso"     , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_nvtx1020", name), Form("%s (30 < p^{#mu}_{T} < 50, 10 < # vertices < 20);pfiso", title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_nvtx20"  , name), Form("%s (30 < p^{#mu}_{T} < 50, # vertices > 20);pfiso"     , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_barrel_nvtx10"  , name), Form("%s (30 < p^{#mu}_{T} < 50, barrel, # vertices < 10);pfiso"     , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_barrel_nvtx1020", name), Form("%s (30 < p^{#mu}_{T} < 50, barrel, 10 < # vertices < 20);pfiso", title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_barrel_nvtx20"  , name), Form("%s (30 < p^{#mu}_{T} < 50, barrel, # vertices > 20);pfiso"     , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_endcap_nvtx10"  , name), Form("%s (30 < p^{#mu}_{T} < 50, endcap, # vertices < 10);pfiso"     , title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_endcap_nvtx1020", name), Form("%s (30 < p^{#mu}_{T} < 50, endcap, 10 < # vertices < 20);pfiso", title), nbins, min, max));
        hc.Add(new TH1D(Form("h_%s_3050_endcap_nvtx20"  , name), Form("%s (30 < p^{#mu}_{T} < 50, endcap, # vertices > 20);pfiso"     , title), nbins, min, max));
        
    }

    //hc.Add(new TH1D("h_pfiso"     , "absolute PF iso;pfiso (GeV)"                        ,  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3050", "absolute PF iso (30 < p^{#mu}_{T} < 50);pfiso (GeV)",  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3035", "absolute PF iso (30 < p^{#mu}_{T} < 35);pfiso (GeV)",  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3540", "absolute PF iso (35 < p^{#mu}_{T} < 40);pfiso (GeV)",  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_4045", "absolute PF iso (40 < p^{#mu}_{T} < 45);pfiso (GeV)",  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_4550", "absolute PF iso (45 < p^{#mu}_{T} < 50);pfiso (GeV)",  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3050_barrel"  , "absolute PF iso (30 < p^{#mu}_{T} < 50, |#eta| < 1.1);pfiso (GeV)"        ,  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3050_endcap"  , "absolute PF iso (30 < p^{#mu}_{T} < 50, |#eta| > 1.1);pfiso (GeV)"        ,  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3050_nvtx10"  , "absolute PF iso (30 < p^{#mu}_{T} < 50, # vertices < 10);pfiso (GeV)"     ,  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3050_nvtx1020", "absolute PF iso (30 < p^{#mu}_{T} < 50, 10 < # vertices < 20);pfiso (GeV)",  30,  0.0, 0.3  ));
    //hc.Add(new TH1D("h_pfiso_3050_nvtx20"  , "absolute PF iso (30 < p^{#mu}_{T} < 50, # vertices > 20);pfiso (GeV)"     ,  30,  0.0, 0.3  ));

    // aliases
    e.SetAlias("l1_pt" , "lep1_p4.pt()"  );
    e.SetAlias("l2_pt" , "lep2_p4.pt()"  );
    e.SetAlias("l1_eta", "lep1_p4.eta())");
    e.SetAlias("l2_eta", "lep2_p4.eta())");

    // cuts
    TCut mm       = "lep1_pdgid*lep2_pdgid==-169";
    TCut zwin     = "76 < dilep_mass && dilep_mass < 106";
    TCut zmatched = "(is_real_data ? 1 : lep1_mc3_momid==23 && lep2_mc3_momid==23)";

    TCut l1_pt_3050 = "30 < l1_pt && l1_pt < 50";
    TCut l2_pt_3050 = "30 < l2_pt && l2_pt < 50";
    TCut l1_pt_3035 = "30 < l1_pt && l1_pt < 35";
    TCut l2_pt_3035 = "30 < l2_pt && l2_pt < 35";
    TCut l1_pt_3540 = "35 < l1_pt && l1_pt < 40";
    TCut l2_pt_3540 = "35 < l2_pt && l2_pt < 40";
    TCut l1_pt_4045 = "40 < l1_pt && l1_pt < 45";
    TCut l2_pt_4045 = "40 < l2_pt && l2_pt < 45";
    TCut l1_pt_4550 = "45 < l1_pt && l1_pt < 50";
    TCut l2_pt_4550 = "45 < l2_pt && l2_pt < 50";

    TCut l1_barrel = "abs(l1_eta) < 1.1";
    TCut l2_barrel = "abs(l2_eta) < 1.1";
    TCut l1_endcap = "abs(l1_eta) > 1.1";
    TCut l2_endcap = "abs(l2_eta) > 1.1";
    
    TCut nvtx10   = "nvtxs < 10";
    TCut nvtx1020 = "10 < nvtxs && nvtxs < 20";
    TCut nvtx20   = "nvtxs > 20";

    TCut l1_den = "";
    TCut l2_den = "";
    TCut l1_num = "lep1_pfiso < 0.1";
    TCut l2_num = "lep2_pfiso < 0.1";

    // draw
    hc.SetDirectory(gDirectory);

    e.Draw(">>event_list", mm && zwin && zmatched, "goff", num_entries);
    TEventList* event_list = dynamic_cast<TEventList*>(gDirectory->Get("event_list"));
    e.SetEventList(event_list);

    e.Draw("dilep_mass>>h_mass", "", "goff", num_entries); 
    e.Draw("nvtxs>>h_nvtxs"    , "", "goff", num_entries); 

    e.Draw("l1_pt>>h_mu1_pt", "", "goff", num_entries); 
    e.Draw("l2_pt>>h_mu2_pt", "", "goff", num_entries); 

    e.Draw("l1_pt>> h_den", l1_den && l1_pt_3050, "goff", num_entries);
    e.Draw("l2_pt>>+h_den", l2_den && l2_pt_3050, "goff", num_entries);
    e.Draw("l1_pt>> h_num", l1_num && l1_pt_3050, "goff", num_entries);
    e.Draw("l2_pt>>+h_num", l2_num && l2_pt_3050, "goff", num_entries);
    //rt::TTreeDraw1D(&e, hc["h_num2"], "l1_pt"   , l1_num && l1_pt_3050, "goff");
    //rt::TTreeDraw1D(&e, hc["h_num2"], "l2_pt>>+", l2_num && l2_pt_3050, "goff");

    for (size_t i = 0; i != iso_types.size(); i++)
    {
        const char* var   = iso_types[i].var.c_str();   
        const char* name  = iso_types[i].name.c_str();  

        const char* draw_iso_l1 = Form("lep1_%s>>h_%s" , var, name);
        const char* draw_iso_l2 = Form("lep2_%s>>+h_%s", var, name);
        if (rt::string_contains(name, "abs"))
        {
            draw_iso_l1 = Form("lep1_%s*l1_pt>>h_%s" , var, name);
            draw_iso_l2 = Form("lep2_%s*l2_pt>>+h_%s", var, name);
        }

        // iso variable
        e.Draw(draw_iso_l1, "", "goff", num_entries); 
        e.Draw(draw_iso_l1, "", "goff", num_entries); 

        // pt bins
        e.Draw(Form("%s_3050", draw_iso_l1), l1_pt_3050, "goff", num_entries); 
        e.Draw(Form("%s_3050", draw_iso_l2), l2_pt_3050, "goff", num_entries); 
        e.Draw(Form("%s_3035", draw_iso_l1), l1_pt_3035, "goff", num_entries); 
        e.Draw(Form("%s_3035", draw_iso_l2), l2_pt_3035, "goff", num_entries); 
        e.Draw(Form("%s_3540", draw_iso_l1), l1_pt_3540, "goff", num_entries); 
        e.Draw(Form("%s_3540", draw_iso_l2), l2_pt_3540, "goff", num_entries); 
        e.Draw(Form("%s_4045", draw_iso_l1), l1_pt_4045, "goff", num_entries); 
        e.Draw(Form("%s_4045", draw_iso_l2), l2_pt_4045, "goff", num_entries); 
        e.Draw(Form("%s_4550", draw_iso_l1), l1_pt_4550, "goff", num_entries); 
        e.Draw(Form("%s_4550", draw_iso_l2), l2_pt_4550, "goff", num_entries); 

        // eta bins
        e.Draw(Form("%s_3050_barrel", draw_iso_l1), l1_pt_3050 && l1_barrel, "goff", num_entries); 
        e.Draw(Form("%s_3050_barrel", draw_iso_l2), l2_pt_3050 && l2_barrel, "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap", draw_iso_l1), l1_pt_3050 && l1_endcap, "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap", draw_iso_l2), l2_pt_3050 && l2_endcap, "goff", num_entries); 

        // # vtx bins
        e.Draw(Form("%s_3050_nvtx10"  , draw_iso_l1), l1_pt_3050 && nvtx10  , "goff", num_entries); 
        e.Draw(Form("%s_3050_nvtx10"  , draw_iso_l2), l2_pt_3050 && nvtx10  , "goff", num_entries); 
        e.Draw(Form("%s_3050_nvtx1020", draw_iso_l1), l1_pt_3050 && nvtx1020, "goff", num_entries); 
        e.Draw(Form("%s_3050_nvtx1020", draw_iso_l2), l2_pt_3050 && nvtx1020, "goff", num_entries); 
        e.Draw(Form("%s_3050_nvtx20"  , draw_iso_l1), l1_pt_3050 && nvtx20  , "goff", num_entries); 
        e.Draw(Form("%s_3050_nvtx20"  , draw_iso_l2), l2_pt_3050 && nvtx20  , "goff", num_entries); 

        // # vtx bins and barrel
        e.Draw(Form("%s_3050_barrel_nvtx10"  , draw_iso_l1), l1_barrel && l1_pt_3050 && nvtx10  , "goff", num_entries); 
        e.Draw(Form("%s_3050_barrel_nvtx10"  , draw_iso_l2), l2_barrel && l2_pt_3050 && nvtx10  , "goff", num_entries); 
        e.Draw(Form("%s_3050_barrel_nvtx1020", draw_iso_l1), l1_barrel && l1_pt_3050 && nvtx1020, "goff", num_entries); 
        e.Draw(Form("%s_3050_barrel_nvtx1020", draw_iso_l2), l2_barrel && l2_pt_3050 && nvtx1020, "goff", num_entries); 
        e.Draw(Form("%s_3050_barrel_nvtx20"  , draw_iso_l1), l1_barrel && l1_pt_3050 && nvtx20  , "goff", num_entries); 
        e.Draw(Form("%s_3050_barrel_nvtx20"  , draw_iso_l2), l2_barrel && l2_pt_3050 && nvtx20  , "goff", num_entries); 

        // # vtx bins and endcap
        e.Draw(Form("%s_3050_endcap_nvtx10"  , draw_iso_l1), l1_endcap && l1_pt_3050 && nvtx10  , "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap_nvtx10"  , draw_iso_l2), l2_endcap && l2_pt_3050 && nvtx10  , "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap_nvtx1020", draw_iso_l1), l1_endcap && l1_pt_3050 && nvtx1020, "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap_nvtx1020", draw_iso_l2), l2_endcap && l2_pt_3050 && nvtx1020, "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap_nvtx20"  , draw_iso_l1), l1_endcap && l1_pt_3050 && nvtx20  , "goff", num_entries); 
        e.Draw(Form("%s_3050_endcap_nvtx20"  , draw_iso_l2), l2_endcap && l2_pt_3050 && nvtx20  , "goff", num_entries); 
    }
    hc.Sumw2();
    hc.SetLineWidth(2);
    hc.SetDirectory(NULL);

    // overlays
    map<string, TH1Overlay> p;
    for (size_t i = 0; i != iso_types.size(); i++)
    {
        const char* name  = iso_types[i].name.c_str();  
        const char* title = iso_types[i].title.c_str(); 
    
        p[Form("p_%s_pt_compare", name)] = TH1Overlay(Form("%s (normalized to unit area); pfiso", title), "dt::norm lg::top sb::right");
        p[Form("p_%s_pt_compare", name)].Add(hc[Form("h_%s_3035", name)], "30 < p^{#mu}_{T} < 35");
        p[Form("p_%s_pt_compare", name)].Add(hc[Form("h_%s_3540", name)], "35 < p^{#mu}_{T} < 40");
        p[Form("p_%s_pt_compare", name)].Add(hc[Form("h_%s_4045", name)], "40 < p^{#mu}_{T} < 45");
        p[Form("p_%s_pt_compare", name)].Add(hc[Form("h_%s_4550", name)], "45 < p^{#mu}_{T} < 50");
        //p[Form("p_%s_pt_compare", name)].SetYAxisRange(0, 1.0);

        p[Form("p_%s_eta_compare", name)] = TH1Overlay(Form("%s (30 < p^{#mu}_{T} < 50); pfiso", title), "dt::norm lg::top sb::right");
        p[Form("p_%s_eta_compare", name)].Add(hc[Form("h_%s_3050_barrel", name)], "|#eta| < 1.1");
        p[Form("p_%s_eta_compare", name)].Add(hc[Form("h_%s_3050_endcap", name)], "|#eta| > 1.1");
        //p[Form("p_%s_eta_compare", name)].SetYAxisRange(0, 1.0);

        p[Form("p_%s_nvtxs_compare", name)] = TH1Overlay(Form("%s (30 < p^{#mu}_{T} < 50); pfiso", title), "dt::norm lg::top sb::right");
        p[Form("p_%s_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_nvtx10"  , name)], "# vertices > 10"     );
        p[Form("p_%s_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_nvtx1020", name)], "10 < # vertices < 20");
        p[Form("p_%s_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_nvtx20"  , name)], "# vertices > 20"     );
        //p[Form("p_%s_nvtxs_compare", name)].SetYAxisRange(0, 1.0);

        p[Form("p_%s_barrel_nvtxs_compare", name)] = TH1Overlay(Form("%s (30 < p^{#mu}_{T} < 50, barrel); pfiso", title), "dt::norm lg::top sb::right");
        p[Form("p_%s_barrel_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_barrel_nvtx10"  , name)], "# vertices > 10"     );
        p[Form("p_%s_barrel_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_barrel_nvtx1020", name)], "10 < # vertices < 20");
        p[Form("p_%s_barrel_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_barrel_nvtx20"  , name)], "# vertices > 20"     );
        //p[Form("p_%s_barrel_nvtxs_compare", name)].SetYAxisRange(0, 1.0);

        p[Form("p_%s_endcap_nvtxs_compare", name)] = TH1Overlay(Form("%s (30 < p^{#mu}_{T} < 50, endcap); pfiso", title), "dt::norm lg::top sb::right");
        p[Form("p_%s_endcap_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_endcap_nvtx10"  , name)], "# vertices > 10"     );
        p[Form("p_%s_endcap_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_endcap_nvtx1020", name)], "10 < # vertices < 20");
        p[Form("p_%s_endcap_nvtxs_compare", name)].Add(hc[Form("h_%s_3050_endcap_nvtx20"  , name)], "# vertices > 20"     );
        //p[Form("p_%s_endcap_nvtxs_compare", name)].SetYAxisRange(0, 1.0);
    }

    // make log plots
    map<string, TH1Overlay> p_log;
    for (map<string, TH1Overlay>::const_iterator iter = p.begin(); iter != p.end(); iter++)
    {
        TH1Overlay plot(iter->second);
        string name = Form("%s_log", iter->first.c_str());
        plot.SetTitle(name);
        plot.SetLogy(true);
        plot.SetYAxisRange(0.001, 0.5);
        p_log[name] = plot;
    }

    // divide
    hc.Add(rt::MakeEfficiencyPlot(hc["h_num"], hc["h_den"], "h_eff", "iso eff (traditional), p_{T}"));
    
    // output
    //hc.Write("plots/data2/hist.root");
    //hc.Print("plots/data2", "png");
    //Print(p    , "plots/data2/overlays", "eps");
    //Print(p_log, "plots/data2/overlays", "eps");
    hc.Write("plots/dy/hist.root");
    hc.Print("plots/dy", "png");
    Print(p    , "plots/dy/overlays", "eps");
    Print(p_log, "plots/dy/overlays", "eps");

    // done
    return;
}

void CreatePdfHist(const std::string& filename = "plots/data/hist.root")
{
    rt::TH1Container hc(filename);
    //hc.List();
    TH1D* h_pdf = dynamic_cast<TH1D*>(hc["h_abs_pfiso_3050"]->Clone("h_pdf_abs_pfiso_3050"));
    rt::Scale(h_pdf, 1.0);
    rt::Write(h_pdf, "plots/data/pdf.root");
}

void OverlayPdfHist()
{
    rt::TH1Container hc_dyll("plots/pdf/h_dy_pdf.root");
    rt::TH1Container hc_data("plots/pdf/h_data_dmu_pdf.root");

    map<string, TH1Overlay> p;
    p["p_pdf"] = TH1Overlay("muon iso PDF", "lg::top_left sb::right logy");
    p["p_pdf"].Add(hc_data["h_pdf_abs_pfiso_3050"], "data" , kBlack, 2);
    p["p_pdf"].Add(hc_dyll["h_pdf_abs_pfiso_3050"], "DY MC", kRed  , 2);
    p["p_pdf"].SetYAxisRange(0.001, 0.1);
    Print(p, "plots/pdf", "eps");

	TH1D* ratio = dynamic_cast<TH1D*>(hc_data["h_pdf_abs_pfiso_3050"]->Clone("h_pdf_abs_pfiso_3050_ratio"));
	ratio->Divide(hc_dyll["h_pdf_abs_pfiso_3050"]);
	ratio->SetLineWidth(1);
	ratio->SetLineColor(kBlack);
	ratio->Draw();
	rt::Print(ratio, "plots/pdf/h_pdf_abs_pfiso_3050_ratio", "eps");
}


void PrintDilepMassPlots(const std::string& filename = "plots/data2/dmu.root")
{
    rt::TH1Container hc(filename);
	rt::Print(hc["h_dilep_mass_0510" ], "plots/data2", "eps");
	rt::Print(hc["h_dilep_mass_1020" ], "plots/data2", "eps");
	rt::Print(hc["h_dilep_mass_2030" ], "plots/data2", "eps");
	rt::Print(hc["h_dilep_mass_3050" ], "plots/data2", "eps");
	rt::Print(hc["h_dilep_mass_50100"], "plots/data2", "eps");
}

void OverlayEffPlot(const std::string& filename = "plots/dy/eff.root")
{
    rt::TH1Container hc(filename);
    map<string, TH1Overlay> p;
    p["p_eff_vs_pt"] = TH1Overlay("muon iso efficiency vs p_{T}", "lg::bottom sb::off");
    p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt"        ], "using PDF"       , kBlue   , 2);
    //p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt_mctruth"], "using N/D"       , kRed    , 2);
    p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt_tap"    ], "using simple T&P", kGreen+2, 2);
    Print(p, "plots/dy/overlays", "eps");
}

void OverlayEffPlotData(const std::string& filename = "plots/data2/dmu.root")
{
    rt::TH1Container hc(filename);
    map<string, TH1Overlay> p;
    p["p_eff_vs_pt"] = TH1Overlay("muon iso efficiency vs p_{T}", "lg::bottom sb::off");
    p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt"        ], "using PDF"       , kBlue   , 2);
    p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt_tap"    ], "using simple T&P", kGreen+2, 2);
    Print(p, "plots/data2/overlays", "eps");
}

void DataToMCPlot()
{
    TH1F* h_dy    = rt::GetHistFromRootFile<TH1F>("plots/dy/eff.root"  , "h_eff_vs_pt");
    TH1F* h_data  = rt::GetHistFromRootFile<TH1F>("plots/data/eff.root", "h_eff_vs_pt");
    TH1F* h_ratio = dynamic_cast<TH1F*>(h_data->Clone("h_ratio_vs_pt"));
    h_ratio->Divide(h_dy);
    //TH1* h_ratio = rt::MakeEfficiencyPlot(h_data, h_dy, "h_ratio_vs_pt"); 
    h_ratio->GetYaxis()->SetRangeUser(0, 1.8);
    h_ratio->Draw();

    //map<string, TH1Overlay> p;
    //p["p_eff_vs_pt"] = TH1Overlay("muon iso efficiency vs p_{T}", "lg::bottom sb::off");
    //p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt"        ], "using PDF"       , kBlue   , 2);
    ////p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt_mctruth"], "using N/D"       , kRed    , 2);
    //p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt_tap"    ], "using simple T&P", kGreen+2, 2);
    //Print(p, "plots/data/overlays", "eps");
}

/* void OverlayIsoPlots(const std::string& suffix = "eps") */
/* { */
/*     rt::TH1Container hc_data("plots/data/dmu.root"); */
/*  */
/*     map<string, TH1Overlay> p; */
/*     p["p_eff_vs_pt"] = TH1Overlay("muon iso efficiency vs p_{T}", "lg::bottom sb::off"); */
/*     p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt"        ], "using PDF"       , kBlue   , 2); */
/*     p["p_eff_vs_pt"].Add(hc["h_eff_vs_pt_tap"    ], "using simple T&P", kGreen+2, 2); */
/*     Print(p, "plots/data/dmu/overlays", "eps"); */
/* } */
