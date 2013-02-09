#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/DileptonChargeType.h"
#include "at/DileptonHypType.h"
#include "AnalysisType.h"
#include "SignalRegion.h"
#include "SSB2012.h"
#include "CTable.h"
#include <string>
#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

struct FakeScalingStruct
{
    FakeScalingStruct(double sf_, double unc_stat_, double unc_syst_) : sf(sf_), unc_stat(unc_stat_), unc_syst(unc_syst_) {}
    FakeScalingStruct() : sf(1.), unc_stat(0.), unc_syst(0.) {}
    double sf;
    double unc_stat;
    double unc_syst;
};

FakeScalingStruct GetPromptSF (TH1* h_data, TH1* h_mc, double cut_lower, double cut_upper,  bool verbose = false)
{
    int lower_bin = h_data->FindBin(cut_lower);
    int upper_bin = h_data->FindBin(cut_upper);

    double y_data  = h_data->Integral(lower_bin, upper_bin);
    double y_mc_err = 0.;
    double y_mc = h_mc->IntegralAndError(lower_bin, upper_bin, y_mc_err);

    double sf = y_data / y_mc;
    double unc_stat = sf * sqrt(pow(sqrt(y_data)/y_data,2) + pow(sqrt(y_mc_err)/y_mc,2));
    double unc_syst = fabs(sf - 1.) / 2.;

    if (verbose)
    {
        cout << endl;
        printf(Form("Calculating SF in mass window [%4.2f,%4.2f]...\n\n", cut_lower, cut_upper));
        printf("data yield: %4.2f\n", y_data);
        printf("MC yield: %4.2f\n", y_mc);
        cout << "--------------------------------" << endl;
        printf("SF: %4.2f\n", sf);
        cout << endl;
    }
    
    return FakeScalingStruct(sf, unc_stat, unc_syst);
}

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    // parameters
    std::string data_input_file         = "";
    std::string mc_input_files          = "";
    std::string output_file             = "";
    double ele_lumi                     = 1.;
    double mu_lumi                      = 1.;
    bool verbose                        = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"   , "print this menu")
        ("in_data" , po::value<std::string>(&data_input_file) , "name of input data root file"                            )
        ("in_mc"   , po::value<std::string>(&mc_input_files)  , "name of input MC root file"                              )
        ("output"  , po::value<std::string>(&output_file)     , "output file name for lists (blank means print to screen)")
        ("ele_lumi", po::value<double>(&ele_lumi)             , "luminosity collected on electron utility triggers"       )
        ("mu_lumi" , po::value<double>(&mu_lumi)              , "luminosity collected on muon utility triggers"           )
        ("verbose" , po::value<bool>(&verbose)                , "print the event lists (default is false)"                )

        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (verbose)
    {
        printf("scaling el,mu with lumi %4.2f, %4.2f.\n", ele_lumi, mu_lumi);
    }

    if (vm.count("help")) 
    {
        cout << desc << "\n";
        return 1;
    }

    // check that the data input file exists and is specified
    if (!data_input_file.empty())
    { 
        if (!rt::exists(data_input_file))
        {
            cout << "[ss2012_make_fr_from_hists]: data input file " << data_input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // check that the MC input files exist and are specified
    std::vector<std::string> v_mc_input_files = rt::string_split(mc_input_files, ",");
    for (std::vector<std::string>::const_iterator vstring = v_mc_input_files.begin(); vstring != v_mc_input_files.end(); vstring++)
    {
        if (!vstring->empty())
        { 
            if (!rt::exists(*vstring))
            {
                cout << "[ss2012_make_fr_from_hists]: MC input file " << *vstring << " not found" << endl;
                cout << desc << "\n";
                return 1;
            }
        }
    }

    // do it
    // -------------------------------------------------------------------------------------------------//

    // write output
    if (not output_file.empty())
    {
        rt::mkdir(rt::dirname(output_file), /*force=*/true);    
    }
    else
    {
        cout << "[ss2012_make_fr_from_hists]: no output file given.  printing to stdout" << endl;
    }
    ostream* out_ptr = output_file.empty() ? &cout : new fstream(output_file.c_str(), fstream::out);
    ostream& out = *out_ptr;

    // call sumw2() for all histograms
    TH1::SetDefaultSumw2();

    // get the data histograms
    rt::TH1Container hc_data(data_input_file);
    rt::TH1Container hc_mc(v_mc_input_files[0]);
    for (unsigned int index = 1; index < v_mc_input_files.size(); index++)
    {
        hc_mc += rt::TH1Container(v_mc_input_files[index]);
    }

    // get data/MC scale factors
    TH1* h_data_el_num40c_mt_met30gt = dynamic_cast<TH1*>(hc_data["h_el_num40c_mt_met30gt"]);
    TH1* h_mc_el_num40c_mt_met30gt   = dynamic_cast<TH1*>(hc_mc["h_el_num40c_mt_met30gt"]);
    h_mc_el_num40c_mt_met30gt->Scale(ele_lumi);
    FakeScalingStruct el_sf = GetPromptSF(h_data_el_num40c_mt_met30gt, h_mc_el_num40c_mt_met30gt, 60.1, 99.9, verbose);    

    TH1* h_data_mu_num40c_mt_met30gt = dynamic_cast<TH1*>(hc_data["h_mu_num40c_mt_met30gt"]);
    TH1* h_mc_mu_num40c_mt_met30gt   = dynamic_cast<TH1*>(hc_mc["h_mu_num40c_mt_met30gt"]);
    h_mc_mu_num40c_mt_met30gt->Scale(mu_lumi);
    FakeScalingStruct mu_sf = GetPromptSF(h_data_mu_num40c_mt_met30gt, h_mc_mu_num40c_mt_met30gt, 60.1, 99.9, verbose);

    // correct electron fake rate
    TH2* h_data_el_num40c = dynamic_cast<TH2*>(hc_data["h_el_num40c"]);
    TH2* h_data_el_fo40c  = dynamic_cast<TH2*>(hc_data["h_el_fo40c"]);

    // create an artificial histogram for scaling
    TH1* h_ele_scaling = dynamic_cast<TH2*>(h_data_el_num40c->Clone("h_ele_scaling"));
    for (int xidx = 0; xidx < h_ele_scaling->GetNbinsX()+1; xidx++)
    {
        for (int yidx = 0; yidx < h_ele_scaling->GetNbinsY()+1; yidx++)
        {
            h_ele_scaling->SetBinContent(xidx, yidx, el_sf.sf);
            h_ele_scaling->SetBinError(xidx, yidx, sqrt(pow(el_sf.unc_stat,2) + pow(el_sf.unc_syst,2)));
        }
    }

    TH2* h_mc_el_num40c = dynamic_cast<TH2*>(hc_mc["h_el_num40c"]);
    h_mc_el_num40c->Scale(ele_lumi);
    h_mc_el_num40c->Multiply(h_ele_scaling);
    TH2* h_mc_el_fo40c  = dynamic_cast<TH2*>(hc_mc["h_el_fo40c"]);
    h_mc_el_fo40c->Scale(ele_lumi);
    h_mc_el_fo40c->Multiply(h_ele_scaling);

    h_data_el_num40c->Add(h_mc_el_num40c, -1);
    h_data_el_fo40c->Add(h_mc_el_fo40c, -1);

    TH2* h_elfr40c_ewkcor        = rt::MakeEfficiencyPlot2D(h_data_el_num40c, h_data_el_fo40c, "h_elfr40c_ewkcor", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40), corrected for prompt EWK contamination");
    TH1* h_elfr40c_vs_pt_ewkcor  = rt::MakeEfficiencyProjectionPlot(h_data_el_num40c, h_data_el_fo40c, "y", "h_elfr40c_vs_pt_ewkcor", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40), corrected for prompt EWK contamination");
    TH1* h_elfr40c_vs_eta_ewkcor = rt::MakeEfficiencyProjectionPlot(h_data_el_num40c, h_data_el_fo40c, "x", "h_elfr40c_vs_eta_ewkcor", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40), corrected for prompt EWK contamination", 20., 9999.);

    // correct muon fake rate
    TH2* h_data_mu_num40c = dynamic_cast<TH2*>(hc_data["h_mu_num40c"]);
    TH2* h_data_mu_fo40c  = dynamic_cast<TH2*>(hc_data["h_mu_fo40c"]);

    if (verbose)
    {
    printf("bin 1,1 for data num is: %4.2f\n", h_data_mu_num40c->GetBinContent(1,1));
    printf("bin 1,1 for data fo is: %4.2f\n", h_data_mu_fo40c->GetBinContent(1,1));
    }

    // create an artificial histogram for scaling
    TH1* h_mu_scaling = dynamic_cast<TH2*>(h_data_mu_num40c->Clone("h_mu_scaling"));
    for (int xidx = 0; xidx < h_mu_scaling->GetNbinsX()+1; xidx++)
    {
        for (int yidx = 0; yidx < h_mu_scaling->GetNbinsY()+1; yidx++)
        {
            h_mu_scaling->SetBinContent(xidx, yidx, mu_sf.sf);
            h_mu_scaling->SetBinError(xidx, yidx, sqrt(pow(mu_sf.unc_stat,2) + pow(mu_sf.unc_syst,2)));
        }
    }

    if (verbose)
    {
        printf("bin 1,1 for scaling is: %4.2f\n", h_mu_scaling->GetBinContent(1,1));
    }

    TH2* h_mc_mu_num40c = dynamic_cast<TH2*>(hc_mc["h_mu_num40c"]);
    TH2* h_mc_mu_fo40c  = dynamic_cast<TH2*>(hc_mc["h_mu_fo40c"]);

    h_mc_mu_num40c->Scale(mu_lumi);
    h_mc_mu_fo40c->Scale(mu_lumi);

    if (verbose)
    {
        printf("bin 1,1 for mc num is: %4.2f\n", h_mc_mu_num40c->GetBinContent(1,1));
        printf("bin 1,1 for mc fo is: %4.2f\n", h_mc_mu_fo40c->GetBinContent(1,1));
    }

    h_mc_mu_num40c->Multiply(h_mu_scaling);
    h_mc_mu_fo40c->Multiply(h_mu_scaling);

    if (verbose)
    {
        printf("bin 1,1 for scaled mc num is: %4.2f\n", h_mc_mu_num40c->GetBinContent(1,1));
        printf("bin 1,1 for scaled mc fo is: %4.2f\n", h_mc_mu_fo40c->GetBinContent(1,1));
    }

    h_data_mu_num40c->Add(h_mc_mu_num40c, -1);
    h_data_mu_fo40c->Add(h_mc_mu_fo40c, -1);

    TH2* h_mufr40c_ewkcor        = rt::MakeEfficiencyPlot2D(h_data_mu_num40c, h_data_mu_fo40c, "h_mufr40c_ewkcor", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, corrected for prompt EWK contamination");
    TH1* h_mufr40c_vs_pt_ewkcor  = rt::MakeEfficiencyProjectionPlot(h_data_mu_num40c, h_data_mu_fo40c, "y", "h_mufr40c_vs_pt_ewkcor", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, corrected for prompt EWK contamination");
    TH1* h_mufr40c_vs_eta_ewkcor = rt::MakeEfficiencyProjectionPlot(h_data_mu_num40c, h_data_mu_fo40c, "x", "h_mufr40c_vs_eta_ewkcor", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, corrected for prompt EWK contamination",20., 9999.);

    rt::TH1Container hc_new(hc_data);
    hc_new.Add(*h_elfr40c_ewkcor);
    hc_new.Add(*h_elfr40c_vs_pt_ewkcor);
    hc_new.Add(*h_elfr40c_vs_eta_ewkcor);
    hc_new.Add(*h_mufr40c_ewkcor);
    hc_new.Add(*h_mufr40c_vs_pt_ewkcor);
    hc_new.Add(*h_mufr40c_vs_eta_ewkcor);
    hc_new.Add(*h_ele_scaling);
    hc_new.Add(*h_mu_scaling);

    hc_new.Write(output_file,"","RECREATE");

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
