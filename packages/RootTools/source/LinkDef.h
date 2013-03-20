//------------------------------------------------------------------------//
// root_tools' link_def.h Kelley 2011-05-01
//------------------------------------------------------------------------//

#ifdef __CINT__  // interpreter and ACLiC

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions; 

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// namespaces
#pragma link C++ namespace rt;

// typedefs
#pragma link C++ typedef rt::TFilePtr;
#pragma link C++ typedef rt::TH1Ptr;
#pragma link C++ struct rt::DrawType;
#pragma link C++ struct rt::LegendPlacement;
#pragma link C++ struct rt::StatBoxPlacement;
#pragma link C++ typedef rt::dt;
#pragma link C++ typedef rt::lg;
#pragma link C++ typedef rt::sb;
#pragma link C++ enum rt::DrawType::value_type;
#pragma link C++ enum rt::LegendPlacement::value_type;
#pragma link C++ enum rt::StatBoxPlacement::value_type;

// templated classes
#pragma link C++ class std::map<std::string, rt::TH1Ptr>+;
#pragma link C++ class std::map<std::string, rt::TH1Ptr>::iterator;
#pragma link C++ class std::map<std::string, rt::TH1Ptr>::const_iterator;
#pragma link C++ class std::pair<std::string, rt::TH1Ptr>+;
#pragma link C++ class std::vector<rt::TH1Ptr>+;
#pragma link C++ class std::vector<rt::TH1Ptr>::iterator;
#pragma link C++ class std::vector<rt::TH1Ptr>::const_iterator;
#pragma link C++ class std::map<std::string, rt::TH1Overlay>+;
#pragma link C++ class std::map<std::string, rt::TH1Overlay>::iterator;
#pragma link C++ class std::map<std::string, rt::TH1Overlay>::const_iterator;
#pragma link C++ class std::map<std::string, rt::TH1Overlay*>+;
#pragma link C++ class std::map<std::string, rt::TH1Overlay*>::iterator;
#pragma link C++ class std::map<std::string, rt::TH1Overlay*>::const_iterator;
#pragma link C++ class std::vector<std::string>+; 
#pragma link C++ class std::vector<vector<std::string> >+; 
#pragma link C++ class std::vector<TChain*>+; 
#pragma link C++ class std::vector<TTree*>+; 

// classes
#pragma link C++ class rt::TH1Container+;
#pragma link C++ class rt::TH1Overlay+;

// functions
#pragma link C++ function rt::GetHistFromRootFile<TH1>;
#pragma link C++ function rt::GetHistFromRootFile<TH1D>;
#pragma link C++ function rt::GetHistFromRootFile<TH1F>;
#pragma link C++ function rt::GetHistFromRootFile<TH2>;
#pragma link C++ function rt::GetHistFromRootFile<TH2D>;
#pragma link C++ function rt::GetHistFromRootFile<TH2F>;
#pragma link C++ fucntion rt::AddWithError;
#pragma link C++ fucntion rt::SubtractWithError;
#pragma link C++ fucntion rt::MultiplyWithError;
#pragma link C++ fucntion rt::DivideWithError;
#pragma link C++ function rt::OpenRootFile;
#pragma link C++ function rt::Scale;
#pragma link C++ function rt::Fill;
#pragma link C++ function rt::Fill2D;
#pragma link C++ function rt::TTreeDraw1D;
#pragma link C++ function rt::Mt;
#pragma link C++ function rt::DeltaPhi;
#pragma link C++ function rt::DeltaR;
#pragma link C++ function rt::GetMapOfTH1s;
#pragma link C++ function rt::GetVectorOfTH1s;
#pragma link C++ fucntion rt::Integral;
#pragma link C++ fucntion rt::IntegralAndError;
#pragma link C++ fucntion rt::EntriesAndError;
#pragma link C++ fucntion rt::CalcErrorsForProfile;
#pragma link C++ fucntion rt::MakeProjectionPlot;
#pragma link C++ fucntion rt::MakeEfficiencyProjectionPlot;
#pragma link C++ fucntion rt::MakeEfficienyPlot;
#pragma link C++ fucntion rt::PrintFakeRateTable;
#pragma link C++ fucntion rt::PrintFilesFromTChain;
#pragma link C++ fucntion rt::CompareContentsOfTTrees;
#pragma link C++ fucntion rt::MergeTChain;
#pragma link C++ fucntion rt::pm;
#pragma link C++ fucntion rt::Print;
#pragma link C++ fucntion rt::Print<rt::TH1Overlay>;
#pragma link C++ fucntion rt::Print<rt::TH1Overlay*>;
#pragma link C++ fucntion rt::Write;
#pragma link C++ fucntion rt::CopyIndexPhp;
#pragma link C++ fucntion rt::getenv;
#pragma link C++ fucntion rt::is_equal;
#pragma link C++ fucntion rt::is_zero;
#pragma link C++ fucntion rt::pm;
#pragma link C++ fucntion rt::TDRGrid;
#pragma link C++ fucntion rt::FixOverlay;
#pragma link C++ fucntion rt::SetTDRStyle;
#pragma link C++ fucntion rt::MakeTChain;
#pragma link C++ fucntion rt::CreateTChainFromCommaSeperatedList;
#pragma link C++ fucntion rt::CreateTableFromHist;
#pragma link C++ fucntion rt::SetSystematicUncertainty;
#pragma link C++ fucntion rt::MultiplyHists;
#pragma link C++ fucntion rt::DivideHists;

// constructors
#pragma link C++ function rt::TH1Container::TH1Container;

#endif // __CINT__
