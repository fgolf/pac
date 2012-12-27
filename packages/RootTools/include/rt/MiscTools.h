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
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TDirectory.h"
#include "Math/LorentzVector.h"

// BOOST includes (not CINT friendly)
#ifndef __RTINT__
#include "boost/shared_ptr.hpp"
#endif

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
	//TChain* CreateTChainFromCommaSeperatedList
	//(
	//	const std::string& str, 
	//	const std::string& treename 
	//);

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

    // calculate the percent of integral 
    double CalcPercentOfIntegral(TH1* h, float low, float high, const std::string& option = "");

    // ostream for LorentzVector
    std::ostream& operator << (ostream& os, const LorentzVector& p4);

    // helper functions for OS operations (uses c++ name conventions)
    // -------------------------------------------------------------------------------------------------//

    // get an environment variable
    std::string getenv(const std::string& name);

    // copy a file
    bool copy_file(const std::string& source, const std::string& destination);

    // move a file
    bool move_file(const std::string& source, const std::string& destination);

    // get a vector of strings for all the files in path 
    std::vector<std::string> get_list_of_files(const std::string &path, bool show_hidden_files = false);

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

    // replace all occurrences of sub_str from str with new_sub_str (not working yet)
    std::string string_replace_all(const std::string& str, const std::string& sub_str, const std::string& new_sub_str);

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

    // print the value/error with +/-
    std::string pm(double value, double error, const std::string& precision = "1.2");
    std::string pm(const std::pair<double, double>& value_pair, const std::string& precision = "1.2");
    std::string pm(const std::pair<float, float>& value_pair, const std::string& precision = "1.2");

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

#endif // ifdef __CINT__

} // namespace rt


// implemenation of templated functions/classes (not in CINT)
// -------------------------------------------------------------------------------------------------//

#ifndef __CINT__
#include "MiscTools.impl.h"
#endif

#endif // RT_MISC_TOOLS_H 
