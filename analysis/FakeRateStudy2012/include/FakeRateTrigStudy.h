#ifndef SS_FAKERATEBABYLOOPER_H
#define SS_FAKERATEBABYLOOPER_H

#include "at/AnalysisWithHist.h"
#include "fr/Sample.h"
#include <string>

class FakeRateTrigStudy : public at::AnalysisWithHist
{
    public:
        // construct:
        FakeRateTrigStudy
        (
             const std::string& root_file_name,
             const fr::Sample::value_type& sample,
             const std::string& lepton,
			 float lumi = 1.0,
             bool verbose = false,
             bool print = false,
             const std::string& suffix = "png"
        );

        // destroy:
        ~FakeRateTrigStudy();

        // function operator:
        int operator()(long event);

        // members
        virtual void BeginJob();
        virtual void EndJob();
        virtual void BookHists();

    private:
        // members
        fr::Sample::value_type m_sample;
        std::string m_lepton;
		float m_lumi;
        bool m_verbose;

};

#endif // SS_FAKERATEBABYLOOPER_H
