#include <iostream>
#include <fstream>
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
    float stat_unc;
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

const float GetValueFromScanHist(TH1* const hist, const float sparm0, const float sparm1)
{
    TH2* const h2 = dynamic_cast<TH2*>(hist);
    return rt::GetBinContent2D(h2, sparm0, sparm1);
}

struct yield_info_t
{
    // mebers:
    unsigned int sr_num;
    unsigned int yield;
    float pred;
    float pred_unc;
    float fake;
    float fake_unc;
    float rare;
    float rare_unc;
    float flip;
    float flip_unc;

    // methods:
    friend std::istream& operator >> (std::istream& in, yield_info_t& yi);
};

std::istream& operator >> (std::istream& in, yield_info_t& yi)
{
    in >> yi.sr_num;
    in >> yi.yield;
    in >> yi.pred;
    in >> yi.pred_unc;
    in >> yi.fake;
    in >> yi.fake_unc;
    in >> yi.rare;
    in >> yi.rare_unc;
    in >> yi.flip;
    in >> yi.flip_unc;
    return in;
};

struct CompareSR
{
    CompareSR(const int sr_num) : m_sr_num(sr_num) {}
    bool operator () (const yield_info_t& yi) {return (yi.sr_num==m_sr_num);}
    const int m_sr_num;
};

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
    std::string output_file         = "";
    std::string syst_file           = "";
    std::string yield_file          = "";
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_17Apr2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02222013.root";
    std::string analysis_type_name  = "high_pt";
    std::string sr_string           = "-1";
    bool exclusive                  = true;
    float ngen_sf                   = 1.0;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.3;
    float rare_sys_unc              = 0.5;
    float lumi                      = 1.0;
    bool verbose                    = false;
    float sparm0                    = -999999.0;
    float sparm1                    = -999999.0;
    float sparm2                    = -999999.0;
    float sparm3                    = -999999.0;
    int run                         = -1;
    int ls                          = -1;
    int event                       = -1;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("syst"      , po::value<std::string>(&syst_file)->required()  , "REQUIRED: file containting systematics"                                         )
        ("yield"     , po::value<std::string>(&yield_file)->required() , "REQUIRED: file to get the yields and predictions"                               )
        ("output"    , po::value<std::string>(&output_file)            , "name of output root file"                                                       )
        ("anal_type" , po::value<std::string>(&analysis_type_name)     , "name of analysis type (from AnalysisType.h)"                                    )
        ("fr_file"   , po::value<std::string>(&fake_rate_file_name)    , Form("fake rate file name (default: %s)", fake_rate_file_name.c_str())           )
        ("fl_file"   , po::value<std::string>(&flip_rate_file_name)    , Form("flip rate file name (default: %s)", flip_rate_file_name.c_str())           )
        ("sr"        , po::value<std::string>(&sr_string)              , "comma seperated list of SRs to run on (any < 0 means all -- default)"           )
        ("ngen_sf"   , po::value<float>(&ngen_sf)                      , Form("scale factor for the # generated events (default is %f)", ngen_sf)         )
        ("fr_unc"    , po::value<float>(&fake_sys_unc)                 , Form("systematic uncertainty for fake prediction (default is %f)", fake_sys_unc) )
        ("fr_unc"    , po::value<float>(&fake_sys_unc)                 , Form("systematic uncertainty for fake prediction (default is %f)", fake_sys_unc) )
        ("fl_unc"    , po::value<float>(&flip_sys_unc)                 , Form("systematic uncertainty for flip prediction (default is %f)", flip_sys_unc) )
        ("rare_unc"  , po::value<float>(&rare_sys_unc)                 , Form("systematic uncertainty for MC prediction (default is %f)", rare_sys_unc)   )
        ("sparm0"    , po::value<float>(&sparm0)                       , "sparm0 is required to be this value"                                            )
        ("sparm1"    , po::value<float>(&sparm1)                       , "sparm1 is required to be this value"                                            )
        ("sparm2"    , po::value<float>(&sparm2)                       , "sparm2 is required to be this value"                                            )
        ("sparm3"    , po::value<float>(&sparm3)                       , "sparm3 is required to be this value"                                            )
        ("lumi"      , po::value<float>(&lumi)                         , "luminosity"                                                                     )
        ("excl"      , po::value<bool>(&exclusive)                     , "use exclusive signal region"                                                    )
        ("verbose"   , po::value<bool>(&verbose)                       , "verbosity"                                                                      )
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
        cout << "output_file         :\t" << output_file         << endl;
        cout << "syst_file           :\t" << syst_file           << endl;
        cout << "analysis_type_name  :\t" << analysis_type_name  << endl;
        cout << "fake_rate_file_name :\t" << fake_rate_file_name << endl;
        cout << "flip_rate_file_name :\t" << flip_rate_file_name << endl;
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
        cout << "sparm0              :\t" << sparm0              << endl;
        cout << "sparm1              :\t" << sparm1              << endl;
        cout << "sparm2              :\t" << sparm2              << endl;
        cout << "sparm3              :\t" << sparm3              << endl;
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

    // check that input file exists and is specified
    if (yield_file.empty())
    { 
        cout << "[ss2012_create_card] ERROR: yield/pred file " << yield_file << " not specified" << endl;
        cout << desc << "\n";
        return 1;
    }
    else 
    { 
        if (!rt::exists(syst_file))
        {
            cout << "[ss2012_create_card] ERROR: yield/pred file " << yield_file << " not found" << endl;
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

    // use pred file if yield type isn't empty
    vector<yield_info_t> yield_infos;
    if (not yield_file.empty())
    {
        std::ifstream fin;
        fin.open(yield_file.c_str(), std::ifstream::in);
        while (fin.good())
        {
            yield_info_t yield_info;
            fin >> yield_info;
            yield_infos.push_back(yield_info);
        }
    }

    // info 
    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = (exclusive ? SignalRegionType::exclusive : SignalRegionType::inclusive);
    const std::string signal_region_type_name                 = GetSignalRegionTypeName(signal_region_type);

    vector<card_info_t> card_infos;
    for (size_t i = 0; i != sr_nums.size(); i++)
    {
        const std::string signal_region_name = Form("sr%d", sr_nums.at(i));
        const ss::SignalRegion::value_type signal_region = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);
        const ss::SignalRegionInfo sr_info               = ss::GetSignalRegionInfo(signal_region, analysis_type, signal_region_type);

        // info object
        card_info_t info;
        yield_info_t yi = *std::find_if(yield_infos.begin(), yield_infos.end(), CompareSR(sr_nums.at(i)));

        // make the card
        info.signal_name = rt::string_upper(signal_region_name);
        info.obs         = yi.yield;
        info.fake        = yi.fake;
        info.fake_unc    = 1.0 + yi.fake_unc/yi.fake;
        info.flip        = yi.flip;
        info.flip_unc    = 1.0 + yi.flip_unc/yi.flip;
        info.rare        = yi.rare;
        info.rare_unc    = 1.0 + yi.rare_unc/yi.rare;

        // systematics (percentage) 
        const std::string sr = GetSRLabel(signal_region);
        rt::TH1Container hc(syst_file);
        //hc.List();

        info.trig_unc    = 1.06;
        info.pdf_unc     = 1.02;
        info.lumi_unc    = 1.044;
        info.acc         = lumi*GetValueFromScanHist(hc[sr+"effNormNice"], sparm0, sparm1);
        info.jer_unc     = GetValueFromScanHist(hc[sr+"effErrJER"  ], sparm0, sparm1);
        info.jes_up_unc  = GetValueFromScanHist(hc[sr+"effErrJESUP"], sparm0, sparm1);
        info.jes_dn_unc  = GetValueFromScanHist(hc[sr+"effErrJESDN"], sparm0, sparm1);
        info.met_up_unc  = GetValueFromScanHist(hc[sr+"effErrMETUP"], sparm0, sparm1);
        info.met_dn_unc  = GetValueFromScanHist(hc[sr+"effErrMETDN"], sparm0, sparm1);
        info.beff_up_unc = GetValueFromScanHist(hc[sr+"effErrBTAUP"], sparm0, sparm1);
        info.beff_dn_unc = GetValueFromScanHist(hc[sr+"effErrBTADN"], sparm0, sparm1);
        info.lep_unc     = 1.0 + GetValueFromScanHist(hc[sr+"leptonSystematic"], sparm0, sparm1);
        info.stat_unc    = 1.0 + GetValueFromScanHist(hc[sr+"effErrStat" ], sparm0, sparm1);
        card_infos.push_back(info);
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
    string stat_sys      = "Stat             lnN\t";
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
        stat_sys.append(Form("%1.3f\t\t-\t\t-\t\t-"    , card_infos.at(i).stat_unc));
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
            stat_sys.append     ("\t\t");
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
            stat_sys.append     ("\t\t");
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
    card.append(stat_sys);

    // print it
    if (output_file.empty())
    {
        cout << card << endl;
    }
    else
    {
        rt::mkdir(rt::dirname(output_file), /*force=*/true);
        std::ofstream out(output_file.c_str(), std::ofstream::out);
        out << card << endl;
        out.close();
    }

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
