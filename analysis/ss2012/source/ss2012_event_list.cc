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

using namespace ssb;

struct event_info_t
{
    unsigned int run;
    unsigned int ls;
    unsigned int evt;
    std::string  channel;
    std::string  l1_flav;
    float        l1_pt;
    float        l1_eta;
    float        l1_phi;
    unsigned int l1_id;
    float        l1_iso;
    float        l1_d0;
    float        l1_dz;
    std::string  l2_flav;
    float        l2_pt;
    float        l2_eta;
    float        l2_phi;
    unsigned int l2_id;
    float        l2_iso;
    float        l2_d0;
    float        l2_dz;
    float        m_ll;
    float        met;
    float        ht;
    unsigned int njets;
    unsigned int nbtags;
};

struct SortByEventInfo
{
    bool operator () (const event_info_t& lhs, const event_info_t& rhs) const 
    { 
        if      (lhs.channel == "ee" && rhs.channel == "mm") {return true; }
        else if (lhs.channel == "ee" && rhs.channel == "em") {return true; }
        else if (lhs.channel == "mm" && rhs.channel == "ee") {return false;}
        else if (lhs.channel == "mm" && rhs.channel == "em") {return true; }
        else if (lhs.channel == "em" && rhs.channel == "ee") {return false;}
        else if (lhs.channel == "em" && rhs.channel == "mm") {return true; }
        else if (lhs.channel == rhs.channel)
        {
            if      (lhs.run <  rhs.run) {return true;}
            else if (lhs.run >  rhs.run) {return false;}
            else if (lhs.run == rhs.run) 
            {
                if      (lhs.ls <  rhs.ls) {return true;}
                else if (lhs.ls >  rhs.ls) {return false;}
                else if (lhs.ls == rhs.ls) 
                {
                    if      (lhs.evt <  rhs.evt) {return true;}
                    else if (lhs.evt >=  rhs.evt) {return false;}
                }
            }
        }
        return false;
    }
};

CTable EventLists
(
    TChain& chain,
    const ss::AnalysisType::value_type& anal_type              = ss::AnalysisType::high_pt,
    const ss::SignalRegion::value_type& signal_region          = ss::SignalRegion::sr0,
    const ss::SignalRegionType::value_type& signal_region_type = ss::SignalRegionType::inclusive,
    const at::DileptonChargeType::value_type& charge_type      = at::DileptonChargeType::SS
)
{
    const ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    const std::string srt_name         = ss::GetSignalRegionTypeName(signal_region_type);
    const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region, anal_type, signal_region_type);
    const std::string charge_type_name = at::GetDileptonChargeTypeName(charge_type);

    // store the events information for sorting
	vector<event_info_t> events;

    samesignbtag.Init(&chain);
    for (long entry = 0; entry != chain.GetEntries(); entry++)
    {
        // intialize event
        samesignbtag.GetEntry(entry);

        // selection
        //if (is_real_data() && not is_good_lumi())   {continue;}
        switch(charge_type)
        {
            case at::DileptonChargeType::SS: if(not is_ss()) {continue;}; break;
            case at::DileptonChargeType::SF: if(not is_sf()) {continue;}; break;
            case at::DileptonChargeType::DF: if(not is_df()) {continue;}; break;
            case at::DileptonChargeType::OS: if(not is_os()) {continue;}; break;
            default: continue;
        }
        if (!ss::PassesSignalRegion(signal_region, anal_type, signal_region_type)) {continue;}
        if (is_real_data() && not is_good_lumi()) {continue;}
        if (is_os() && dilep_type()==1)           {continue;}  // don't care about mm/OS events

        // local variables
        string channel = at::GetDileptonHypTypeName(dilep_type());
        string l1_flav = abs(lep1_pdgid()==11) ? "el" : "mu";
        string l2_flav = abs(lep2_pdgid()==11) ? "el" : "mu";

        // store the event info
        const event_info_t event_info =
        {
            run(), 
            ls(), 
            evt(), 
            channel, 
            l1_flav, 
            lep1_p4().pt(), 
            lep1_p4().eta(), 
            lep1_p4().phi(), 
            lep1_passes_id(), 
            lep1_corpfiso(), 
            10000*lep1_d0(), 
            10000*lep1_dz(), 
            l2_flav, 
            lep2_p4().pt(), 
            lep2_p4().eta(), 
            lep2_p4().phi(), 
            lep2_passes_id(), 
            lep2_corpfiso(), 
            10000*lep2_d0(), 
            10000*lep2_dz(), 
            dilep_mass(), 
            pfmet(), 
            ht(), 
            njets(), 
            nbtags(), 
        };
        events.push_back(event_info);
    }

    // sort events
    std::sort(events.begin(), events.end(), SortByEventInfo());

    // print table
    CTable list;
    list.setTitle(Form("events for %s, signal region %s, %s", at_info.title.c_str(), sr_info.name.c_str(), srt_name.c_str()));
    list.useTitle();

    size_t col = 0;
    list.setColLabel("run"     , col++);
    list.setColLabel("ls"      , col++);
    list.setColLabel("evt"     , col++);
    list.setColLabel("chan"    , col++);
    list.setColLabel("l1"      , col++);
    list.setColLabel("l1 pt"   , col++);
    list.setColLabel("l1 eta"  , col++);
    list.setColLabel("l1 phi"  , col++);
    list.setColLabel("l1 id"   , col++);
    list.setColLabel("l1 iso"  , col++);
    list.setColLabel("l1 d0"   , col++);
    list.setColLabel("l1 dz"   , col++);
    list.setColLabel("l2"      , col++);
    list.setColLabel("l2 pt"   , col++);
    list.setColLabel("l2 eta"  , col++);
    list.setColLabel("l2 phi"  , col++);
    list.setColLabel("l2 id"   , col++);
    list.setColLabel("l2 iso"  , col++);
    list.setColLabel("l2 d0"   , col++);
    list.setColLabel("l2 dz"   , col++);
    list.setColLabel("m_ll"    , col++);
    list.setColLabel("met"     , col++);
    list.setColLabel("ht"      , col++);
    list.setColLabel("njets"   , col++);
    list.setColLabel("nbjets"  , col++);

    // set the table entries
    size_t row = 0;
    for (size_t i = 0; i != events.size(); i++)
    {
        const event_info_t& event = events.at(i);

        size_t col = 0;
        list.setCell(event.run    , row, col++);
        list.setCell(event.ls     , row, col++);
        list.setCell(event.evt    , row, col++);
        list.setCell(event.channel                 , row, col++);
        list.setCell(event.l1_flav                 , row, col++);
        list.setCell(Form("%4.2f"  , event.l1_pt)  , row, col++);
        list.setCell(Form("%4.2f"  , event.l1_eta) , row, col++);
        list.setCell(Form("%4.2f"  , event.l1_phi) , row, col++);
        list.setCell(Form("%1u"    , event.l1_id)  , row, col++);
        list.setCell(Form("%4.3f"  , event.l1_iso) , row, col++);
        list.setCell(Form("%4.2f"  , event.l1_d0)  , row, col++);
        list.setCell(Form("%4.2f"  , event.l1_dz)  , row, col++);
        list.setCell(event.l2_flav                 , row, col++);
        list.setCell(Form("%4.2f"  , event.l2_pt)  , row, col++);
        list.setCell(Form("%4.2f"  , event.l2_eta) , row, col++);
        list.setCell(Form("%4.2f"  , event.l2_phi) , row, col++);
        list.setCell(Form("%1u"    , event.l2_id)  , row, col++);
        list.setCell(Form("%4.2f"  , event.l2_iso) , row, col++);
        list.setCell(Form("%4.2f"  , event.l2_d0)  , row, col++);
        list.setCell(Form("%4.2f"  , event.l2_dz)  , row, col++);
        list.setCell(Form("%4.2f"  , event.m_ll)   , row, col++);
        list.setCell(Form("%4.2f"  , event.met)    , row, col++);
        list.setCell(Form("%4.2f"  , event.ht)     , row, col++);
        list.setCell(Form("%1u"    , event.njets)  , row, col++);
        list.setCell(Form("%1u"    , event.nbtags) , row, col++);
        row++;
    }
    return list;
}


CTable EventCounts
(
    TChain& chain,
    const ss::AnalysisType::value_type& anal_type              = ss::AnalysisType::high_pt,
    const ss::SignalRegion::value_type& signal_region          = ss::SignalRegion::sr0,
    const ss::SignalRegionType::value_type& signal_region_type = ss::SignalRegionType::inclusive
)
{
    const ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    const std::string srt_name         = ss::GetSignalRegionTypeName(signal_region_type);
    const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region, anal_type, signal_region_type);

    // yields         ee,  mm,  em,  ll
    float y_ss[4] = {0.0, 0.0, 0.0, 0.0};
    float y_sf[4] = {0.0, 0.0, 0.0, 0.0};
    float y_df[4] = {0.0, 0.0, 0.0, 0.0};
    float y_os[4] = {0.0, 0.0, 0.0, 0.0};

    samesignbtag.Init(&chain);
    for (long entry = 0; entry != chain.GetEntries(); entry++)
    {
        // intialize event
        samesignbtag.GetEntry(entry);
        
        //cout << Form("run: %d, ls: %d, event: %d", run(), ls(), evt()) << endl;

        // selection
        if (!ss::PassesSignalRegion(signal_region, anal_type, signal_region_type)) {continue;}
        if (is_real_data() && not is_good_lumi()) {continue;}
        if (is_os() && dilep_type()==1)           {continue;}

        // fill counts
        if (is_ss()) 
        {
            if (dilep_type()==3) {y_ss[0]++;}
            if (dilep_type()==1) {y_ss[1]++;}
            if (dilep_type()==2) {y_ss[2]++;}
            y_ss[3]++;
        }
        if (is_sf()) 
        {
            if (dilep_type()==3) {y_sf[0]++;}
            if (dilep_type()==1) {y_sf[1]++;}
            if (dilep_type()==2) {y_sf[2]++;}
            y_sf[3]++;
        }
        if (is_df()) 
        {
            if (dilep_type()==3) {y_df[0]++;}
            if (dilep_type()==1) {y_df[1]++;}
            if (dilep_type()==2) {y_df[2]++;}
            y_df[3]++;
        }
        if (is_os()) 
        {
            if (dilep_type()==3) {y_os[0]++;}
            if (dilep_type()==1) {y_os[1]++;}
            if (dilep_type()==2) {y_os[2]++;}
            y_os[3]++;
        }
    }

    // print tables
    CTable t1;
    t1.setTitle(Form("yields for %s, signal region %s, %s", at_info.title.c_str(), sr_info.name.c_str(), srt_name.c_str()));
    t1.useTitle();
    t1.setTable() (         "ee",    "mm",    "em",    "ll")
                  ("SS", y_ss[0], y_ss[1], y_ss[2], y_ss[3])
                  ("SF", y_sf[0], y_sf[1], y_sf[2], y_sf[3])
                  ("DF", y_df[0], y_df[1], y_df[2], y_df[3])
                  ("OS", y_os[0], "NA"   , y_os[2], y_os[3]);
    return t1;  
}

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    // parameters
    std::string sample_name             = "data";
    std::string analysis_type_name      = "high_pt";
    std::string signal_region_name      = "sr0";
    std::string signal_region_type_name = "inclusive";
    std::string input_file              = "";
    std::string output_file             = "";
    std::string charge_option           = "ss";
    bool print_list                     = true;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("sample"    , po::value<std::string>(&sample_name)             , "sample to run on (from at/Samples.h)"                    )
        ("input"    , po::value<std::string>(&input_file)               , "name of input root file (optional)"                      )
        ("output"    , po::value<std::string>(&output_file)             , "output file name for lists (blank means print to screen)")
        ("sr"        , po::value<std::string>(&signal_region_name)      , "signal region number (default is 0)"                     )
        ("sr_type"   , po::value<std::string>(&signal_region_type_name) , "signal region type (default is inclusive)"               )
        ("anal_type" , po::value<std::string>(&analysis_type_name)      , "name of input sample (from at/AnalysisType.h)"           )
        ("charge"    , po::value<std::string>(&charge_option)           , "charge option (ss, sf, df, os, all)"                     )
        ("print_list", po::value<bool>(&print_list)                     , "print the event lists (default is true)"                 )

        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) 
    {
        cout << desc << "\n";
        return 1;
    }

    // ensure lower case
    charge_option = rt::string_lower(charge_option);

    // check that input file exists and is specified
    if (!input_file.empty())
    { 
        if (!rt::exists(input_file))
        {
            cout << "[ss2012_event_list]: input file " << input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // do it
    // -------------------------------------------------------------------------------------------------//

    const ss::AnalysisType::value_type at      = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type srt = ss::GetSignalRegionTypeFromName(signal_region_type_name);
    const ss::SignalRegion::value_type sr      = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);

    // write output
    if (not output_file.empty())
    {
        rt::mkdir(rt::dirname(output_file), /*force=*/true);    
    }
    else
    {
        cout << "[ss2012_event_list]: no output file given.  printing to stdout" << endl;
    }
    ostream* out_ptr = output_file.empty() ? &cout : new fstream(output_file.c_str(), fstream::out);
    ostream& out = *out_ptr;

    // get the chain
    at::Sample::value_type sample = at::GetSampleFromName(sample_name);
    at::SampleInfo sample_info    = at::GetSampleInfo(sample);
    TChain chain("tree"); 
    if (not input_file.empty())
    {
        chain.Add(input_file.c_str());
    }
    else
    {
        chain.Add(Form("babies/%s/%s.root", ss::GetAnalysisTypeInfo(at).short_name.c_str(), sample_info.name.c_str()));
    }

    CTable counts   = EventCounts(chain, at, sr, srt);
    out << "total yields:\n" << counts << endl; 
    if (print_list)
    {
        if (charge_option == "all" or charge_option =="ss")
        {
            CTable ss_lists = EventLists (chain, at, sr, srt, at::DileptonChargeType::SS);
            out << "printing SS events:\n" << ss_lists << endl;
        }
        if (charge_option == "all" or charge_option =="sf")
        {
            CTable sf_lists = EventLists (chain, at, sr, srt, at::DileptonChargeType::SF);
            out << "printing SF events:\n" << sf_lists << endl;
        }
        if (charge_option == "all" or charge_option =="ds")
        {
            CTable df_lists = EventLists (chain, at, sr, srt, at::DileptonChargeType::DF);
            out << "printing DF events:\n" << df_lists << endl;
        }
        if (charge_option == "all" or charge_option =="os")
        {
            CTable os_lists = EventLists (chain, at, sr, srt, at::DileptonChargeType::OS);
            out << "printing OS events:\n" << os_lists << endl;
        }
    }

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
