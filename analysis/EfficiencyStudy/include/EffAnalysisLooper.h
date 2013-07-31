#ifndef EFFANALYSISLOOPER_H 
#define EFFANALYSISLOOPER_H

#include "at/AnalysisWithTree.h"
#include "at/Sample.h"
#include "Math/LorentzVector.h"
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <string>
#include "EfficiencyTree.h"

class TH2F;
class FactorizedJetCorrector;
class MetCorrector;

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class EffAnalysisLooper : public at::AnalysisWithTree
{
    public:
        // construct:
        EffAnalysisLooper
        (
             const std::string& root_file_name,
             const at::Sample::value_type& sample,
             double luminosity = 1.0,
             bool verbose = false
        );

        // destroy:
        ~EffAnalysisLooper();

        // function operator:
        int operator() (long event, const std::string& filename);

        // members:
        virtual void BeginJob();
        virtual void EndJob();
        int Analyze(long event, const std::string& filename);

    private:
        // members:
        at::Sample::value_type m_sample;
        double m_lumi;
        bool m_verbose;

        // struct to hold tree values
        EfficiencyTree m_evt;

};

#endif // EFFANALYSISLOOPER_H 
