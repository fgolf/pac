#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "AnalysisType.h"
#include "CTable.h"


struct yield_t
{
    int ee;
    int mm;
    int em;
    int ll;
};

void SSQuickYields(const std::string& srt_name = "inclusive")
{
    // chains
    TChain ch_hpt("tree"); ch_hpt.Add("babies/hpt/data.root");
    TChain ch_lpt("tree"); ch_lpt.Add("babies/lpt/data.root");
    TChain ch_vpt("tree"); ch_vpt.Add("babies/vpt/data.root");

	const ss::SignalRegionType::value_type srt = ss::GetSignalRegionTypeFromName(srt_name);

    // aliases
    ss::SetSignalRegionAliases(ch_hpt, ss::AnalysisType::high_pt);
    ss::SetSignalRegionAliases(ch_lpt, ss::AnalysisType::low_pt);
    ss::SetSignalRegionAliases(ch_vpt, ss::AnalysisType::vlow_pt);
    
    // selection
    const TCut ss = "is_ss && trig && lep_pt";
    const TCut ee = "ee";
    const TCut mm = "mm";
    const TCut em = "em";

	const bool is_incl = (srt == ss::SignalRegionType::inclusive);
    
    const TCut sr0  = (is_incl ? "sr0"  : "ex_sr0" );
    const TCut sr1  = (is_incl ? "sr1"  : "ex_sr1" );
    const TCut sr2  = (is_incl ? "sr2"  : "ex_sr2" );
    const TCut sr3  = (is_incl ? "sr3"  : "ex_sr3" );
    const TCut sr4  = (is_incl ? "sr4"  : "ex_sr4" );
    const TCut sr5  = (is_incl ? "sr5"  : "ex_sr5" );
    const TCut sr6  = (is_incl ? "sr6"  : "ex_sr6" );
    const TCut sr7  = (is_incl ? "sr7"  : "ex_sr7" );
    const TCut sr8  = (is_incl ? "sr8"  : "ex_sr8" );
    const TCut sr9  = (is_incl ? "sr9"  : "ex_sr9" );
    const TCut sr10 = (is_incl ? "sr10" : "ex_sr10");
    const TCut sr11 = (is_incl ? "sr11" : "ex_sr11");
    const TCut sr12 = (is_incl ? "sr12" : "ex_sr12");
    const TCut sr13 = (is_incl ? "sr13" : "ex_sr13");
    const TCut sr14 = (is_incl ? "sr14" : "ex_sr14");
    const TCut sr15 = (is_incl ? "sr15" : "ex_sr15");
    const TCut sr16 = (is_incl ? "sr16" : "ex_sr16");
    const TCut sr17 = (is_incl ? "sr17" : "ex_sr17");
    const TCut sr18 = (is_incl ? "sr18" : "ex_sr18");
    const TCut sr19 = (is_incl ? "sr19" : "ex_sr19");
    const TCut sr20 = (is_incl ? "sr20" : "ex_sr20");
    const TCut sr21 = (is_incl ? "sr21" : "ex_sr21");
    const TCut sr22 = (is_incl ? "sr22" : "ex_sr22");
    const TCut sr23 = (is_incl ? "sr23" : "ex_sr23");
    const TCut sr24 = (is_incl ? "sr24" : "ex_sr24");
    const TCut sr25 = (is_incl ? "sr25" : "ex_sr25");
    const TCut sr26 = (is_incl ? "sr26" : "ex_sr26");
    const TCut sr27 = (is_incl ? "sr27" : "ex_sr27");
    const TCut sr28 = (is_incl ? "sr28" : "ex_sr28");
    
    // high pT
    const yield_t y_hpt[29] = 
    {
        {ch_hpt.GetEntries(ss && ee && sr0 ), ch_hpt.GetEntries(ss && mm && sr0 ), ch_hpt.GetEntries(ss && em && sr0 ), ch_hpt.GetEntries(ss && sr0 )},
        {ch_hpt.GetEntries(ss && ee && sr1 ), ch_hpt.GetEntries(ss && mm && sr1 ), ch_hpt.GetEntries(ss && em && sr1 ), ch_hpt.GetEntries(ss && sr1 )},
        {ch_hpt.GetEntries(ss && ee && sr2 ), ch_hpt.GetEntries(ss && mm && sr2 ), ch_hpt.GetEntries(ss && em && sr2 ), ch_hpt.GetEntries(ss && sr2 )},
        {ch_hpt.GetEntries(ss && ee && sr3 ), ch_hpt.GetEntries(ss && mm && sr3 ), ch_hpt.GetEntries(ss && em && sr3 ), ch_hpt.GetEntries(ss && sr3 )},
        {ch_hpt.GetEntries(ss && ee && sr4 ), ch_hpt.GetEntries(ss && mm && sr4 ), ch_hpt.GetEntries(ss && em && sr4 ), ch_hpt.GetEntries(ss && sr4 )},
        {ch_hpt.GetEntries(ss && ee && sr5 ), ch_hpt.GetEntries(ss && mm && sr5 ), ch_hpt.GetEntries(ss && em && sr5 ), ch_hpt.GetEntries(ss && sr5 )},
        {ch_hpt.GetEntries(ss && ee && sr6 ), ch_hpt.GetEntries(ss && mm && sr6 ), ch_hpt.GetEntries(ss && em && sr6 ), ch_hpt.GetEntries(ss && sr6 )},
        {ch_hpt.GetEntries(ss && ee && sr7 ), ch_hpt.GetEntries(ss && mm && sr7 ), ch_hpt.GetEntries(ss && em && sr7 ), ch_hpt.GetEntries(ss && sr7 )},
        {ch_hpt.GetEntries(ss && ee && sr8 ), ch_hpt.GetEntries(ss && mm && sr8 ), ch_hpt.GetEntries(ss && em && sr8 ), ch_hpt.GetEntries(ss && sr8 )},
        {ch_hpt.GetEntries(ss && ee && sr9 ), ch_hpt.GetEntries(ss && mm && sr9 ), ch_hpt.GetEntries(ss && em && sr9 ), ch_hpt.GetEntries(ss && sr9 )},
        {ch_hpt.GetEntries(ss && ee && sr10), ch_hpt.GetEntries(ss && mm && sr10), ch_hpt.GetEntries(ss && em && sr10), ch_hpt.GetEntries(ss && sr10)},
        {ch_hpt.GetEntries(ss && ee && sr11), ch_hpt.GetEntries(ss && mm && sr11), ch_hpt.GetEntries(ss && em && sr11), ch_hpt.GetEntries(ss && sr11)},
        {ch_hpt.GetEntries(ss && ee && sr12), ch_hpt.GetEntries(ss && mm && sr12), ch_hpt.GetEntries(ss && em && sr12), ch_hpt.GetEntries(ss && sr12)},
        {ch_hpt.GetEntries(ss && ee && sr13), ch_hpt.GetEntries(ss && mm && sr13), ch_hpt.GetEntries(ss && em && sr13), ch_hpt.GetEntries(ss && sr13)},
        {ch_hpt.GetEntries(ss && ee && sr14), ch_hpt.GetEntries(ss && mm && sr14), ch_hpt.GetEntries(ss && em && sr14), ch_hpt.GetEntries(ss && sr14)},
        {ch_hpt.GetEntries(ss && ee && sr15), ch_hpt.GetEntries(ss && mm && sr15), ch_hpt.GetEntries(ss && em && sr15), ch_hpt.GetEntries(ss && sr15)},
        {ch_hpt.GetEntries(ss && ee && sr16), ch_hpt.GetEntries(ss && mm && sr16), ch_hpt.GetEntries(ss && em && sr16), ch_hpt.GetEntries(ss && sr16)},
        {ch_hpt.GetEntries(ss && ee && sr17), ch_hpt.GetEntries(ss && mm && sr17), ch_hpt.GetEntries(ss && em && sr17), ch_hpt.GetEntries(ss && sr17)},
        {ch_hpt.GetEntries(ss && ee && sr18), ch_hpt.GetEntries(ss && mm && sr18), ch_hpt.GetEntries(ss && em && sr18), ch_hpt.GetEntries(ss && sr18)},
        {ch_hpt.GetEntries(ss && ee && sr19), ch_hpt.GetEntries(ss && mm && sr19), ch_hpt.GetEntries(ss && em && sr19), ch_hpt.GetEntries(ss && sr19)},
        {ch_hpt.GetEntries(ss && ee && sr20), ch_hpt.GetEntries(ss && mm && sr20), ch_hpt.GetEntries(ss && em && sr20), ch_hpt.GetEntries(ss && sr20)},
        {ch_hpt.GetEntries(ss && ee && sr21), ch_hpt.GetEntries(ss && mm && sr21), ch_hpt.GetEntries(ss && em && sr21), ch_hpt.GetEntries(ss && sr21)},
        {ch_hpt.GetEntries(ss && ee && sr22), ch_hpt.GetEntries(ss && mm && sr22), ch_hpt.GetEntries(ss && em && sr22), ch_hpt.GetEntries(ss && sr22)},
        {ch_hpt.GetEntries(ss && ee && sr23), ch_hpt.GetEntries(ss && mm && sr23), ch_hpt.GetEntries(ss && em && sr23), ch_hpt.GetEntries(ss && sr23)},
        {ch_hpt.GetEntries(ss && ee && sr24), ch_hpt.GetEntries(ss && mm && sr24), ch_hpt.GetEntries(ss && em && sr24), ch_hpt.GetEntries(ss && sr24)},
        {ch_hpt.GetEntries(ss && ee && sr25), ch_hpt.GetEntries(ss && mm && sr25), ch_hpt.GetEntries(ss && em && sr25), ch_hpt.GetEntries(ss && sr25)},
        {ch_hpt.GetEntries(ss && ee && sr26), ch_hpt.GetEntries(ss && mm && sr26), ch_hpt.GetEntries(ss && em && sr26), ch_hpt.GetEntries(ss && sr26)},
        {ch_hpt.GetEntries(ss && ee && sr27), ch_hpt.GetEntries(ss && mm && sr27), ch_hpt.GetEntries(ss && em && sr27), ch_hpt.GetEntries(ss && sr27)},
        {ch_hpt.GetEntries(ss && ee && sr28), ch_hpt.GetEntries(ss && mm && sr28), ch_hpt.GetEntries(ss && em && sr28), ch_hpt.GetEntries(ss && sr28)}
    };

    CTable t_hpt;
    t_hpt.useTitle();
    t_hpt.setTitle("high pT yields");
    t_hpt.setTable()(               "ee",         "mm",         "em",         "ll")
                    ("sr0" , y_hpt[0 ].ee, y_hpt[0 ].mm, y_hpt[0 ].em, y_hpt[0 ].ll)
                    ("sr1" , y_hpt[1 ].ee, y_hpt[1 ].mm, y_hpt[1 ].em, y_hpt[1 ].ll)
                    ("sr2" , y_hpt[2 ].ee, y_hpt[2 ].mm, y_hpt[2 ].em, y_hpt[2 ].ll)
                    ("sr3" , y_hpt[3 ].ee, y_hpt[3 ].mm, y_hpt[3 ].em, y_hpt[3 ].ll)
                    ("sr4" , y_hpt[4 ].ee, y_hpt[4 ].mm, y_hpt[4 ].em, y_hpt[4 ].ll)
                    ("sr5" , y_hpt[5 ].ee, y_hpt[5 ].mm, y_hpt[5 ].em, y_hpt[5 ].ll)
                    ("sr6" , y_hpt[6 ].ee, y_hpt[6 ].mm, y_hpt[6 ].em, y_hpt[6 ].ll)
                    ("sr7" , y_hpt[7 ].ee, y_hpt[7 ].mm, y_hpt[7 ].em, y_hpt[7 ].ll)
                    ("sr8" , y_hpt[8 ].ee, y_hpt[8 ].mm, y_hpt[8 ].em, y_hpt[8 ].ll)
                    ("sr9" , "--"        , "--"        , "--"        , "--"        )
                    ("sr10", y_hpt[10].ee, y_hpt[10].mm, y_hpt[10].em, y_hpt[10].ll)
                    ("sr11", y_hpt[11].ee, y_hpt[11].mm, y_hpt[11].em, y_hpt[11].ll)
                    ("sr12", y_hpt[12].ee, y_hpt[12].mm, y_hpt[12].em, y_hpt[12].ll)
                    ("sr13", y_hpt[13].ee, y_hpt[13].mm, y_hpt[13].em, y_hpt[13].ll)
                    ("sr14", y_hpt[14].ee, y_hpt[14].mm, y_hpt[14].em, y_hpt[14].ll)
                    ("sr15", y_hpt[15].ee, y_hpt[15].mm, y_hpt[15].em, y_hpt[15].ll)
                    ("sr16", y_hpt[16].ee, y_hpt[16].mm, y_hpt[16].em, y_hpt[16].ll)
                    ("sr17", y_hpt[17].ee, y_hpt[17].mm, y_hpt[17].em, y_hpt[17].ll)
                    ("sr18", y_hpt[18].ee, y_hpt[18].mm, y_hpt[18].em, y_hpt[18].ll)
                    ("sr19", "--"        , "--"        , "--"        , "--"        )
                    ("sr20", y_hpt[20].ee, y_hpt[20].mm, y_hpt[20].em, y_hpt[20].ll)
                    ("sr21", y_hpt[21].ee, y_hpt[21].mm, y_hpt[21].em, y_hpt[21].ll)
                    ("sr22", y_hpt[22].ee, y_hpt[22].mm, y_hpt[22].em, y_hpt[22].ll)
                    ("sr23", y_hpt[23].ee, y_hpt[23].mm, y_hpt[23].em, y_hpt[23].ll)
                    ("sr24", y_hpt[24].ee, y_hpt[24].mm, y_hpt[24].em, y_hpt[24].ll)
                    ("sr25", y_hpt[25].ee, y_hpt[25].mm, y_hpt[25].em, y_hpt[25].ll)
                    ("sr26", y_hpt[26].ee, y_hpt[26].mm, y_hpt[26].em, y_hpt[26].ll)
                    ("sr27", y_hpt[27].ee, y_hpt[27].mm, y_hpt[27].em, y_hpt[27].ll)
                    ("sr28", y_hpt[28].ee, y_hpt[28].mm, y_hpt[28].em, y_hpt[28].ll);
    t_hpt.print();

    // low pT
    const yield_t y_lpt[29] = 
   	{ 
       {ch_lpt.GetEntries(ss && ee && sr0 ), ch_lpt.GetEntries(ss && mm && sr0 ), ch_lpt.GetEntries(ss && em && sr0 ), ch_lpt.GetEntries(ss && sr0 )},
       {ch_lpt.GetEntries(ss && ee && sr1 ), ch_lpt.GetEntries(ss && mm && sr1 ), ch_lpt.GetEntries(ss && em && sr1 ), ch_lpt.GetEntries(ss && sr1 )},
       {ch_lpt.GetEntries(ss && ee && sr2 ), ch_lpt.GetEntries(ss && mm && sr2 ), ch_lpt.GetEntries(ss && em && sr2 ), ch_lpt.GetEntries(ss && sr2 )},
       {ch_lpt.GetEntries(ss && ee && sr3 ), ch_lpt.GetEntries(ss && mm && sr3 ), ch_lpt.GetEntries(ss && em && sr3 ), ch_lpt.GetEntries(ss && sr3 )},
       {ch_lpt.GetEntries(ss && ee && sr4 ), ch_lpt.GetEntries(ss && mm && sr4 ), ch_lpt.GetEntries(ss && em && sr4 ), ch_lpt.GetEntries(ss && sr4 )},
       {ch_lpt.GetEntries(ss && ee && sr5 ), ch_lpt.GetEntries(ss && mm && sr5 ), ch_lpt.GetEntries(ss && em && sr5 ), ch_lpt.GetEntries(ss && sr5 )},
       {ch_lpt.GetEntries(ss && ee && sr6 ), ch_lpt.GetEntries(ss && mm && sr6 ), ch_lpt.GetEntries(ss && em && sr6 ), ch_lpt.GetEntries(ss && sr6 )},
       {ch_lpt.GetEntries(ss && ee && sr7 ), ch_lpt.GetEntries(ss && mm && sr7 ), ch_lpt.GetEntries(ss && em && sr7 ), ch_lpt.GetEntries(ss && sr7 )},
       {ch_lpt.GetEntries(ss && ee && sr8 ), ch_lpt.GetEntries(ss && mm && sr8 ), ch_lpt.GetEntries(ss && em && sr8 ), ch_lpt.GetEntries(ss && sr8 )},
       {ch_lpt.GetEntries(ss && ee && sr9 ), ch_lpt.GetEntries(ss && mm && sr9 ), ch_lpt.GetEntries(ss && em && sr9 ), ch_lpt.GetEntries(ss && sr9 )},
       {ch_lpt.GetEntries(ss && ee && sr10), ch_lpt.GetEntries(ss && mm && sr10), ch_lpt.GetEntries(ss && em && sr10), ch_lpt.GetEntries(ss && sr10)},
       {ch_lpt.GetEntries(ss && ee && sr11), ch_lpt.GetEntries(ss && mm && sr11), ch_lpt.GetEntries(ss && em && sr11), ch_lpt.GetEntries(ss && sr11)},
       {ch_lpt.GetEntries(ss && ee && sr12), ch_lpt.GetEntries(ss && mm && sr12), ch_lpt.GetEntries(ss && em && sr12), ch_lpt.GetEntries(ss && sr12)},
       {ch_lpt.GetEntries(ss && ee && sr13), ch_lpt.GetEntries(ss && mm && sr13), ch_lpt.GetEntries(ss && em && sr13), ch_lpt.GetEntries(ss && sr13)},
       {ch_lpt.GetEntries(ss && ee && sr14), ch_lpt.GetEntries(ss && mm && sr14), ch_lpt.GetEntries(ss && em && sr14), ch_lpt.GetEntries(ss && sr14)},
       {ch_lpt.GetEntries(ss && ee && sr15), ch_lpt.GetEntries(ss && mm && sr15), ch_lpt.GetEntries(ss && em && sr15), ch_lpt.GetEntries(ss && sr15)},
       {ch_lpt.GetEntries(ss && ee && sr16), ch_lpt.GetEntries(ss && mm && sr16), ch_lpt.GetEntries(ss && em && sr16), ch_lpt.GetEntries(ss && sr16)},
       {ch_lpt.GetEntries(ss && ee && sr17), ch_lpt.GetEntries(ss && mm && sr17), ch_lpt.GetEntries(ss && em && sr17), ch_lpt.GetEntries(ss && sr17)},
       {ch_lpt.GetEntries(ss && ee && sr18), ch_lpt.GetEntries(ss && mm && sr18), ch_lpt.GetEntries(ss && em && sr18), ch_lpt.GetEntries(ss && sr18)},
       {ch_lpt.GetEntries(ss && ee && sr19), ch_lpt.GetEntries(ss && mm && sr19), ch_lpt.GetEntries(ss && em && sr19), ch_lpt.GetEntries(ss && sr19)},
       {ch_lpt.GetEntries(ss && ee && sr20), ch_lpt.GetEntries(ss && mm && sr20), ch_lpt.GetEntries(ss && em && sr20), ch_lpt.GetEntries(ss && sr20)},
       {ch_lpt.GetEntries(ss && ee && sr21), ch_lpt.GetEntries(ss && mm && sr21), ch_lpt.GetEntries(ss && em && sr21), ch_lpt.GetEntries(ss && sr21)},
       {ch_lpt.GetEntries(ss && ee && sr22), ch_lpt.GetEntries(ss && mm && sr22), ch_lpt.GetEntries(ss && em && sr22), ch_lpt.GetEntries(ss && sr22)},
       {ch_lpt.GetEntries(ss && ee && sr23), ch_lpt.GetEntries(ss && mm && sr23), ch_lpt.GetEntries(ss && em && sr23), ch_lpt.GetEntries(ss && sr23)},
       {ch_lpt.GetEntries(ss && ee && sr24), ch_lpt.GetEntries(ss && mm && sr24), ch_lpt.GetEntries(ss && em && sr24), ch_lpt.GetEntries(ss && sr24)},
       {ch_lpt.GetEntries(ss && ee && sr25), ch_lpt.GetEntries(ss && mm && sr25), ch_lpt.GetEntries(ss && em && sr25), ch_lpt.GetEntries(ss && sr25)},
       {ch_lpt.GetEntries(ss && ee && sr26), ch_lpt.GetEntries(ss && mm && sr26), ch_lpt.GetEntries(ss && em && sr26), ch_lpt.GetEntries(ss && sr26)},
       {ch_lpt.GetEntries(ss && ee && sr27), ch_lpt.GetEntries(ss && mm && sr27), ch_lpt.GetEntries(ss && em && sr27), ch_lpt.GetEntries(ss && sr27)},
       {ch_lpt.GetEntries(ss && ee && sr28), ch_lpt.GetEntries(ss && mm && sr28), ch_lpt.GetEntries(ss && em && sr28), ch_lpt.GetEntries(ss && sr28)}
    };

    CTable t_lpt;
    t_lpt.useTitle();
    t_lpt.setTitle("low pT yields");
    t_lpt.setTable()(               "ee",         "mm",         "em",         "ll")
                    ("sr0" , y_lpt[0 ].ee, y_lpt[0 ].mm, y_lpt[0 ].em, y_lpt[0 ].ll)
                    ("sr1" , y_lpt[1 ].ee, y_lpt[1 ].mm, y_lpt[1 ].em, y_lpt[1 ].ll)
                    ("sr2" , y_lpt[2 ].ee, y_lpt[2 ].mm, y_lpt[2 ].em, y_lpt[2 ].ll)
                    ("sr3" , y_lpt[3 ].ee, y_lpt[3 ].mm, y_lpt[3 ].em, y_lpt[3 ].ll)
                    ("sr4" , y_lpt[4 ].ee, y_lpt[4 ].mm, y_lpt[4 ].em, y_lpt[4 ].ll)
                    ("sr5" , y_lpt[5 ].ee, y_lpt[5 ].mm, y_lpt[5 ].em, y_lpt[5 ].ll)
                    ("sr6" , y_lpt[6 ].ee, y_lpt[6 ].mm, y_lpt[6 ].em, y_lpt[6 ].ll)
                    ("sr7" , y_lpt[7 ].ee, y_lpt[7 ].mm, y_lpt[7 ].em, y_lpt[7 ].ll)
                    ("sr8" , y_lpt[8 ].ee, y_lpt[8 ].mm, y_lpt[8 ].em, y_lpt[8 ].ll)
                    ("sr9" , "--"        , "--"        , "--"        , "--"        )
                    ("sr10", y_lpt[10].ee, y_lpt[10].mm, y_lpt[10].em, y_lpt[10].ll)
                    ("sr11", y_lpt[11].ee, y_lpt[11].mm, y_lpt[11].em, y_lpt[11].ll)
                    ("sr12", y_lpt[12].ee, y_lpt[12].mm, y_lpt[12].em, y_lpt[12].ll)
                    ("sr13", y_lpt[13].ee, y_lpt[13].mm, y_lpt[13].em, y_lpt[13].ll)
                    ("sr14", y_lpt[14].ee, y_lpt[14].mm, y_lpt[14].em, y_lpt[14].ll)
                    ("sr15", y_lpt[15].ee, y_lpt[15].mm, y_lpt[15].em, y_lpt[15].ll)
                    ("sr16", y_lpt[16].ee, y_lpt[16].mm, y_lpt[16].em, y_lpt[16].ll)
                    ("sr17", y_lpt[17].ee, y_lpt[17].mm, y_lpt[17].em, y_lpt[17].ll)
                    ("sr18", y_lpt[18].ee, y_lpt[18].mm, y_lpt[18].em, y_lpt[18].ll)
                    ("sr19", "--"        , "--"        , "--"        , "--"        )
                    ("sr20", y_lpt[20].ee, y_lpt[20].mm, y_lpt[20].em, y_lpt[20].ll)
                    ("sr21", y_lpt[21].ee, y_lpt[21].mm, y_lpt[21].em, y_lpt[21].ll)
                    ("sr22", y_lpt[22].ee, y_lpt[22].mm, y_lpt[22].em, y_lpt[22].ll)
                    ("sr23", y_lpt[23].ee, y_lpt[23].mm, y_lpt[23].em, y_lpt[23].ll)
                    ("sr24", y_lpt[24].ee, y_lpt[24].mm, y_lpt[24].em, y_lpt[24].ll)
                    ("sr25", y_lpt[25].ee, y_lpt[25].mm, y_lpt[25].em, y_lpt[25].ll)
                    ("sr26", y_lpt[26].ee, y_lpt[26].mm, y_lpt[26].em, y_lpt[26].ll)
                    ("sr27", y_lpt[27].ee, y_lpt[27].mm, y_lpt[27].em, y_lpt[27].ll)
                    ("sr28", y_lpt[28].ee, y_lpt[28].mm, y_lpt[28].em, y_lpt[28].ll);
    cout << endl;
    t_lpt.print();

    // very low pT
    const yield_t y_vpt[29] = 
    {
        {ch_vpt.GetEntries(ss && ee && sr0 ), ch_vpt.GetEntries(ss && mm && sr0 ), ch_vpt.GetEntries(ss && em && sr0 ), ch_vpt.GetEntries(ss && sr0 )},
        {ch_vpt.GetEntries(ss && ee && sr1 ), ch_vpt.GetEntries(ss && mm && sr1 ), ch_vpt.GetEntries(ss && em && sr1 ), ch_vpt.GetEntries(ss && sr1 )},
        {ch_vpt.GetEntries(ss && ee && sr2 ), ch_vpt.GetEntries(ss && mm && sr2 ), ch_vpt.GetEntries(ss && em && sr2 ), ch_vpt.GetEntries(ss && sr2 )},
        {ch_vpt.GetEntries(ss && ee && sr3 ), ch_vpt.GetEntries(ss && mm && sr3 ), ch_vpt.GetEntries(ss && em && sr3 ), ch_vpt.GetEntries(ss && sr3 )},
        {ch_vpt.GetEntries(ss && ee && sr4 ), ch_vpt.GetEntries(ss && mm && sr4 ), ch_vpt.GetEntries(ss && em && sr4 ), ch_vpt.GetEntries(ss && sr4 )},
        {ch_vpt.GetEntries(ss && ee && sr5 ), ch_vpt.GetEntries(ss && mm && sr5 ), ch_vpt.GetEntries(ss && em && sr5 ), ch_vpt.GetEntries(ss && sr5 )},
        {ch_vpt.GetEntries(ss && ee && sr6 ), ch_vpt.GetEntries(ss && mm && sr6 ), ch_vpt.GetEntries(ss && em && sr6 ), ch_vpt.GetEntries(ss && sr6 )},
        {ch_vpt.GetEntries(ss && ee && sr7 ), ch_vpt.GetEntries(ss && mm && sr7 ), ch_vpt.GetEntries(ss && em && sr7 ), ch_vpt.GetEntries(ss && sr7 )},
        {ch_vpt.GetEntries(ss && ee && sr8 ), ch_vpt.GetEntries(ss && mm && sr8 ), ch_vpt.GetEntries(ss && em && sr8 ), ch_vpt.GetEntries(ss && sr8 )},
        {ch_vpt.GetEntries(ss && ee && sr9 ), ch_vpt.GetEntries(ss && mm && sr9 ), ch_vpt.GetEntries(ss && em && sr9 ), ch_vpt.GetEntries(ss && sr9 )},
        {ch_vpt.GetEntries(ss && ee && sr10), ch_vpt.GetEntries(ss && mm && sr10), ch_vpt.GetEntries(ss && em && sr10), ch_vpt.GetEntries(ss && sr10)},
        {ch_vpt.GetEntries(ss && ee && sr11), ch_vpt.GetEntries(ss && mm && sr11), ch_vpt.GetEntries(ss && em && sr11), ch_vpt.GetEntries(ss && sr11)},
        {ch_vpt.GetEntries(ss && ee && sr12), ch_vpt.GetEntries(ss && mm && sr12), ch_vpt.GetEntries(ss && em && sr12), ch_vpt.GetEntries(ss && sr12)},
        {ch_vpt.GetEntries(ss && ee && sr13), ch_vpt.GetEntries(ss && mm && sr13), ch_vpt.GetEntries(ss && em && sr13), ch_vpt.GetEntries(ss && sr13)},
        {ch_vpt.GetEntries(ss && ee && sr14), ch_vpt.GetEntries(ss && mm && sr14), ch_vpt.GetEntries(ss && em && sr14), ch_vpt.GetEntries(ss && sr14)},
        {ch_vpt.GetEntries(ss && ee && sr15), ch_vpt.GetEntries(ss && mm && sr15), ch_vpt.GetEntries(ss && em && sr15), ch_vpt.GetEntries(ss && sr15)},
        {ch_vpt.GetEntries(ss && ee && sr16), ch_vpt.GetEntries(ss && mm && sr16), ch_vpt.GetEntries(ss && em && sr16), ch_vpt.GetEntries(ss && sr16)},
        {ch_vpt.GetEntries(ss && ee && sr17), ch_vpt.GetEntries(ss && mm && sr17), ch_vpt.GetEntries(ss && em && sr17), ch_vpt.GetEntries(ss && sr17)},
        {ch_vpt.GetEntries(ss && ee && sr18), ch_vpt.GetEntries(ss && mm && sr18), ch_vpt.GetEntries(ss && em && sr18), ch_vpt.GetEntries(ss && sr18)},
        {ch_vpt.GetEntries(ss && ee && sr19), ch_vpt.GetEntries(ss && mm && sr19), ch_vpt.GetEntries(ss && em && sr19), ch_vpt.GetEntries(ss && sr19)},
        {ch_vpt.GetEntries(ss && ee && sr20), ch_vpt.GetEntries(ss && mm && sr20), ch_vpt.GetEntries(ss && em && sr20), ch_vpt.GetEntries(ss && sr20)},
        {ch_vpt.GetEntries(ss && ee && sr21), ch_vpt.GetEntries(ss && mm && sr21), ch_vpt.GetEntries(ss && em && sr21), ch_vpt.GetEntries(ss && sr21)},
        {ch_vpt.GetEntries(ss && ee && sr22), ch_vpt.GetEntries(ss && mm && sr22), ch_vpt.GetEntries(ss && em && sr22), ch_vpt.GetEntries(ss && sr22)},
        {ch_vpt.GetEntries(ss && ee && sr23), ch_vpt.GetEntries(ss && mm && sr23), ch_vpt.GetEntries(ss && em && sr23), ch_vpt.GetEntries(ss && sr23)},
        {ch_vpt.GetEntries(ss && ee && sr24), ch_vpt.GetEntries(ss && mm && sr24), ch_vpt.GetEntries(ss && em && sr24), ch_vpt.GetEntries(ss && sr24)},
        {ch_vpt.GetEntries(ss && ee && sr25), ch_vpt.GetEntries(ss && mm && sr25), ch_vpt.GetEntries(ss && em && sr25), ch_vpt.GetEntries(ss && sr25)},
        {ch_vpt.GetEntries(ss && ee && sr26), ch_vpt.GetEntries(ss && mm && sr26), ch_vpt.GetEntries(ss && em && sr26), ch_vpt.GetEntries(ss && sr26)},
        {ch_vpt.GetEntries(ss && ee && sr27), ch_vpt.GetEntries(ss && mm && sr27), ch_vpt.GetEntries(ss && em && sr27), ch_vpt.GetEntries(ss && sr27)},
        {ch_vpt.GetEntries(ss && ee && sr28), ch_vpt.GetEntries(ss && mm && sr28), ch_vpt.GetEntries(ss && em && sr28), ch_vpt.GetEntries(ss && sr28)}
    };

    CTable t_vpt;
    t_vpt.useTitle();
    t_vpt.setTitle("very low pT yields");
    t_vpt.setTable()(               "ee",         "mm",         "em",         "ll")
                    ("sr0" , y_vpt[0 ].ee, y_vpt[0 ].mm, y_vpt[0 ].em, y_vpt[0 ].ll)
                    ("sr1" , y_vpt[1 ].ee, y_vpt[1 ].mm, y_vpt[1 ].em, y_vpt[1 ].ll)
                    ("sr2" , y_vpt[2 ].ee, y_vpt[2 ].mm, y_vpt[2 ].em, y_vpt[2 ].ll)
                    ("sr3" , y_vpt[3 ].ee, y_vpt[3 ].mm, y_vpt[3 ].em, y_vpt[3 ].ll)
                    ("sr4" , y_vpt[4 ].ee, y_vpt[4 ].mm, y_vpt[4 ].em, y_vpt[4 ].ll)
                    ("sr5" , y_vpt[5 ].ee, y_vpt[5 ].mm, y_vpt[5 ].em, y_vpt[5 ].ll)
                    ("sr6" , y_vpt[6 ].ee, y_vpt[6 ].mm, y_vpt[6 ].em, y_vpt[6 ].ll)
                    ("sr7" , y_vpt[7 ].ee, y_vpt[7 ].mm, y_vpt[7 ].em, y_vpt[7 ].ll)
                    ("sr8" , y_vpt[8 ].ee, y_vpt[8 ].mm, y_vpt[8 ].em, y_vpt[8 ].ll)
                    ("sr9" , "--"        , "--"        , "--"        , "--"        )
                    ("sr10", y_vpt[10].ee, y_vpt[10].mm, y_vpt[10].em, y_vpt[10].ll)
                    ("sr11", y_vpt[11].ee, y_vpt[11].mm, y_vpt[11].em, y_vpt[11].ll)
                    ("sr12", y_vpt[12].ee, y_vpt[12].mm, y_vpt[12].em, y_vpt[12].ll)
                    ("sr13", y_vpt[13].ee, y_vpt[13].mm, y_vpt[13].em, y_vpt[13].ll)
                    ("sr14", y_vpt[14].ee, y_vpt[14].mm, y_vpt[14].em, y_vpt[14].ll)
                    ("sr15", y_vpt[15].ee, y_vpt[15].mm, y_vpt[15].em, y_vpt[15].ll)
                    ("sr16", y_vpt[16].ee, y_vpt[16].mm, y_vpt[16].em, y_vpt[16].ll)
                    ("sr17", y_vpt[17].ee, y_vpt[17].mm, y_vpt[17].em, y_vpt[17].ll)
                    ("sr18", y_vpt[18].ee, y_vpt[18].mm, y_vpt[18].em, y_vpt[18].ll)
                    ("sr19", "--"        , "--"        , "--"        , "--"        )
                    ("sr20", y_vpt[20].ee, y_vpt[20].mm, y_vpt[20].em, y_vpt[20].ll)
                    ("sr21", y_vpt[21].ee, y_vpt[21].mm, y_vpt[21].em, y_vpt[21].ll)
                    ("sr22", y_vpt[22].ee, y_vpt[22].mm, y_vpt[22].em, y_vpt[22].ll)
                    ("sr23", y_vpt[23].ee, y_vpt[23].mm, y_vpt[23].em, y_vpt[23].ll)
                    ("sr24", y_vpt[24].ee, y_vpt[24].mm, y_vpt[24].em, y_vpt[24].ll)
                    ("sr25", y_vpt[25].ee, y_vpt[25].mm, y_vpt[25].em, y_vpt[25].ll)
                    ("sr26", y_vpt[26].ee, y_vpt[26].mm, y_vpt[26].em, y_vpt[26].ll)
                    ("sr27", y_vpt[27].ee, y_vpt[27].mm, y_vpt[27].em, y_vpt[27].ll)
                    ("sr28", y_vpt[28].ee, y_vpt[28].mm, y_vpt[28].em, y_vpt[28].ll);
    cout << endl;
    t_vpt.print();
}
