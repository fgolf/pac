#ifndef SS_FAKERATEBABYLOOPERETH_H
#define SS_FAKERATEBABYLOOPERETH_H

#include "at/AnalysisWithHist.h"
#include <string>

class FakeRateBabyLooperETH : public at::AnalysisWithHist
{
public:
    // construct:
    FakeRateBabyLooperETH
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
    ~FakeRateBabyLooperETH();

    // function operator:
    int operator()(long event);

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
};

#endif // SS_FAKERATEBABYLOOPERETH_HPP
