// -*- C++ -*-

#ifndef TOOLS_H
#define TOOLS_H

#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TVector3.h"
#include <algorithm>
#include <vector>
#include <set>
#include "Math/VectorUtil.h"

using std::vector;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

struct DorkyEventIdentifier {
     // this is a workaround for not having unique event id's in MC 
     DorkyEventIdentifier (class CMS2 &cms2);
     DorkyEventIdentifier (unsigned long int r, unsigned long int e, unsigned long int l);
     unsigned long int run, event, lumi_section;
     float trks_d0;
     float trks_pt, trks_eta, trks_phi;
     bool operator < (const DorkyEventIdentifier &) const;
     bool operator == (const DorkyEventIdentifier &) const;
};

extern std::set<DorkyEventIdentifier> already_seen;

bool is_duplicate (const DorkyEventIdentifier &id);

extern class TDirectory *histo_directory;

double dRbetweenVectors(const LorentzVector & vec1, const LorentzVector & vec2 );
#endif
