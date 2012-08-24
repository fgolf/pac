//------------------------------------------------------------------------//
// AnalysisTools LinkDef.h Kelley 2011-05-01
//------------------------------------------------------------------------//

#ifdef __CINT__  // interpreter and ACLiC

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions; 

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// namespaces
#pragma link C++ namespace at;

// typedefs
#pragma link C++ enum at::Sample::value_type;
#pragma link C++ enum at::NtupleType::value_type;
#pragma link C++ enum at::DileptonHypType::value_type;
#pragma link C++ enum at::DileptonChargeType::value_type;

// templated classes

// classes or structs
#pragma link C++ struct at::Sample;
#pragma link C++ struct at::SampleInfo;
#pragma link C++ struct at::DileptonHypType;
#pragma link C++ struct at::DileptonChargeType;

// functions
#pragma link C++ function at::GetSampleInfo;
#pragma link C++ function at::GetSampleFromName;
#pragma link C++ function at::GetSampleTChain;
#pragma link C++ function at::GetNtuplePath;
#pragma link C++ function at::GetNtuplePath;
#pragma link C++ function at::GetNtupleTypeFromName;

#endif // __CINT__
