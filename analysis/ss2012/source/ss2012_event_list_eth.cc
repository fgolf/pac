#include "rt/RootTools.h"
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
    unsigned int tlcat;
    float ht;
    float met;
};

struct SortByEventInfo
{
    bool operator () (const event_info_t& lhs, const event_info_t& rhs) const 
    { 
        if      (lhs.tlcat <  rhs.tlcat) {return true;}
        else if (lhs.tlcat >  rhs.tlcat) {return false;}
        else if (lhs.tlcat == rhs.tlcat) 
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
                    else if (lhs.evt >  rhs.evt) {return false;}
                    else if (lhs.evt == rhs.evt) 
                    {
                        return false;
                        //throw std::runtime_error("SortByEventInfo: two events with same run/ls/evt");
                    }
                }
            }
        }
        return false;
    }
};

CTable EventListsETH
(
    const ss::AnalysisType::value_type& anal_type              = ss::AnalysisType::high_pt,
    const ss::SignalRegion::value_type& signal_region          = ss::SignalRegion::sr0,
    const ss::SignalRegionType::value_type& signal_region_type = ss::SignalRegionType::inclusive
)
{
    const ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    const std::string srt_name         = ss::GetSignalRegionTypeName(signal_region_type);
    const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region, anal_type, signal_region_type);

    TChain chain("tree"); 
    chain.Add(Form("babies/%s/data.root", at_info.short_name.c_str()));

    //Run:LS:Event:TLcat:HT:MET
    //Where TLcat denotes the following:
    //TLcat == 0 for both tight leptons (i.e. the signal events)
    //TLcat == 1 for one tight, one loose lepton in case of same flavour. in case of emu events, this is tight muon, loose electron
    //TLcat == 2 doesn't exist for same flavour events, and is tight electron, loose muon for emu events
    //TLcat == 3 for both loose leptons.
    vector<event_info_t> events;

    samesignbtag.Init(&chain);
    size_t row = 0;
    for (long entry = 0; entry != chain.GetEntries(); entry++)
    {
        // intialize event
        samesignbtag.GetEntry(entry);

        // selection
        if (ssb::is_real_data() && not ssb::is_good_lumi())                        {continue;}
        if (!ss::PassesSignalRegion(signal_region, anal_type, signal_region_type)) {continue;}
        if (ssb::ht()<200)                                                         {continue;} // for sync with UFL
        if (ssb::is_os())                                                          {continue;}
        if (ssb::dilep_type()==4)                                                  {continue;}

        // category
        unsigned int tlcat = 99999;
        if      (ssb::is_ss()) {tlcat = 0;}
        if      (ssb::is_df()) {tlcat = 3;}
        else if (ssb::is_sf()) 
        {
            if      (ssb::ee()) {tlcat = 1;}
            else if (ssb::mm()) {tlcat = 1;}
            else if (ssb::em()) 
            {
                if      (abs(ssb::lep1_pdgid())==13 && ssb::lep1_is_num()) {tlcat = 1;}
                else if (abs(ssb::lep2_pdgid())==13 && ssb::lep2_is_num()) {tlcat = 1;}
                else if (abs(ssb::lep1_pdgid())==11 && ssb::lep1_is_num()) {tlcat = 2;}
                else if (abs(ssb::lep2_pdgid())==11 && ssb::lep2_is_num()) {tlcat = 2;}
            }
        }

        event_info_t event_info = {ssb::run(), ssb::ls(), ssb::evt(), tlcat, ssb::ht(), ssb::pfmet()};
        events.push_back(event_info);
    }

    // sort
    std::sort(events.begin(), events.end(), SortByEventInfo());

    // print table
    CTable list;
    list.setTitle(Form("events for %s, signal region %s, %s", at_info.title.c_str(), sr_info.name.c_str(), srt_name.c_str()));
    list.useTitle();

    size_t col = 0;
    list.setColLabel("Run"  , col++);
    list.setColLabel("LS"   , col++);
    list.setColLabel("Event", col++);
    list.setColLabel("TLcat", col++);
    list.setColLabel("MET"  , col++);
    list.setColLabel("HT"   , col++);

    for (size_t i = 0; i != events.size(); i++)
    {
        const std::string run   = Form("%6u"   , events.at(i).run  ); 
        const std::string ls    = Form("%5u"   , events.at(i).ls   ); 
        const std::string event = Form("%15u"  , events.at(i).evt  ); 
        const std::string tlcat = Form("%1u"   , events.at(i).tlcat); 
        const std::string ht    = Form("%4.3f" , events.at(i).ht   ); 
        const std::string met   = Form("%4.3f" , events.at(i).met  ); 

        // set the lists
        size_t col = 0;
        //list.setRowLabel(Form("entry: %ld", i), row);
        list.setCell(run   , row , col++);
        list.setCell(ls    , row , col++);
        list.setCell(event , row , col++);
        list.setCell(tlcat , row , col++);
        list.setCell(ht    , row , col++);
        list.setCell(met   , row , col++);
        row++;
    }
    return list;
}

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    // parameters
    std::string analysis_type_name      = "high_pt";
    std::string signal_region_name      = "sr0";
    std::string signal_region_type_name = "exclusive";
    std::string output_name             = "";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("anal_type", po::value<std::string>(&analysis_type_name)      , "name of input sample (from at/AnalysisType.h)"           )
        ("output"   , po::value<std::string>(&output_name)             , "output file name for lists (blank means print to screen)")
        ("sr"       , po::value<std::string>(&signal_region_name)      , "signal region number (default is 0)"                     )
        ("sr_type"  , po::value<std::string>(&signal_region_type_name) , "\"exclusive\" or \"inclusive\""                          )
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) 
    {
        cout << desc << "\n";
        return 1;
    }

    // do it
    // -------------------------------------------------------------------------------------------------//

    const ss::AnalysisType::value_type at      = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type srt = ss::GetSignalRegionTypeFromName(signal_region_type_name);
    const ss::SignalRegion::value_type sr      = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);

    // write output
    if (not output_name.empty())
    {
        rt::mkdir(rt::dirname(output_name), /*force=*/true);    
    }
    else
    {
        cout << "[ss2012_event_list]: no output file given.  printing to stdout" << endl;
    }
    ostream* out_ptr = output_name.empty() ? &cout : new fstream(output_name.c_str(), fstream::out);
    ostream& out = *out_ptr;

    CTable eth_lists = EventListsETH(at, sr, srt);
    out << eth_lists << endl;

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
