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

CTable EventLists
(
    const std::string& output_name = "",
    const ss::AnalysisType::value_type& anal_type         = ss::AnalysisType::high_pt,
    const ss::SignalRegion::value_type& signal_region     = ss::SignalRegion::sr0,
    const at::DileptonChargeType::value_type& charge_type = at::DileptonChargeType::SS
)
{
    ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region);
    TChain chain("tree"); 
    //chain.Add(Form("babies/%s/data.root", at_info.short_name.c_str()));
    chain.Add("output/alex_sync.root");

    CTable list;
    list.setTitle(Form("SS events for %s, signal region %s", at_info.title.c_str(), sr_info.name.c_str()));
    list.useTitle();

    size_t col = 0;
    list.setColLabel("run"     , col++);
    list.setColLabel("ls"      , col++);
    list.setColLabel("evt"     , col++);
    list.setColLabel("chan"    , col++);
    list.setColLabel("l1 flav" , col++);
    list.setColLabel("l1 pt"   , col++);
    list.setColLabel("l1 eta"  , col++);
    list.setColLabel("l1 phi"  , col++);
    list.setColLabel("l1 id"   , col++);
    list.setColLabel("l1 iso"  , col++);
    list.setColLabel("l2 flav" , col++);
    list.setColLabel("l2 pt"   , col++);
    list.setColLabel("l2 eta"  , col++);
    list.setColLabel("l2 phi"  , col++);
    list.setColLabel("l2 id"   , col++);
    list.setColLabel("l2 iso"  , col++);
    list.setColLabel("m_ll"    , col++);
    list.setColLabel("met"     , col++);
    list.setColLabel("ht"      , col++);
    list.setColLabel("njets"   , col++);
    list.setColLabel("nbjets"  , col++);

    samesignbtag.Init(&chain);
    size_t row = 0;
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
        if (!ss::PassesSignalRegion(signal_region)) {continue;}
        //if (is_real_data() && not is_good_lumi()) {continue;}
        if (is_os() && dilep_type()==1)           {continue;}

        // local variables
        string channel = at::GetDileptonHypTypeName(dilep_type());
        string l1_name = abs(lep1_pdgid()==11) ? "el" : "mu";
        string l2_name = abs(lep2_pdgid()==11) ? "el" : "mu";


        // set the lists
        size_t col = 0;
        list.setRowLabel(Form("entry: %ld", entry), row);
        list.setCell(run()            , row, col++);
        list.setCell(ls()             , row, col++);
        list.setCell(evt()            , row, col++);
        list.setCell(channel          , row, col++);
        list.setCell(l1_name          , row, col++);
        list.setCell(lep1_p4().pt()   , row, col++);
        list.setCell(lep1_p4().eta()  , row, col++);
        list.setCell(lep1_p4().phi()  , row, col++);
        list.setCell(lep1_passes_id() , row, col++);
        list.setCell(lep1_corpfiso()  , row, col++);
        list.setCell(l2_name          , row, col++);
        list.setCell(lep2_p4().pt()   , row, col++);
        list.setCell(lep2_p4().eta()  , row, col++);
        list.setCell(lep2_p4().phi()  , row, col++);
        list.setCell(lep2_passes_id() , row, col++);
        list.setCell(lep2_corpfiso()  , row, col++);
        list.setCell(dilep_mass()     , row, col++);
        list.setCell(pfmet()          , row, col++);
        list.setCell(ht()             , row, col++);
        list.setCell(njets()          , row, col++);
        list.setCell(nbtags()         , row, col++);
        row++;
    }
    return list;
}


CTable EventCounts
(
    const ss::AnalysisType::value_type& anal_type     = ss::AnalysisType::high_pt,
    const ss::SignalRegion::value_type& signal_region = ss::SignalRegion::sr0
)
{
    ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region);
    TChain chain("tree"); 
    //chain.Add(Form("babies/%s/data.root", at_info.short_name.c_str()));
    chain.Add("output/alex_sync.root");
    //ss::SetSignalRegionAliases(chain);
    //cout << chain.GetEntries() << endl;


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
        if (!ss::PassesSignalRegion(signal_region)) {continue;}
        //if (is_real_data() && not is_good_lumi())   {continue;}
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
    t1.setTitle(Form("yields for %s, signal region %s", at_info.title.c_str(), sr_info.name.c_str()));
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
    std::string analysis_type_name  = "high_pt";
    unsigned int signal_region_num  = 0;
    std::string output_name         = "";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("anal_type", po::value<std::string>(&analysis_type_name) , "name of input sample (from at/AnalysisType.h)"           )
        ("output"   , po::value<std::string>(&output_name)        , "output file name for lists (blank means print to screen)")
        ("sr"       , po::value<unsigned int>(&signal_region_num) , "signal region number (default is 0)"                     )
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

    const string signal_region_name = Form("sr%d", signal_region_num);
    ss::SignalRegion::value_type sr = ss::GetSignalRegionFromName(signal_region_name);
    ss::AnalysisType::value_type at = ss::GetAnalysisTypeFromName(analysis_type_name);

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

    CTable counts =  EventCounts(at, sr);
    CTable ss_lists = EventLists(output_name, at, sr, at::DileptonChargeType::SS);
    CTable sf_lists = EventLists(output_name, at, sr, at::DileptonChargeType::SF);
    CTable df_lists = EventLists(output_name, at, sr, at::DileptonChargeType::DF);
    CTable os_lists = EventLists(output_name, at, sr, at::DileptonChargeType::OS);
    out << "total yields:\n" << counts << endl; 
    out << "printing SS events:\n" << ss_lists << endl;
    out << "printing SF events:\n" << sf_lists << endl;
    out << "printing DF events:\n" << df_lists << endl;
    out << "printing OS events:\n" << os_lists << endl;
    
    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
