//------------------------------------------------------------------------//
// Tag & Probe Tools LinkDef.h
//------------------------------------------------------------------------//

#ifdef __CINT__  // interpreter and ACLiC

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions; 

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

//// namespaces
//#pragma link C++ namespace tp; 
//
//// typedefs
//#pragma link C++ enum tp::Model::value_type;
//
//// classes or structs
//#pragma link C++ struct tp::Model+;
//#pragma link C++ struct tp::Result+;
#pragma link C++ class RooCMSShape+;

// functions
//#pragma link C++ function tp::PerformSimultaneousFit;
//#pragma link C++ function tp::PerformSimpleCount;


#endif // __CINT__
