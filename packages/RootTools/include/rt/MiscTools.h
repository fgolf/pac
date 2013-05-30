#ifndef RT_MISC_TOOLS_H
#define RT_MISC_TOOLS_H

// c++ includes
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <ostream>

// ROOT includes
#include "TFile.h"
#include "TChain.h"
#include "TCut.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TDirectory.h"
#include "TEfficiency.h"
#include "Math/LorentzVector.h"

// BOOST includes (not CINT friendly)
#ifndef __RTINT__
#include "boost/shared_ptr.hpp"
#endif

// Ian's table class
#include "CTable.h"

// lorentz vector of floats 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// namespace rt --> root tools
namespace rt
{
    // Typedefs -- interactive types use bare pointer, full c++ use smart pointer 
    // -------------------------------------------------------------------------------------------------//

#ifdef __RTINT__
    typedef TFile* TFilePtr;
    typedef TH1* TH1Ptr;
#else
    //typedef std::auto_ptr<TFile> TFilePtr;
    typedef TFile* TFilePtr;
    typedef boost::shared_ptr<TH1> TH1Ptr;
#endif // ifdef __RTINT__

    // helper and functions for ROOT operations (uses ROOT name conventions)
    // -------------------------------------------------------------------------------------------------//

    // get a root file (throws if file not found)
    TFilePtr OpenRootFile(const std::string& file_name, const std::string& option = "");

    // get a single histgram from a root file (client is the owner)
    template <typename HistType>
    HistType* GetHistFromRootFile(const std::string& file_name, const std::string& hist_name);

    // get all the hists from a root file (given a file) in a map of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    std::map<std::string, rt::TH1Ptr> GetMapOfTH1s(const rt::TFilePtr& file, const std::string& root_file_dir = "");

    // get all the hists from a root file (given a filename) in a map of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    std::map<std::string, rt::TH1Ptr> GetMapOfTH1s(const std::string& filename, const std::string& root_file_dir = "");

    // get all the hists from a root file (given a file) in a vector of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    std::vector<rt::TH1Ptr> GetVectorOfTH1s(const rt::TFilePtr& file, const std::string& root_file_dir = "");

    // get all the hists from a root file (given a filename) in a vector of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    std::vector<rt::TH1Ptr> GetVectorOfTH1s(const std::string& filename, const std::string& root_file_dir = "");

    // save the contents of the map to a root file
    void Write
    (
         std::map<std::string, TH1Ptr>& hist_map, 
         const std::string& file_name, 
         const std::string& root_file_dir = "",
         const std::string& option = "UPDATE"
    );

    void Write
    (
         std::map<std::string, TH1Ptr>& hist_map, 
         TFile* root_file,
         const std::string& root_file_dir = ""
    );

    // save the contents of the vector to a root file
    void Write
    (
         std::vector<rt::TH1Ptr>& hist_vector, 
         const std::string& file_name, 
         const std::string& root_file_dir = "",
         const std::string& option = "UPDATE"
    );

    // save a hist to a ROOT file 
    void Write
    (
         const rt::TH1Ptr& hist_ptr, 
         const std::string& file_name, 
         const std::string& root_file_dir = "",
         const std::string& option = "UPDATE"
    );

    // print a single object to eps/png/pdf
    template <typename RootObjectType>
    void Print
    (
         RootObjectType obj, 
         const std::string& file_name, 
         const std::string& suffix = "png", 
         const std::string& option = "",
         bool logy = false
    );

    // print the plots from the map to eps/png/pdf
    template <typename RootObjectType>
    void Print
    (
         std::map<std::string, RootObjectType>& m, 
         const std::string& dir_name, 
         const std::string& suffix = "png", 
         const std::string& option = "",
         bool logy = false
    );

    // print the histogram to eps/png/pdt
    void Print
    (
         TH1* hist_ptr, 
         const std::string& dir_name, 
         const std::string& suffix = "png", 
         const std::string& file_name = "", 
         const std::string& option = "",
         bool logy = false
    );

#ifndef __RTINT__
    // print the histogram to eps/png/pdf
    void Print
    (
         const boost::shared_ptr<TH1>& hist_ptr, 
         const std::string& dir_name, 
         const std::string& suffix = "png", 
         const std::string& file_name = "", 
         const std::string& option = "",
         bool logy = false
    );
#endif // __RTINT__

    // print the plots to eps/png/pdf 
    void Print
    (
         std::map<std::string, TH1Ptr>& hist_map, 
         const std::string& dir_name, 
         const std::string& suffix = "png",
         const std::string& option = "",
         bool logy = false
    );

    // print the plots to eps/png/pdf 
    void Print
    (
         std::vector<rt::TH1Ptr>& hist_vector, 
         const std::string& dir_name, 
         const std::string& suffix = "png",
         const std::string& option = "",
         bool logy = false
    );


    // print list of files in a TChain
    void PrintFilesFromTChain(TChain* chain);
    void PrintFilesFromTChain(const TChain& chain);
    void PrintFilesFromTChain(std::vector<TChain*> chains);

	// make a TChain from a path
	TChain* MakeTChain
	(
		const std::string& glob, 
		const std::string& treename = "Events", 
		TChain* chain_in = NULL, 
		bool verbose = false
	);

	// create a chain from a comma serperated list (e.g. "file1,file2,...")
    // NOTE: user is charge of deleting!
	TChain* CreateTChainFromCommaSeperatedList
	(
		const std::string& str, 
		const std::string& treename,
		const std::string& prefix = "" 
	);

    // print list of files in a TChain
    std::vector<std::string> GetFilesFromTChain(TChain* chain);

    // create a Projection from 2D hist 
    TH1* MakeProjectionPlot
    (
        TH2* hist, 
        const std::string& axis = "x", 
        const std::string& name = "", 
        const std::string& title = "", 
        double low = 0.0, 
        double high = -1.0,
        const std::string& option = ""
    );

    // create a Projection from num and den hists 
    TH1* MakeEfficiencyProjectionPlot
    (
        TH2* num_hist, 
        TH2* den_hist, 
        const std::string& axis = "x", 
        const std::string& name = "", 
        const std::string& title = "", 
        double low = 0.0, 
        double high = -1.0,
        const std::string& option = ""
    );

    // create a Projection from num and den hists 
    // this version for convenience (num and den hist must be castable to TH2*)
    TH1* MakeEfficiencyProjectionPlot
    (
        TH1* num_hist,  
        TH1* den_hist, 
        const std::string& axis = "x", 
        const std::string& name = "", 
        const std::string& title = "", 
        double low = 0.0, 
        double high = -1.0,
        const std::string& option = ""
    );

    // make an efficiency plot by dividing the two histograms 
    TH1* MakeEfficiencyPlot
    (
        TH1* num_hist, 
        TH1* den_hist, 
        const std::string& name = "h_eff", 
        const std::string& title = ""
    );

    // make a 2D efficiency plot by dividing the two histograms 
    TH2* MakeEfficiencyPlot2D
    (
        TH1* num_hist, 
        TH1* den_hist, 
        const std::string& name = "h_eff2D",
        const std::string& title = ""
    );

    TH2* MakeEfficiencyPlot2D
    (
        TH2* num_hist, 
        TH2* den_hist, 
        const std::string& name = "h_eff2D",
        const std::string& title = ""
    );

    // Add Hists and return new hist (client is owner of the TH1*)
    TH1* AddHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title = "");
    TH1* AddHists(TH1* h1, TH1* h2, TH1* h3, const std::string& name, const std::string& title = "");

    // Subtract Hists and return new hist (client is owner of the TH1*)
    TH1* SubtractHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title = "");

    // Divide Hists and return new hist (client is owner of the TH1*)
    TH1* DivideHists(TH1* h_num, TH1* h_den, const std::string& name, const std::string& title = "", const std::string& option = "");

    // Multiply Hists and return new hist (client is owner of the TH1*)
    TH1* MultiplyHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title = "", const std::string& option = "");

    // Subtract Hists and then divide by the first and return new hist (client is owner of the TH1*)
    // rel diff = (h1 - h2)/h1
    TH1* RelativeDiffHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title = "");

    // mask off all values that are in the range and set the values to zero 
    void MaskHist2D(TH1* h1, std::string axis_label, const float low, const float high);

    // set statbox position
    void SetStatBoxPosition(TH1* hist_ptr, float x1 = 0.8, float y1 = 0.8, float x2 = 1.0, float y2 = 1.0);

    // a fix to the issue of the erros on the profile hists
    void CalcErrorsForProfile(TProfile* profile);

    // maximum value in hist 
    double GetHistMaximumValue(TH1* hist, bool include_error = false);

    // minimum value in hist 
    double GetHistMinimumValue(TH1* hist, bool include_error = false);

    // add root files (returns 0 if successful) -- lower case to match the utility name
    int hadd(const std::string& target, const std::vector<std::string>& sources);

    // copy the index.php file to dirname
    void CopyIndexPhp(const std::string& target_dir);

    // Set style
    void SetStyle(const std::string& value = "emrou");

    // scale the histogram to scale 
    void Scale(TH1* hist, double scale = 1.0);

    // calulate Mt between two vectors
    double Mt(const LorentzVector& p1, const LorentzVector& p2);

    // calulate Mt between LorentzVector and Missing ET
    double Mt(const LorentzVector& p, double met, double met_phi);

    // calulate Delta Phi between two angles 
    double DeltaPhi(double phi1, double ph2);

    // calulate DeltaEta between two LorentzVectors
    double DeltaEta(const LorentzVector& p1, const LorentzVector& p2);

    // calulate DeltaPhi between two LorentzVectors
    double DeltaPhi(const LorentzVector& p1, const LorentzVector& p2);

    // calulate DeltaR between two LorentzVectors
    double DeltaR(const LorentzVector& p1, const LorentzVector& p2);

    // calculate the integral 1D
    double Integral(TH1* h, const std::string& option = "");
    double Integral(TH1* h, float low, float high, const std::string& option = "");

    // calculate the integral 1D
    double Integral(TH2* h, const std::string& option = "");
    double Integral(TH2* h, float xlow, float xhigh, float ylow, float yhigh, const std::string& option = "");

    // get the bin content with float values
    double GetBinContent1D(TH1* h, const float x);
    double GetBinContent2D(TH2* h, const float x, const float y);
    double GetBinError1D(TH1* h, const float x);
    double GetBinError2D(TH2* h, const float x, const float y);

    // create a CTable from a hist (1D and 2D only)                            
    CTable CreateTableFromHist                                                 
    (                                                                          
        TH1* hist,                                                             
        const std::string& title = "",                                         
        const std::string& xtitle = "",                                        
        const std::string& ytitle = "",                                        
        const std::string& xunit = "",                                         
        const std::string& yunit = "",                                         
        const std::string& precision = "1.2",                                  
        const std::string& xprecision = "1.2",                                 
        const std::string& yprecision = "1.2",                                 
        const bool reverse_axis = false                                        
    );                                                                         

    // inflate the bin error by percentage of the bin value (used for systematic uncertainties)
    void SetSystematicUncertainty(TH1* h, float sys_unc);

    // calculate the integral and Error
    std::pair<double, double> IntegralAndError(TH1* h, const std::string& option = "");
    std::pair<double, double> IntegralAndError(TH1* h, float low, float high, const std::string& option = "");

    // calculate the integral and Error
    std::pair<double, double> EntriesAndError(TH1* h, const std::string& option = "");

    // Add with error
    std::pair<double, double> AddWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2);
    std::pair<float, float>   AddWithError(const std::pair<float, float>& v1  , const std::pair<float, float>& v2  );

    // Subtract with error
    std::pair<double, double> SubtractWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2);
    std::pair<float, float>   SubtractWithError(const std::pair<float, float>& v1  , const std::pair<float, float>& v2  );

    // Multiply with error
    std::pair<double, double> MultiplyWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2);
    std::pair<float, float>   MultiplyWithError(const std::pair<float, float>& v1  , const std::pair<float, float>& v2  );

    // Divide with error
    std::pair<double, double> DivideWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2);
    std::pair<float, float>   DivideWithError(const std::pair<float, float>& v1  , const std::pair<float, float>& v2  );

    // If num_passed passed of num_generated, what is upper limit on number of events passing?
    float GetClopperPearsonUncertainty(const int num_passed, const int num_generated, const float level = 0.68, const bool use_upper = true);

    double CalcPercentOfIntegral(TH1* h, float low, float high, const std::string& option = "");

    // ostream for LorentzVector
    std::ostream& operator << (ostream& os, const LorentzVector& p4);

    // wrapper around TTree::Draw to manange underflow and overflow bins
    // NOTE: doesn't support yet tree->Draw("x>>+h") yet...
    long TTreeDraw1D
    (
        TTree* const tree, 
        TH1* hist_ptr, 
        const std::string& varexp, 
        const TCut& selection, 
        const std::string& option = "", 
        long nentries = 1000000000, 
        long firstentry = 0
    );

    long TTreeDraw1D
    (
        TTree* const tree, 
        TH1* hist_ptr, 
        const std::string& varexp, 
        const std::string& selection = "", 
        const std::string& option = "", 
        long nentries = 1000000000, 
        long firstentry = 0
    );

    // helper functions for OS operations (uses c++ name conventions)
    // -------------------------------------------------------------------------------------------------//

    // format the float to a string 
    std::string fmt(const float value, const std::string& format = "1.2f");

    // get an environment variable
    std::string getenv(const std::string& name);

    // copy a file
    bool copy_file(const std::string& source, const std::string& destination);

    // move a file
    bool move_file(const std::string& source, const std::string& destination);

    // get a vector of strings for all the files in path 
    std::vector<std::string> get_list_of_files(const std::string &path, bool show_hidden_files = false);

    // simple ls function
    std::vector<std::string> ls(const std::string& mask);

    // get a vector of strings for all the files in path 
    std::vector<std::string> get_list_of_files_from_castor(const std::string &path);

    // get the base name of file from a full path (i.e. /path/to/file.txt --> file) 
    std::string basename(const std::string& full_name);

    // get the extension  name of file from a full path (i.e. /path/to/file.txt --> .txt) 
    std::string extension(const std::string& full_name);

    // get the file name from a full path (i.e. /path/to/file.txt --> file.txt) 
    std::string filename(const std::string& full_name);

    // get the path from a full path (i.e. /path/to/file.txt --> /path/to) 
    std::string dirname(const std::string& full_name);

    // create a folder (force is the equivalent of POSIX option "-p")
    bool mkdir(const std::string& path_name, bool force = false);

    // create a folder from the file name if it doesn't exist -- returns the file name
    // throws if it can't make the dir
    std::string mkdir_from_filename(const std::string& file_name, bool force = true);

    // remove a file (force is the equivalent of POSIX option "-r")
    void remove(const std::string& file_name, bool force = false);

    // file exists
    bool exists(const std::string& file_name); 

    // helper functions for std::string operations 
    // -------------------------------------------------------------------------------------------------//

    // does str contains sub_str?
    bool string_contains(const std::string& str, const std::string& sub_str);

    // remove all occurrences of sub_str from str
    std::string string_remove_all(const std::string& str, const std::string& sub_str);

    // replace all occurrences of sub_str from str with new_sub_str
    std::string string_replace_all(const std::string& str, const std::string& sub_str, const std::string& new_sub_str);

    // replace first occurrences of sub_str from str with new_sub_str
    std::string string_replace_first(const std::string& str, const std::string& sub_str, const std::string& new_sub_str);

    // replace last occurrences of sub_str from str with new_sub_str
    std::string string_replace_last(const std::string& str, const std::string& sub_str, const std::string& new_sub_str);

    // replace all upper case characters to lower case 
    std::string string_lower(const std::string& str);

    // replace all lower case characters to upper case 
    std::string string_upper(const std::string& str);

    // split the string into a vector of string based on the deliminator 
    std::vector<std::string> string_split(const std::string& str, const std::string& delim = ",");

    // character is space
    bool is_space(char c);

    // character is not a space
    bool not_space(char c);

    // get an array of floats from an array of doubles
    float* ConvertDoubleArrayToFloatArray(const double *d, size_t n);

    // print the value/error with +/-
    std::string pm(double value, double error, const std::string& precision = "1.2");
    std::string pm(const std::pair<double, double>& value_pair, const std::string& precision = "1.2");
    std::string pm(const std::pair<float, float>& value_pair, const std::string& precision = "1.2");

    // print the value/error with +/- in latex
    std::string pm_latex(double value, double error, const std::string& precision = "1.2");
    std::string pm_latex(const std::pair<double, double>& value_pair, const std::string& precision = "1.2");
    std::string pm_latex(const std::pair<float, float>& value_pair, const std::string& precision = "1.2");

    // helper for low level objects 
    // -------------------------------------------------------------------------------------------------//

    // only works on compile time arrays (e.g. float bins[] = {1,2,3};)
    template <int N> unsigned int find_bin(const float value, const float (&bins)[N]);
    template <int N> unsigned int find_bin(const double value, const double (&bins)[N]);

    // helper functions for STL containters  (not in CINT)
    // -------------------------------------------------------------------------------------------------//

#ifndef __CINT__

    // copy a container filtering on predicate
    template <typename InputIterator, typename OutputIterator, typename Predicate >
    OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator dest, Predicate p);

    // filter the container
    template <typename Container, typename Predicate>
    Container filter_container(const Container &c, Predicate p);

    // combine containers 
    template <typename Container>
    Container combine_container(const Container &c1, const Container &c2);

    // delete the container
    template <typename Container>
    void delete_container(const Container &c);

    // initialze container
    //template <typename Container, typename Type>
    //void init_container(const Container &c, const Type& t = Type());

    // helper functions for low level c++ 
    // -------------------------------------------------------------------------------------------------//

#endif // ifdef __CINT__

} // namespace rt


// implemenation of templated functions/classes (not in CINT)
// -------------------------------------------------------------------------------------------------//

#ifndef __CINT__
#include "MiscTools.impl.h"
#endif

#endif // RT_MISC_TOOLS_H 
