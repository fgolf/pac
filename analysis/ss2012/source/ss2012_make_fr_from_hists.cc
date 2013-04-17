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
#include <tr1/array>
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
        printf("Calculating SF in mass window [%4.2f,%4.2f]...\n\n", cut_lower, cut_upper);
        printf("data yield: %4.2f\n", y_data);
        printf("MC yield: %4.2f\n", y_mc);
        cout << "--------------------------------" << endl;
        printf("SF: %4.2f\n", sf);
        cout << endl;
    }
    
    return FakeScalingStruct(sf, unc_stat, unc_syst);
}

void SetScalingHistValues(TH2* h_scale, const FakeScalingStruct& fake_scale)
{
    for (int xidx = 0; xidx < h_scale->GetNbinsX()+1; xidx++)
    {
        for (int yidx = 0; yidx < h_scale->GetNbinsY()+1; yidx++)
        {
            h_scale->SetBinContent(xidx, yidx, 1.0);
            h_scale->SetBinError(xidx, yidx, 0.0);
        }
    }
    return;
}

TH2* ApplyScalingHist(TH2* h_unscaled, TH2* h_scale_factor, float lumi_scale)
{
    TH2* h_scaled = dynamic_cast<TH2*>(h_unscaled->Clone(Form("%s_scaled", h_unscaled->GetName())));
    h_scaled->Scale(lumi_scale);
    h_scaled->Multiply(h_scale_factor);
    return h_scaled;
}

TH2* CreateAbove20CorrectionHist(TH2* h_template)
{
    TH2* h_scale = dynamic_cast<TH2*>(h_template->Clone("h_above20c"));
    h_scale->Clear();
    for (int xidx = 0; xidx < h_scale->GetNbinsX()+1; xidx++)
    {
        for (int yidx = 0; yidx < h_scale->GetNbinsY()+1; yidx++)
        {
            const float pt = h_scale->GetYaxis()->GetBinUpEdge(yidx);
            if (pt > 20.0)
            {
                h_scale->SetBinContent(xidx, yidx, 1.0);
                h_scale->SetBinError(xidx, yidx, 0.0);
            }
            else
            {
                h_scale->SetBinContent(xidx, yidx, 0.0);
                h_scale->SetBinError(xidx, yidx, 0.0);
            }
        }
    }
    return h_scale;
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
    double ele_lumi                     = 1.0;
    double mu_lumi                      = 1.0;
    double ele_noiso_lumi               = 1.0;
    double mu_iso_lumi                  = 1.0;
    bool verbose                        = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"   , "print this menu")
        ("in_data"       , po::value<std::string>(&data_input_file)->required() , "REQUIRED: name of input data root file"                             )
        ("in_mc"         , po::value<std::string>(&mc_input_files)->required()  , "REQUIRED: name of input MC root file"                               )
        ("output"        , po::value<std::string>(&output_file)->required()     , "REQUIRED: output file name for lists (blank means print to screen)" )
        ("ele_lumi"      , po::value<double>(&ele_lumi)                         , "luminosity collected on electron utility triggers"                  )
        ("mu_lumi"       , po::value<double>(&mu_lumi)                          , "luminosity collected on muon utility triggers"                      )
        ("ele_noiso_lumi", po::value<double>(&ele_noiso_lumi)                   , "luminosity collected on electron utility triggers with no isolation")
        ("mu_iso_lumi"   , po::value<double>(&mu_iso_lumi)                      , "luminosity collected on muon utility triggers with isolation"       )
        ("verbose"       , po::value<bool>(&verbose)                            , "print the event lists (default is false)"                           )
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
    cout << "data_input_file :\t" << data_input_file << endl;
    cout << "mc_input_files  :\t" << mc_input_files  << endl;
    cout << "output_file     :\t" << output_file     << endl;
    cout << "ele_lumi        :\t" << ele_lumi        << endl;
    cout << "mu_lumi         :\t" << mu_lumi         << endl;
    cout << "ele_noiso_lumi  :\t" << ele_noiso_lumi  << endl;
    cout << "mu_iso_lumi     :\t" << mu_iso_lumi     << endl;
    cout << "verbose         :\t" << verbose         << endl;

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

    // check mc files
    if (v_mc_input_files.empty())
    {
        cout << "[ss2012_make_fr_from_hists]: no mc files given.  exiting" << endl;
        return 0;
    }

    // call sumw2() for all histograms
    TH1::SetDefaultSumw2();

    // get the data histograms
    rt::TH1Container hc_data(data_input_file);
    rt::TH1Container hc_mc(v_mc_input_files.front());
    for (size_t index = 1; index < v_mc_input_files.size(); index++)
    {
        hc_mc += rt::TH1Container(v_mc_input_files[index]);
    }

    // away jets
    const std::tr1::array<unsigned int, 3> ajetpt = {{20, 40, 60}};

    // output hist containter
    rt::TH1Container hc_new(hc_data);

    for (size_t i = 0; i != ajetpt.size(); i++)
    {
        const std::string jpt_str = Form("%uc", ajetpt[i]);
        const char* const jpt = jpt_str.c_str();

        // get data/MC scale factors
        const float mt_cut_min = 60.1f;
        const float mt_cut_max = 99.9f;
        TH1* h_data_el_num_mt_met30gt = dynamic_cast<TH1*>(hc_data[Form("h_el_num%s_mt_met30gt", jpt)]);
        TH1* h_mc_el_num_mt_met30gt   = dynamic_cast<TH1*>(hc_mc  [Form("h_el_num%s_mt_met30gt", jpt)]);
        h_mc_el_num_mt_met30gt->Scale(ele_lumi);
        FakeScalingStruct el_sf = GetPromptSF(h_data_el_num_mt_met30gt, h_mc_el_num_mt_met30gt, mt_cut_min, mt_cut_max, verbose);    

        TH1* h_data_mu_num_mt_met30gt = dynamic_cast<TH1*>(hc_data[Form("h_mu_num%s_mt_met30gt", jpt)]);
        TH1* h_mc_mu_num_mt_met30gt   = dynamic_cast<TH1*>(hc_mc  [Form("h_mu_num%s_mt_met30gt", jpt)]);
        h_mc_mu_num_mt_met30gt->Scale(mu_lumi);
        FakeScalingStruct mu_sf = GetPromptSF(h_data_mu_num_mt_met30gt, h_mc_mu_num_mt_met30gt, mt_cut_min, mt_cut_max, verbose);

        TH1* h_data_el_noiso_num_mt_met30gt = dynamic_cast<TH1*>(hc_data[Form("h_el_noiso_num%s_mt_met30gt", jpt)]);
        TH1* h_mc_el_noiso_num_mt_met30gt   = dynamic_cast<TH1*>(hc_mc  [Form("h_el_noiso_num%s_mt_met30gt", jpt)]);
        h_mc_el_noiso_num_mt_met30gt->Scale(ele_noiso_lumi);
        FakeScalingStruct el_noiso_sf = GetPromptSF(h_data_el_noiso_num_mt_met30gt, h_mc_el_noiso_num_mt_met30gt, mt_cut_min, mt_cut_max, verbose);    

        TH1* h_data_mu_iso_num_mt_met30gt = dynamic_cast<TH1*>(hc_data[Form("h_mu_iso_num%s_mt_met30gt", jpt)]);
        TH1* h_mc_mu_iso_num_mt_met30gt   = dynamic_cast<TH1*>(hc_mc  [Form("h_mu_iso_num%s_mt_met30gt", jpt)]);
        h_mc_mu_iso_num_mt_met30gt->Scale(mu_iso_lumi);
        FakeScalingStruct mu_iso_sf = GetPromptSF(h_data_mu_iso_num_mt_met30gt, h_mc_mu_iso_num_mt_met30gt, mt_cut_min, mt_cut_max, verbose);

        // correct electron fake rate
        // ----------------------------------------------------------------------------------------------------- //


        TH2* h_data_el_num       = dynamic_cast<TH2*>(hc_data[Form("h_el_num%s"      , jpt)]->Clone(Form("h_data_el_num%s_ewkcor"      , jpt)));
        TH2* h_data_el_fo        = dynamic_cast<TH2*>(hc_data[Form("h_el_fo%s"       , jpt)]->Clone(Form("h_data_el_fo%s_ewkcor"       , jpt)));
        TH2* h_data_el_noiso_num = dynamic_cast<TH2*>(hc_data[Form("h_el_num%s_noiso", jpt)]->Clone(Form("h_data_el_num%s_noiso_ewkcor", jpt)));
        TH2* h_data_el_noiso_fo  = dynamic_cast<TH2*>(hc_data[Form("h_el_fo%s_noiso" , jpt)]->Clone(Form("h_data_el_fo%s_noiso_ewkcor" , jpt)));

        // create an artificial histogram for scaling
        TH2* h_ele_scaling = dynamic_cast<TH2*>(h_data_el_num->Clone(Form("h_el%s_scaling", jpt)));
        SetScalingHistValues(h_ele_scaling, el_sf);
        TH2* h_mc_el_num = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_el_num%s", jpt)]), h_ele_scaling, ele_lumi);
        TH2* h_mc_el_fo  = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_el_fo%s" , jpt)]), h_ele_scaling, ele_lumi);

        TH2* h_ele_noiso_scaling = dynamic_cast<TH2*>(h_data_el_noiso_num->Clone(Form("h_el%s_noiso_scaling", jpt)));
        SetScalingHistValues(h_ele_noiso_scaling, el_noiso_sf);
        TH2* h_mc_el_noiso_num = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_el_num%s_noiso", jpt)]), h_ele_noiso_scaling, ele_noiso_lumi);
        TH2* h_mc_el_noiso_fo  = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_el_fo%s_noiso" , jpt)]), h_ele_noiso_scaling, ele_noiso_lumi);

        // subtract contamination
        h_data_el_num->Add(h_mc_el_num, -1);
        h_data_el_fo->Add(h_mc_el_fo, -1);
        h_data_el_noiso_num->Add(h_mc_el_noiso_num, -1);
        h_data_el_noiso_fo->Add(h_mc_el_noiso_fo, -1);

        // create fake rates and projections
        TH2* h_elfr_ewkcor        = rt::MakeEfficiencyPlot2D(        h_data_el_num, h_data_el_fo,      Form("h_elfr%s_ewkcor"       , jpt), Form("electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > %d), corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_elfr_vs_pt_ewkcor  = rt::MakeEfficiencyProjectionPlot(h_data_el_num, h_data_el_fo, "y", Form("h_elfr%s_ewkcor_vs_pt" , jpt), Form("electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > %d), corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_elfr_vs_eta_ewkcor = rt::MakeEfficiencyProjectionPlot(h_data_el_num, h_data_el_fo, "x", Form("h_elfr%s_ewkcor_vs_eta", jpt), Form("electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > %d), corrected for prompt EWK contamination", ajetpt[i]), 20.0f , 9999.0f);

        TH2* h_elfr_noiso_ewkcor        = rt::MakeEfficiencyPlot2D(        h_data_el_noiso_num, h_data_el_noiso_fo,      Form("h_elfr%s_noiso_ewkcor"       , jpt), Form("electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > %d), corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_elfr_vs_pt_noiso_ewkcor  = rt::MakeEfficiencyProjectionPlot(h_data_el_noiso_num, h_data_el_noiso_fo, "y", Form("h_elfr%s_noiso_ewkcor_vs_pt" , jpt), Form("electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > %d), corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_elfr_vs_eta_noiso_ewkcor = rt::MakeEfficiencyProjectionPlot(h_data_el_noiso_num, h_data_el_noiso_fo, "x", Form("h_elfr%s_noiso_ewkcor_vs_eta", jpt), Form("electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > %d), corrected for prompt EWK contamination", ajetpt[i]), 10.0f , 9999.0f);

        // correct muon fake rate
        // ----------------------------------------------------------------------------------------------------- //

        TH2* h_data_mu_num     = dynamic_cast<TH2*>(hc_data[Form("h_mu_num%s"    , jpt)]->Clone(Form("h_data_mu_num%s_ewkcor"    ,jpt)));
        TH2* h_data_mu_fo      = dynamic_cast<TH2*>(hc_data[Form("h_mu_fo%s"     , jpt)]->Clone(Form("h_data_mu_fo%s_ewkcor"     ,jpt)));
        TH2* h_data_mu_iso_num = dynamic_cast<TH2*>(hc_data[Form("h_mu_num%s_iso", jpt)]->Clone(Form("h_data_mu_num%s_iso_ewkcor",jpt)));
        TH2* h_data_mu_iso_fo  = dynamic_cast<TH2*>(hc_data[Form("h_mu_fo%s_iso" , jpt)]->Clone(Form("h_data_mu_fo%s_iso_ewkcor" ,jpt)));

        // create an artificial histogram for scaling
        TH2* h_mu_scaling = dynamic_cast<TH2*>(h_data_mu_num->Clone(Form("h_mu%s_scaling", jpt)));
        SetScalingHistValues(h_mu_scaling, mu_sf);
        TH2* h_mc_mu_num = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_mu_num%s", jpt)]), h_mu_scaling, mu_lumi);
        TH2* h_mc_mu_fo  = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_mu_fo%s" , jpt)]), h_mu_scaling, mu_lumi);

        TH2* h_mu_iso_scaling = dynamic_cast<TH2*>(h_data_mu_iso_num->Clone(Form("h_mu%s_iso_scaling", jpt)));
        SetScalingHistValues(h_mu_iso_scaling, mu_iso_sf);
        TH2* h_mc_mu_iso_num = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_mu_num%s_iso", jpt)]), h_mu_iso_scaling, mu_iso_lumi);
        TH2* h_mc_mu_iso_fo  = ApplyScalingHist(dynamic_cast<TH2*>(hc_mc[Form("h_mu_fo%s_iso" , jpt)]), h_mu_iso_scaling, mu_iso_lumi);
        h_mc_mu_iso_num->SetName(Form("h_mc_mu_iso_num%s", jpt));
        h_mc_mu_iso_fo ->SetName(Form("h_mc_mu_iso_fo%s" , jpt));

        // only apply correction for iso trigger derived FR above 20 GeV --> stats too low below 20 GeV
        TH2* h_above20c = CreateAbove20CorrectionHist(h_mu_iso_scaling);
        h_mc_mu_iso_num->Multiply(h_above20c);
        h_mc_mu_iso_fo->Multiply(h_above20c);

        // subtract contamination
        h_data_mu_num->Add(h_mc_mu_num, -1);
        h_data_mu_fo->Add(h_mc_mu_fo, -1);
        h_data_mu_iso_num->Add(h_mc_mu_iso_num, -1);
        h_data_mu_iso_fo->Add(h_mc_mu_iso_fo, -1);
        h_data_mu_iso_num->SetName(Form("h_data_mu_iso_num%s", jpt));
        h_data_mu_iso_fo ->SetName(Form("h_data_mu_iso_fo%s" , jpt));

        // create fake rates and projections
        TH2* h_mufr_ewkcor        = rt::MakeEfficiencyPlot2D(        h_data_mu_num, h_data_mu_fo,      Form("h_mufr%s_ewkcor"       , jpt), Form("#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > %d, corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_mufr_vs_pt_ewkcor  = rt::MakeEfficiencyProjectionPlot(h_data_mu_num, h_data_mu_fo, "y", Form("h_mufr%s_ewkcor_vs_pt" , jpt), Form("#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > %d, corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_mufr_vs_eta_ewkcor = rt::MakeEfficiencyProjectionPlot(h_data_mu_num, h_data_mu_fo, "x", Form("h_mufr%s_ewkcor_vs_eta", jpt), Form("#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > %d, corrected for prompt EWK contamination", ajetpt[i]), 20., 9999.);

        TH2* h_mufr_iso_ewkcor        = rt::MakeEfficiencyPlot2D(        h_data_mu_iso_num, h_data_mu_iso_fo,      Form("h_mufr%s_iso_ewkcor"       , jpt), Form("#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > %d, corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_mufr_vs_pt_iso_ewkcor  = rt::MakeEfficiencyProjectionPlot(h_data_mu_iso_num, h_data_mu_iso_fo, "y", Form("h_mufr%s_iso_ewkcor_vs_pt" , jpt), Form("#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > %d, corrected for prompt EWK contamination", ajetpt[i]));
        TH1* h_mufr_vs_eta_iso_ewkcor = rt::MakeEfficiencyProjectionPlot(h_data_mu_iso_num, h_data_mu_iso_fo, "x", Form("h_mufr%s_iso_ewkcor_vs_eta", jpt), Form("#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > %d, corrected for prompt EWK contamination", ajetpt[i]), 5.0f, 9999.);

        // collect hists
        // ----------------------------------------------------------------------------------------------------- //

        hc_new.Add(h_above20c);
        hc_new.Add(h_elfr_ewkcor);
        hc_new.Add(h_elfr_vs_pt_ewkcor);
        hc_new.Add(h_elfr_vs_eta_ewkcor);
        hc_new.Add(h_mufr_ewkcor);
        hc_new.Add(h_mufr_vs_pt_ewkcor);
        hc_new.Add(h_mufr_vs_eta_ewkcor);
        hc_new.Add(h_ele_scaling);
        hc_new.Add(h_mu_scaling);
        hc_new.Add(h_elfr_noiso_ewkcor);
        hc_new.Add(h_elfr_vs_pt_noiso_ewkcor);
        hc_new.Add(h_elfr_vs_eta_noiso_ewkcor);
        hc_new.Add(h_mufr_iso_ewkcor);
        hc_new.Add(h_mufr_vs_pt_iso_ewkcor);
        hc_new.Add(h_mufr_vs_eta_iso_ewkcor);
        hc_new.Add(h_ele_noiso_scaling);
        hc_new.Add(h_mu_iso_scaling);
        hc_new.Add(h_mc_mu_iso_num);
        hc_new.Add(h_mc_mu_iso_fo);
        hc_new.Add(h_data_mu_iso_num);
        hc_new.Add(h_data_mu_iso_fo);

    } // end ajetpt loop

    // save output 
    // ----------------------------------------------------------------------------------------------------- //

    hc_new.Write(output_file,"","RECREATE");

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
