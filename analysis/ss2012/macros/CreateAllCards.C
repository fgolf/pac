#include "at/Sample.h"
#include "rt/RootTools.h"
#include "SignalBinInfo.h"
#include <iostream>
#include <string>
#include "TSystem.h"

// this macro creates a folder that contains all of the cards for each mass point
// the mass points are defined in SignalBinInfo.cc


void CreateAllCards
(
    const at::Sample::value_type sample,
    const std::string& yield_file,
    const std::string& syst_file,
    const std::string& output_file_stem,
    const std::string& signal_region_list, 
    const float luminosity = 1.0
)
{
    using namespace ss;
    using namespace at;
    using namespace std;

    SignalBinInfo bin_info = GetSignalBinInfo(sample);


    const size_t nbinsx = bin_info.nbinsx;
    const size_t nbinsy = bin_info.nbinsy;
    const float xmin    = bin_info.xmin;
    const float xmax    = bin_info.xmax;
    const float ymin    = bin_info.ymin + bin_info.ywidth + bin_info.offset;
    const float ymax    = bin_info.ymax + bin_info.ywidth;
    const float m       = (ymax - ymin)/(xmax - xmin);

    for (size_t xbin = 0; xbin != nbinsx; xbin++)
    {
        for (size_t ybin = 0; ybin != nbinsy; ybin++)
        {
            const float sparm0 = bin_info.xmin + xbin*bin_info.xwidth;
            const float sparm1 = bin_info.ymin + ybin*bin_info.ywidth;
            const float x      = bin_info.xmin + xbin*bin_info.xwidth;
            const float y      = bin_info.ymin + (ybin+1)*bin_info.ywidth;
            const float cond   = m*(x - xmin) + ymin;

            // boundary conditions
            if (y > cond) {continue;}

            const string output_file = (output_file_stem.empty() ? "\"\"" : Form("cards/%s/%s_p%1.0f_p%1.0f.txt", output_file_stem.c_str(), output_file_stem.c_str(), sparm0, sparm1));

            string cmd = Form
            (
                 "ss2012_create_card --sr %s --yield %s --syst %s --output %s --sparm0 %f --sparm1 %f --lumi %f",
                 signal_region_list.c_str(),
                 yield_file.c_str(),
                 syst_file.c_str(),
                 output_file.c_str(),
                 sparm0,
                 sparm1,
                 luminosity
            );
            cout << cmd << endl;
            gSystem->Exec(cmd.c_str());
        } 
    }

    // done
    return;
}
