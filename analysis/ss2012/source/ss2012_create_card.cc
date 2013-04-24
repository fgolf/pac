#include <iostream>
#include <string>
#include "TChain.h"
#include "InterpLooper.h"
#include "SSB2012Wrapper.h"
#include "at/ScanChain.h"
#include "at/Sample.h"
#include "at/YieldType.h"
#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "SSYields.h"
#include <boost/program_options.hpp>

struct card_info_t
{
    card_info_t() {}
    std::string signal_name;
    unsigned int obs;
    float acc;
    float fake;
    float fake_unc;
    float flip;
    float flip_unc;
    float rare;
    float rare_unc;
    float trig_unc;
    float lep_unc;
    float pdf_unc;
    float jer_unc;
    float lumi_unc;
    float beff_up_unc;
    float beff_dn_unc;
    float met_up_unc;
    float met_dn_unc;
    float jes_up_unc;
    float jes_dn_unc;
};


float GetSyst(const float num_up, const float num)
{
    const float syst = 1.0 + (num_up - num)/num;
    return syst;
}


std::string GetSRLabel(ss::SignalRegion::value_type sr)
{
    const unsigned int sr_num = static_cast<unsigned int>(sr);
    return Form((sr < 10 ? "SR0%u_" : "SR%u_"), sr_num);
}


int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;
    using namespace ss;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    std::string input_label         = "";
    std::string output_file         = "";
    std::string syst_file           = "";
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_17Apr2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02222013.root";
    std::string den_hist_file_name  = "";
    std::string analysis_type_name  = "high_pt";
    std::string sr_string           = "-1";
    bool exclusive                  = true;
    float ngen_sf                   = 1.0;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.3;
    float rare_sys_unc              = 0.5;
    float lumi                      = 1.0;
    bool verbose                    = false;
    int run                         = -1;
    int ls                          = -1;
    int event                       = -1;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("label"     , po::value<std::string>(&input_label)->required(), "REQUIRED: name of input label to get the root files: plots/<label>/..."        )
//         ("sample"    , po::value<std::string>(&sample_name)->required(), "REQUIRED: name of input sample (from at/Sample.h)"                             )
        ("syst"      , po::value<std::string>(&syst_file)->required()  , "REQUIRED: file containting systematics"                                        )
        ("output"    , po::value<std::string>(&output_file)            , "name of output root file"                                                      )
        ("anal_type" , po::value<std::string>(&analysis_type_name)     , "name of analysis type (from AnalysisType.h)"                                   )
        ("fr_file"   , po::value<std::string>(&fake_rate_file_name)    , Form("fake rate file name (default: %s)", fake_rate_file_name.c_str())          )
        ("fl_file"   , po::value<std::string>(&flip_rate_file_name)    , Form("flip rate file name (default: %s)", flip_rate_file_name.c_str())          )
        ("den_file"  , po::value<std::string>(&den_hist_file_name)     , Form("den count file name (default: %s)", input_label.c_str())                  )
        ("sr"        , po::value<std::string>(&sr_string)              , "comma seperated list of SRs to run on (any < 0 means all -- default)"          )
        ("ngen_sf"   , po::value<float>(&ngen_sf)                      , Form("scale factor for the # generated events (default is %f)", ngen_sf)        )
        ("fr_unc"    , po::value<float>(&fake_sys_unc)                 , Form("systematic uncertainty for fake prediction (default is %f)", fake_sys_unc))
        ("fr_unc"    , po::value<float>(&fake_sys_unc)                 , Form("systematic uncertainty for fake prediction (default is %f)", fake_sys_unc))
        ("fl_unc"    , po::value<float>(&flip_sys_unc)                 , Form("systematic uncertainty for flip prediction (default is %f)", flip_sys_unc))
        ("rare_unc"  , po::value<float>(&rare_sys_unc)                 , Form("systematic uncertainty for MC prediction (default is %f)", rare_sys_unc)  )
        ("lumi"      , po::value<float>(&lumi)                         , "luminosity"                                                                    )
        ("excl"      , po::value<bool>(&exclusive)                     , "use exclusive signal region"                                                   )
        ("verbose"   , po::value<bool>(&verbose)                       , "verbosity"                                                                     )
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
    

    if (verbose)
    {
        cout << "inputs:" << endl;
        cout << "input_label         :\t" << input_label         << endl;
        //     cout << "sample_name         :\t" << sample_name         << endl;
        cout << "output_file         :\t" << output_file         << endl;
        cout << "syst_file           :\t" << syst_file           << endl;
        cout << "analysis_type_name  :\t" << analysis_type_name  << endl;
        cout << "fake_rate_file_name :\t" << fake_rate_file_name << endl;
        cout << "flip_rate_file_name :\t" << flip_rate_file_name << endl;
        cout << "den_hist_file_name  :\t" << den_hist_file_name  << endl;
        cout << "number_of_events    :\t" << number_of_events    << endl;
        cout << "sr                  :\t" << sr_string           << endl;
        cout << "ngen_sf             :\t" << ngen_sf             << endl;
        cout << "fake_sys_unc        :\t" << fake_sys_unc        << endl;
        cout << "flip_sys_unc        :\t" << flip_sys_unc        << endl;
        cout << "rare_sys_unc        :\t" << rare_sys_unc        << endl;
        cout << "lumi                :\t" << lumi                << endl;
        cout << "exclusive           :\t" << exclusive           << endl;
        cout << "verbose             :\t" << verbose             << endl;
        cout << "run                 :\t" << run                 << endl;
        cout << "ls                  :\t" << ls                  << endl;
        cout << "event               :\t" << event               << endl;
    }

   // check that input file exists and is specified
   if (!syst_file.empty())
   { 
       if (!rt::exists(syst_file))
       {
           cout << "[ss2012_create_card] ERROR: systematic histogram file " << syst_file << " not found" << endl;
           cout << desc << "\n";
           return 1;
       }
   }

    // parse the signal region string
    std::vector<std::string> sr_strings = rt::string_split(sr_string);
    std::vector<unsigned int> sr_nums;
    for (size_t i = 0; i != sr_strings.size(); i++)
    {
        int sr_num_raw = boost::lexical_cast<int>(sr_strings.at(i));
        // any < 0 numbers means run on all
        if (sr_num_raw < 0)
        {
            sr_nums.clear();
            const unsigned int values[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,
                                           10, 11, 12, 13, 14, 15, 16, 17, 18,
                                           20, 21, 22, 23, 24, 25, 26, 27, 28};
            sr_nums.assign(values, values+27);
            break;
        }
        sr_nums.push_back(sr_num_raw);
    }
    if (verbose)
    {
        cout << "[ss2012_create_card] running in SR(s): ";
        for (size_t i = 0; i != sr_nums.size(); i++)
        {
            if (sr_nums.at(i) != sr_nums.back()) {cout << sr_nums.at(i) << ", ";}
            else                                 {cout << sr_nums.at(i) << endl;}
        }
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // analysis type

    // signal region and type

    // sample
//     at::Sample::value_type sample = at::GetSampleFromName(sample_name);
//     const bool is_data = (at::GetSampleInfo(sample).type == at::SampleType::data);

    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = (exclusive ? SignalRegionType::exclusive : SignalRegionType::inclusive);
    const std::string signal_region_type_name                 = GetSignalRegionTypeName(signal_region_type);

    vector<card_info_t> card_infos;
    for (size_t i = 0; i != sr_nums.size(); i++)
    {
        const std::string signal_region_name = Form("sr%d", sr_nums.at(i));
        const ss::SignalRegion::value_type signal_region = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);
        const ss::SignalRegionInfo sr_info               = ss::GetSignalRegionInfo(signal_region, analysis_type, signal_region_type);
        const int charge_option = 0;

        // get the yields
        std::map<std::string, ss::Yield> m_yield = GetYieldsMap("ss"  , signal_region, analysis_type, signal_region_type, charge_option, input_label);
        std::map<std::string, ss::Yield> m_fake  = GetYieldsMap("fake", signal_region, analysis_type, signal_region_type, charge_option, input_label);
        ss::Yield yield_data = m_yield["data"];
        ss::Yield yield_rare = m_yield["rare"];
        ss::Yield yield_spil = m_fake ["rare"];
        ss::Yield yield_fake = ss::GetFakeYield(at::Sample::data, signal_region, analysis_type, signal_region_type, charge_option, input_label);
        ss::Yield yield_flip = ss::GetFlipYield(at::Sample::data, signal_region, analysis_type, signal_region_type, charge_option, input_label); 

        // subtract the spillage from the rare MC
        ss::Yield yield_cfake = (yield_fake - yield_spil);

        // set systematic uncertainties
        ss::SetSysUncertainties(yield_rare , rare_sys_unc);
        ss::SetSysUncertainties(yield_cfake, fake_sys_unc);
        ss::SetSysUncertainties(yield_flip , flip_sys_unc);

        // total prediction
        ss::Yield yield_pred = yield_rare;
        yield_pred += yield_cfake;
        yield_pred += yield_flip;

        // systematics and acceptance hists
        rt::TH1Container hc(syst_file);
        //hc.List();

        // make the card
        card_info_t info;
        info.signal_name = rt::string_upper(signal_region_name);
        info.obs         = static_cast<unsigned int>(yield_data.ll);
        info.fake        = yield_cfake.ll;
        info.fake_unc    = 1.0 + (yield_cfake.tll() - yield_cfake.ll)/yield_cfake.ll;
        info.flip        = yield_flip.ll;
        info.flip_unc    = 1.0 + (yield_flip.tll() - yield_flip.ll)/yield_flip.ll;
        info.rare        = yield_rare.ll;
        info.rare_unc    = 1.0 + (yield_rare.tll() - yield_rare.ll)/yield_rare.ll;

        // systematics (percentage) 
        const std::string sr = GetSRLabel(signal_region);
        const float num      = rt::Integral(hc[sr+"nPassing"]);
        const float den      = rt::Integral(hc[sr+"nGenerated"]) * ngen_sf;
        info.acc             = lumi*(num/den);
        info.lumi_unc        = 1.044;
        info.pdf_unc         = 1.02;
        info.lep_unc         = GetSyst(rt::Integral(hc[sr+"nLepEffUP" ]), num);
        info.trig_unc        = GetSyst(rt::Integral(hc[sr+"nTrigEffUP"]), num);
        info.jer_unc         = GetSyst(rt::Integral(hc[sr+"nJER"      ]), num);
        info.jes_up_unc      = GetSyst(rt::Integral(hc[sr+"nJESUP"    ]), num);
        info.jes_dn_unc      = GetSyst(rt::Integral(hc[sr+"nJESDN"    ]), num);
        info.met_up_unc      = GetSyst(rt::Integral(hc[sr+"nMETUP"    ]), num);
        info.met_dn_unc      = GetSyst(rt::Integral(hc[sr+"nMETDN"    ]), num);
        info.beff_up_unc     = GetSyst(rt::Integral(hc[sr+"nBTAUP"    ]), num);
        info.beff_dn_unc     = GetSyst(rt::Integral(hc[sr+"nBTADN"    ]), num);
        card_infos.push_back(info);

//         CTable t_yields;
//         t_yields.useTitle();
//         t_yields.setTitle(Form("yields for SS 2012 %s (%s)", sr_info.name.c_str(), sr_info.title.c_str()));
//         t_yields.setTable()
//             (                                        "obs",                  "pred",                  "fakes",                  "rare",                  "flips")
//             ("value"                  , (int)yield_data.ll, yield_pred.ll_syst_pm(), yield_cfake.ll_syst_pm(), yield_rare.ll_syst_pm(),  yield_flip.ll_syst_pm())
//             ("rel unc factor (1 + dx)",                1.0, yield_pred.ll_rel_unc(), yield_cfake.ll_rel_unc(), yield_rare.ll_rel_unc(),  yield_flip.ll_rel_unc());

        // print it
//         t_yields.print();
    }

    const std::string header = "imax %lu number of search regions\n"
                               "jmax 3 number of backgrounds ('*' = automatic)\n"
                               "kmax * number of nuisance parameters (sources of systematical uncertainties)\n"
                               "------------\n";
    std::string card = Form(header.c_str(), sr_nums.size());

    // per bin info
    string signal_header = "       bin \t\t";
    string signal_obs    = "observation\t\t";
    string rate_header   = "------------\nbin\t\t\t";
    string rate_label    = "process\t\t\t";
    string rate_number   = "process\t\t\t";
    string rate          = "rate\t\t\t";
    string error_header  = "### Error Matrix\n------------\n";
    string fake_sys      = "FakeSys          lnN\t";
    string rare_sys      = "RareMCSys        lnN\t";
    string flip_sys      = "FlipSys          lnN\t";
    string trig_sys      = "TriggerSys       lnN\t";
    string lep_sys       = "LepIdSys         lnN\t";
    string pdf_sys       = "ISRFSRPDF        lnN\t";
    string beff_sys      = "bSys             lnN\t";
    string met_sys       = "mSys             lnN\t";
    string jes_sys       = "jSys             lnN\t";
    string jer_sys       = "JERSys           lnN\t";
    string lumi_sys      = "Lumi             lnN\t";

// "------------\n"
    for (size_t i = 0; i != card_infos.size(); i++)
    {
        signal_header.append(card_infos.at(i).signal_name);
        signal_obs.append(Form("%u", card_infos.at(i).obs));
        rate_header.append(Form("%s\t\t%s\t\t%s\t\t%s", card_infos.at(i).signal_name.c_str(), card_infos.at(i).signal_name.c_str(), card_infos.at(i).signal_name.c_str(), card_infos.at(i).signal_name.c_str())); 
        rate_label.append("signal\t\tfake\t\trare\t\tflip");
        rate_number.append("0\t\t1\t\t2\t\t3");
        rate.append(Form("%1.5f\t\t%1.3f\t\t%1.3f\t\t%1.3f", card_infos.at(i).acc, card_infos.at(i).fake, card_infos.at(i).rare, card_infos.at(i).flip));
        fake_sys.append(Form("-\t\t%1.3f\t\t-\t\t-"    , card_infos.at(i).fake_unc));
        rare_sys.append(Form("-\t\t-\t\t%1.3f\t\t-"    , card_infos.at(i).rare_unc));
        flip_sys.append(Form("-\t\t-\t\t-\t\t%1.3f"    , card_infos.at(i).flip_unc));
        trig_sys.append(Form("%1.3f\t\t-\t\t-\t\t-"    , card_infos.at(i).trig_unc));
        lep_sys.append (Form("%1.3f\t\t-\t\t-\t\t-"    , card_infos.at(i).lep_unc ));
        pdf_sys.append (Form("%1.3f\t\t-\t\t-\t\t-"    , card_infos.at(i).pdf_unc ));
        jer_sys.append (Form("%1.3f\t\t-\t\t-\t\t-"    , card_infos.at(i).jer_unc ));
        lumi_sys.append(Form("%1.3f\t\t-\t\t-\t\t-"    , card_infos.at(i).lumi_unc));
        beff_sys.append(Form("%1.3f/%1.3f\t-\t\t-\t\t-", card_infos.at(i).beff_dn_unc, card_infos.at(i).beff_up_unc));
        met_sys.append (Form("%1.3f/%1.3f\t-\t\t-\t\t-", card_infos.at(i).met_dn_unc , card_infos.at(i).met_up_unc ));
        jes_sys.append (Form("%1.3f/%1.3f\t-\t\t-\t\t-", card_infos.at(i).jes_dn_unc , card_infos.at(i).jes_up_unc ));
        if (i != card_infos.size()-1)
        {
            signal_header.append("\t\t");
            signal_obs.append   ("\t\t");
            rate_header.append  ("\t\t");
            rate_label.append   ("\t\t");
            rate_number.append  ("\t\t");
            rate.append         ("\t\t");
            fake_sys.append     ("\t\t");
            rare_sys.append     ("\t\t");
            flip_sys.append     ("\t\t");
            trig_sys.append     ("\t\t");
            lep_sys.append      ("\t\t");
            pdf_sys.append      ("\t\t");
            beff_sys.append     ("\t\t");
            met_sys.append      ("\t\t");
            jes_sys.append      ("\t\t");
            jer_sys.append      ("\t\t");
            lumi_sys.append     ("\t\t");
        }
        else
        {
            signal_header.append("\n");
            signal_obs.append   ("\n");
            rate_header.append  ("\n");
            rate_label.append   ("\n");
            rate_number.append  ("\n");
            rate.append         ("\n");
            fake_sys.append     ("\n");
            rare_sys.append     ("\n");
            flip_sys.append     ("\n");
            trig_sys.append     ("\n");
            lep_sys.append      ("\n");
            pdf_sys.append      ("\n");
            beff_sys.append     ("\n");
            met_sys.append      ("\n");
            jes_sys.append      ("\n");
            jer_sys.append      ("\n");
            lumi_sys.append     ("\n");
        }
    }


    card.append(signal_header);
    card.append(signal_obs);
    card.append(rate_header);
    card.append(rate_label);
    card.append(rate_number);
    card.append(rate);
    card.append(error_header);
    card.append(fake_sys);
    card.append(rare_sys);
    card.append(flip_sys);
    card.append(trig_sys);
    card.append(lep_sys);
    card.append(pdf_sys);
    card.append(beff_sys);
    card.append(met_sys);
    card.append(jes_sys);
    card.append(jer_sys);
    card.append(lumi_sys);
// "------------\n"
// "       bin                SR31      SR31      SR31      SR31        SR35      SR35      SR35      SR35\n"
// "   process              signal      fake      rare      flip      signal      fake      rare      flip\n"
// "   process                   0         1         2         3           0         1         2         3\n"
// "      rate              0.0511      12.41    12.81      1.41      0.0846     90.07     30.49      3.22\n"
// " ### Error Matrix\n"
//     );

    cout << card << endl;

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
