#include "TList.h"
#include "TIterator.h"
#include "TRegexp.h"
#include "TFile.h"
#include "TObject.h"
#include "TKey.h"
#include "TH1.h"
#include "TStyle.h"
#include "TClass.h"

#include <iostream>

#include "histio.h"

void saveHist(const char* filename, const char* pat) {
	 TList* list = gDirectory->GetList();
	 TIterator* iter = list->MakeIterator();

	 TRegexp re(pat, kTRUE);

	 TFile outf(filename, "RECREATE");
	 TObject* obj;
	 while ((obj = iter->Next())) {    
		  if (TString(obj->GetName()).Index(re) >= 0) {
			   obj->Write() ;
			   std::cout << "." ;
			   std::cout.flush() ;
		  }
	 }

	 std::cout << std::endl ;
	 outf.Close() ;

	 delete iter ;
}


void loadHist(const char* filename, const char* pfx, const char* pat, Bool_t doAdd) {
	 TFile inf(filename);
	 TList* list = inf.GetListOfKeys();
	 TIterator* iter = list->MakeIterator();

	 TRegexp re(pat, kTRUE);
	 std::cout << "pat = " << pat << std::endl;

	 gDirectory->cd("Rint:");

	 TObject* obj;
	 TKey* key;
	 std::cout << "doAdd = " << (doAdd ? "T" : "F") << std::endl;
	 std::cout << "loadHist: reading.";
	 while ((key = dynamic_cast<TKey*>(iter->Next()))) {
   
		  Int_t ridx = TString(key->GetName()).Index(re);
		  if (ridx == -1)
			   continue;

		  obj = inf.Get(key->GetName());
		  TObject* clone;
		  if (pfx) {

			   // Find existing TH1-derived objects
			   TObject* oldObj = 0 ;
			   if (doAdd) {
					oldObj = gDirectory->Get(Form("%s_%s", pfx, obj->GetName()));
					if (oldObj && !oldObj->IsA()->InheritsFrom(TH1::Class()))
						 oldObj = 0;
			   }
			   if (oldObj) {
					clone = oldObj;
					((TH1*)clone)->Add((TH1*)obj);
			   } else
					clone = obj->Clone(Form("%s_%s", pfx, obj->GetName()));
		  } else {

			   // Find existing TH1-derived objects
			   TObject* oldObj = 0;
			   if (doAdd) {
					oldObj = gDirectory->Get(key->GetName());
					if (oldObj && !oldObj->IsA()->InheritsFrom(TH1::Class()))
						 oldObj = 0;
			   }
			   if (oldObj) {
					clone = oldObj;
					((TH1*)clone)->Add((TH1*)obj);
			   } else
					clone = obj->Clone();
		  }
		  if (!gDirectory->GetList()->FindObject(clone))
			   gDirectory->Append(clone);

		  std::cout << ".";
		  std::cout.flush();
	 }

	 std::cout << std::endl;
	 inf.Close();
	 delete iter;
}
