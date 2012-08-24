#include <algorithm>
#include <set>
#include "Math/VectorUtil.h"
#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TMath.h"
#include "TList.h"
#include "TRegexp.h"
#include "TDirectory.h"
#include "tools.h"
#include "CMS2.h"

// use this directory to store our histograms (so they can be written to file in one fell swoop)
TDirectory *histo_directory = new TDirectory("histo_directory", "directory for all our histograms");

void progressBar(int& i_permille_old, int nEventsTotal, int nEventsChain) {
  // 
  // progress bar
  //
  int i_permille = (int)floor(1000 * nEventsTotal / float(nEventsChain));
  if (i_permille != i_permille_old) {
    // xterm magic from L. Vacavant and A. Cerri
    printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
	   "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
    fflush(stdout);
    i_permille_old = i_permille;
  }
}

DorkyEventIdentifier::DorkyEventIdentifier (CMS2 &cms2)
     : run(cms2.evt_run()),
       event(cms2.evt_event()),
       lumi_section(cms2.evt_lumiBlock()),
       trks_d0(cms2.trks_d0().at(0)), // use at() because that way we
				      // get an exception if we are
				      // out of bounds
       trks_pt (cms2.trks_trk_p4().at(0).pt()),
       trks_eta(cms2.trks_trk_p4().at(0).eta()),
       trks_phi(cms2.trks_trk_p4().at(0).phi()) { }

DorkyEventIdentifier::DorkyEventIdentifier (unsigned long int r, unsigned long int e, unsigned long int l)
     : run(r),
       event(e),
       lumi_section(l),
       trks_d0(0),
       trks_pt (0),
       trks_eta(0),
       trks_phi(0) { }

bool DorkyEventIdentifier::operator < (const DorkyEventIdentifier &other) const
{
     if (run != other.run)
          return run < other.run;
     if (event != other.event)
          return event < other.event;
     if (lumi_section != other.lumi_section)
          return lumi_section < other.lumi_section;
     if (TMath::Abs(trks_d0 - other.trks_d0) > 1e-6 * fabs(trks_d0))
       return trks_d0 < other.trks_d0;
     if (TMath::Abs(trks_pt - other.trks_pt) > 1e-6 * fabs(trks_pt))
       return trks_pt < other.trks_pt;
     if (TMath::Abs(trks_eta - other.trks_eta) > 1e-6 * fabs(trks_eta))
       return trks_eta < other.trks_eta;
     if (TMath::Abs(trks_phi - other.trks_phi) > 1e-6 * fabs(trks_phi))
       return trks_phi < other.trks_phi;
     return false;
}

bool DorkyEventIdentifier::operator == (const DorkyEventIdentifier &other) const
{
     if (run != other.run)
          return false;
     if (event != other.event)
          return false;
     if (lumi_section != other.lumi_section)
          return false;
     if (TMath::Abs(trks_d0 - other.trks_d0) > 1e-6 * fabs(trks_d0))
          return false;
     if (TMath::Abs(trks_pt - other.trks_pt) > 1e-6 * fabs(trks_pt))
          return false;
     if (TMath::Abs(trks_eta - other.trks_eta) > 1e-6 * fabs(trks_eta))
          return false;
     if (TMath::Abs(trks_phi - other.trks_phi) > 1e-6 * fabs(trks_phi))
          return false;
     return true;
}

std::set<DorkyEventIdentifier> already_seen;

bool is_duplicate (const DorkyEventIdentifier &id)
{
     std::pair<std::set<DorkyEventIdentifier>::const_iterator, bool> ret =
          already_seen.insert(id);
     return !ret.second;
}

double dRbetweenVectors (const LorentzVector &vec1, const LorentzVector &vec2 )
{ 
  double dphi = std::min(::fabs(vec1.Phi() - vec2.Phi()), 2 * M_PI - fabs(vec1.Phi() - vec2.Phi()));
  double deta = vec1.Eta() - vec2.Eta();
  return sqrt(dphi*dphi + deta*deta);
}
