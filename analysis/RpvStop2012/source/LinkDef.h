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
#pragma link C++ namespace rpv_stop;

// typedefs
#pragma link C++ enum rpv_stop::SignalRegion::value_type;
#pragma link C++ enum rpv_stop::AnalysisType::value_type;
#pragma link C++ enum rpv_stop::SignalRegionType::value_type;

// templated classes

// classes or structs
#pragma link C++ struct rpv_stop::SignalRegion+;
#pragma link C++ struct rpv_stop::AnalysisType+;

// functions
#pragma link C++ function rpv_stop::GetSignalRegionFromName;
#pragma link C++ function rpv_stop::GetSignalRegionInfo;
#pragma link C++ function rpv_stop::GetSignalRegionTypeName;
#pragma link C++ function rpv_stop::GetSignalRegionTypeFromName;
#pragma link C++ function rpv_stop::SetSignalRegionAliases;

#pragma link C++ function rpv_stop::GetAnalysisTypeFromName;
#pragma link C++ function rpv_stop::GetAnalysisTypeInfo;
#pragma link C++ function rpv_stop::SetAnalysisTypeAliases;

#endif // __CINT__
