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
#pragma link C++ namespace ss; 

// typedefs
#pragma link C++ enum ss::SignalRegion::value_type;
#pragma link C++ enum ss::AnalysisType::value_type;
#pragma link C++ enum ss::SignalRegionType::value_type;

// templated classes

// classes or structs
#pragma link C++ struct ss::SignalRegion+;
#pragma link C++ struct ss::AnalysisType+;

// functions
#pragma link C++ function ss::GetSignalRegionFromName;
#pragma link C++ function ss::GetSignalRegionInfo;
#pragma link C++ function ss::GetSignalRegionTypeName;
#pragma link C++ function ss::GetSignalRegionTypeFromName;
#pragma link C++ function ss::SetSignalRegionAliases;

#pragma link C++ function ss::GetAnalysisTypeFromName;
#pragma link C++ function ss::GetAnalysisTypeInfo;
#pragma link C++ function ss::SetAnalysisTypeAliases;

#endif // __CINT__
