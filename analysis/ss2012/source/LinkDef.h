//------------------------------------------------------------------------//
// SS2012 Tools LinkDef.h Kelley 2011-05-01
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

// templated classes

// classes or structs
#pragma link C++ struct ss::SignalRegion;

// functions
#pragma link C++ function ss::GetSignalRegionFromName;
#pragma link C++ function ss::GetSignalRegionInfo;
#pragma link C++ function ss::GetSignalRegionInfo;

#endif // __CINT__
