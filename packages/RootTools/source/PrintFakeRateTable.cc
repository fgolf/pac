#include "rt/PrintFakeRateTable.h"
#include "TROOT.h"
#include "TH2.h"
#include <iostream>
#include <string>

namespace rt
{
    void PrintFakeRateTable(TH2* hist, std::ostream& out)
    {
        // some commonly used charactors for printing table
        std::string colsep = " & ";
        std::string pmSign = " $\\pm$ ";
        std::string endL   = " \\\\ \\hline";

        // print out header stuff for latex table
        out << "\\begin{table}[htb]" << std::endl;
        out << "\\begin{center}" << std::endl;
        out << "\\caption{}" << std::endl;
        out << "\\begin{tabular}{c|ccccc}" << std::endl;
        out << "\\hline" << std::endl;
        out << "\\backslashbox{$|\\eta|$}{$p_T$}";

        int nbinsx = hist->GetNbinsX(); // number of bins along x axis
        int nbinsy = hist->GetNbinsY(); // number of bins along y axis

        // first, print pt ranges
        for (int ny = 1; ny < nbinsy+1; ny++) 
        {
            float lowedge  = hist->GetYaxis()->GetBinLowEdge(ny);
            float width    = hist->GetYaxis()->GetBinWidth(ny);

            printf("%s%.3f%s%.3f", colsep.c_str(), lowedge, " -- ", lowedge+width);
        }

        out << endL << "\\hline" << std::endl;

        // loop over bins
        for (int nx = 1; nx < nbinsx+1; nx++) 
        {
            for (int ny = 1; ny < nbinsy+1; ny++) 
            {
                int nbin = hist->GetBin(nx, ny);

                // if first bin in column, print out eta range
                if (ny == 1) 
                {
                    float lowedge  = hist->GetXaxis()->GetBinLowEdge(nx);
                    float width    = hist->GetXaxis()->GetBinWidth(nx);

                    printf("%.3f%s%.3f", lowedge, " -- ", lowedge+width);
                }

                float fr    = hist->GetBinContent(nbin);
                float frerr = hist->GetBinError(nbin);

                printf("%s%.4f%s%.4f", colsep.c_str(), fr, pmSign.c_str(), frerr);
            }

            out << endL << "\\hline" << std::endl;
        }

        // print out final header stuff for table
        out << "\\end{tabular}" << std::endl;
        out << "\\end{center}" << std::endl;
        out << "\\end{table}" << std::endl;

        // done
        return;
    }

    void PrintFlipRateTable(TH2* hist, std::ostream& out)
    {
        // some commonly used charactors for printing table
        std::string colsep = " & ";
        std::string pmSign = " $\\pm$ ";
        std::string endL   = " \\\\ \\hline";

        // print out header stuff for latex table
        out << "\\begin{table}[htb]" << std::endl;
        out << "\\begin{center}" << std::endl;
        out << "\\caption{}" << std::endl;
        out << "\\begin{tabular}{c|ccccc}" << std::endl;
        out << "\\hline" << std::endl;
        out << "\\backslashbox{$|\\eta|$}{$p_T$}";

        int nbinsx = hist->GetNbinsX(); // number of bins along x axis
        int nbinsy = hist->GetNbinsY(); // number of bins along y axis

        // first, print pt ranges
        for (int ny = 1; ny < nbinsy+1; ny++) 
        {
            float lowedge  = hist->GetYaxis()->GetBinLowEdge(ny);
            float width    = hist->GetYaxis()->GetBinWidth(ny);

            printf("%s%.2e%s%.2e", colsep.c_str(), lowedge, " -- ", lowedge+width);
        }

        out << endL << "\\hline" << std::endl;

        // loop over bins
        for (int nx = 1; nx < nbinsx+1; nx++) 
        {
            for (int ny = 1; ny < nbinsy+1; ny++) 
            {
                int nbin = hist->GetBin(nx, ny);

                // if first bin in column, print out eta range
                if (ny == 1) 
                {
                    float lowedge  = hist->GetXaxis()->GetBinLowEdge(nx);
                    float width    = hist->GetXaxis()->GetBinWidth(nx);

                    printf("%.2e%s%.2e", lowedge, " -- ", lowedge+width);
                }

                float fr    = hist->GetBinContent(nbin);
                float frerr = hist->GetBinError(nbin);

                printf("%s%.2e%s%.2e", colsep.c_str(), fr, pmSign.c_str(), frerr);
            }

            out << endL << "\\hline" << std::endl;
        }

        // print out final header stuff for table
        out << "\\end{tabular}" << std::endl;
        out << "\\end{center}" << std::endl;
        out << "\\end{table}" << std::endl;

        // done
        return;
    }

} // namespace rt
