#ifndef PLOTLOOPER_H
#define PLOTLOOPER_H

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include <string>
#include <tr1/memory>
#include "TH1F.h"

class PlotLooper : public at::AnalysisWithHist
{
    public:
        // construct:
        PlotLooper
        (
            const std::string& root_file_name,
            at::Sample::value_type sample,
            const std::string& pdf_hist_file_name,
			float iso_cut = 0.1,
			bool derive_pdf = false,
            bool verbose = false
        );

        // destroy:
        ~PlotLooper();

        // function operator:
        int operator()(long event);

        // members
        virtual void BeginJob();
        virtual void EndJob();
        virtual void BookHists();

    private:
        // members
        const bool m_verbose;
		const float m_iso_cut;
		const bool m_derive_pdf;
        const at::Sample::value_type m_sample;

        // fake/flip rate hists
        std::tr1::shared_ptr<TH1F> h_pdf;

        // help function to extract eff from pdf
        float GetEffFromPDF(float x);
};

#endif // PLOTLOOPER_HPP
