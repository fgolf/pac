//------------------------------------------------------------------------//
// SS2012 Tools LinkDef.h Kelley 2012-09-07
//------------------------------------------------------------------------//

#ifdef __CINT__  // interpreter and ACLiC

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions; 

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// namespaces
#pragma link C++ namespace ewkino;
#pragma link C++ namespace ewkino_ss;

// typedefs
#pragma link C++ enum ewkino::SignalRegion::value_type;
#pragma link C++ enum ewkino::AnalysisType::value_type;
#pragma link C++ enum ewkino::SignalRegionType::value_type;

// templated classes

// classes or structs
#pragma link C++ struct ewkino::SignalRegion+;
#pragma link C++ struct ewkino::AnalysisType+;
#pragma link C++ struct ewkino_ss::Yield+;
#pragma link C++ struct ewkino::SignalBinInfo+;

// functions
#pragma link C++ function ewkino::GetSignalRegionFromName;
#pragma link C++ function ewkino::GetSignalRegionInfo;
#pragma link C++ function ewkino::GetSignalRegionTypeName;
#pragma link C++ function ewkino::GetSignalRegionTypeFromName;
#pragma link C++ function ewkino::SetSignalRegionAliases;

#pragma link C++ function ewkino::GetAnalysisTypeFromName;
#pragma link C++ function ewkino::GetAnalysisTypeInfo;
#pragma link C++ function ewkino::SetAnalysisTypeAliases;

#pragma link C++ function operator-;
#pragma link C++ function operator+;
#pragma link C++ function operator*;
#pragma link C++ function ewkino_ss::SetErrorsToBogus;
#pragma link C++ function ewkino_ss::SetSysUncertainties;
#pragma link C++ function ewkino_ss::DetermineError;
#pragma link C++ function ewkino_ss::AddUncertaintiesAbsolute;
#pragma link C++ function ewkino_ss::GetSampleHists;
#pragma link C++ function ewkino_ss::GetSSYield;
#pragma link C++ function ewkino_ss::GetDFYield;
#pragma link C++ function ewkino_ss::GetSFYield;
#pragma link C++ function ewkino_ss::GetFakeYield;
#pragma link C++ function ewkino_ss::GetFlipYield;
#pragma link C++ function ewkino_ss::GetYield;
#pragma link C++ function ewkino_ss::GetYieldsMap;

#endif // __CINT__
