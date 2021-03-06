#ifndef OUTREACHCLOSURE_H
#define OUTREACHCLOSURE_H

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include <string>
#include "TH1F.h"
#include "boost/shared_ptr.hpp"

class OutreachClosure : public at::AnalysisWithHist
{
    public:
        // construct:
        OutreachClosure
        (
             const std::string& root_file_name,
             at::Sample::value_type sample,
             const std::string& fit_eff_file = "",
             bool verbose = false,
             bool print = false,
             const std::string& suffix = "png"
        );

        // destroy:
        ~OutreachClosure();

        // function operator:
        int operator()(long event);

        // members
        virtual void BeginJob();
        virtual void EndJob();
        virtual void BookHists();

    private:
        // members
        at::Sample::value_type m_sample;
        std::string m_fit_sample_name;
        bool m_verbose;

        // fake/flip rate hists
        boost::shared_ptr<TH1F> h_btagpt;
        boost::shared_ptr<TH1F> h_el_pt;
        boost::shared_ptr<TH1F> h_mu_pt;
        boost::shared_ptr<TH1F> h_el_id;
        boost::shared_ptr<TH1F> h_mu_id;
        boost::shared_ptr<TH1F> h_el_iso;
        boost::shared_ptr<TH1F> h_mu_iso;
        boost::shared_ptr<TH1F> h_genmet30;
        boost::shared_ptr<TH1F> h_genmet50;
        boost::shared_ptr<TH1F> h_genmet120;
        boost::shared_ptr<TH1F> h_ht200;
        boost::shared_ptr<TH1F> h_ht320;
};

#endif // OUTREACHCLOSURE_H
