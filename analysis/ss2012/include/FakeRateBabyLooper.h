#ifndef SS_FAKERATEBABYLOOPER_H
#define SS_FAKERATEBABYLOOPER_H

#include "at/AnalysisWithHist.h"
#include <string>

class FakeRateBabyLooper : public at::AnalysisWithHist
{
public:
    // construct:
    FakeRateBabyLooper
    (
        const std::string& root_file_name,
        const std::string& dataset,
        const std::string& lepton,
        float lumi = 1.0,
        int charge = 0,
        bool verbose = false,
        bool print = false,
        const std::string& suffix = "png"
        );

    // destroy:
    ~FakeRateBabyLooper();

    // function operator:
    int operator()(long event, const std::string& current_file_name = "");

    // members
    virtual void BeginJob();
    virtual void EndJob();
    virtual void BookHists();    

private:
    // members
    std::string m_dataset;
    std::string m_lepton;
    float m_lumi;
    int m_charge;
    bool m_verbose;
};

#endif // SS_FAKERATEBABYLOOPER_HPP
