//------------------------------------------------------------------------//
// FakeRateStudy LinkDef.h Kelley 2012-05-03
//------------------------------------------------------------------------//

#ifdef __CINT__  // interpreter and ACLiC

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// namespaces
#pragma link C++ namespace fr;

// enum
#pragma link C++ enum fr::Sample::value_type;

// classes
#pragma link C++ struct fr::Sample+;

// functions
#pragma link C++ function fr::GetSampleFromName(const std::string&);
#pragma link C++ function fr::GetSampleInfo(const Sample::value_type&);
#pragma link C++ function fr::GetSampleInfo(const std::string&);
#pragma link C++ function fr::GetSampleTChain(const Sample::value_type&); 

// templates
//#pragma link C++ class std::vector<DataSet>+;

#endif // __CINT__

