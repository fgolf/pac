#ifndef SS_FAKEPREDLOOPER_H
#define SS_FAKEPREDLOOPER_H

#include "at/AnalysisWithHist.h"
#include <string>
#include <vector>
#include "TH2F.h"

struct FakeRate
{
    FakeRate(const std::string& file_name, const std::string& hist_name);
	~FakeRate();
    float GetValue(float pt, float eta, float mc3pt) const;
    float GetError(float pt, float eta, float mc3pt) const;
    float GetValue(float pt, float eta) const;
    float GetError(float pt, float eta) const;
    float GetValue(float pt) const;
    float GetError(float pt) const;
    TH1* h_fake_rate;
};

struct FO
{
    FO(float fo_pt, float fo_eta, float fo_fr, float fo_frerr)
        : pt(fo_pt)
        , aeta(fabs(fo_eta))
        , fr(fo_fr)
        , frerr(fo_frerr)
    {}

    float pt;
    float aeta;
    float fr;
    float frerr;
};

struct SF
{
    SF(FO f) 
        : fo(f) 
    {}
    SF(float fo_pt, float fo_eta, float fo_fr, float fo_frerr) 
        : fo(fo_pt, fo_eta, fo_fr, fo_frerr) 
    {}
    FO fo;
};

struct DF
{
    DF(FO f1, FO f2) : fo1(f1), fo2(f2) {}
    DF(float fo_pt1, float fo_eta1, float fo_fr1, float fo_frerr1,
       float fo_pt2, float fo_eta2, float fo_fr2, float fo_frerr2) 
        : fo1(fo_pt1, fo_eta1, fo_fr1, fo_frerr1)
        , fo2(fo_pt2, fo_eta2, fo_fr2, fo_frerr2) 
    {}
    FO fo1;
    FO fo2;
};

class FakePredLooper : public at::AnalysisWithHist
{
    public:
        // construct:
        FakePredLooper
        (
             const std::string& root_file_name,
             const std::string& vtxreweight_file_name = "",
             const std::string& fr_file_name = "",
             const std::string& fr_hist_name = "",
             unsigned int num_btags = 0,
             bool directb = false,
             float lumi = 1.0,
             bool verbose = false,
             bool print = false,
             const std::string& suffix = "png"
        );

        // destroy:
        ~FakePredLooper();

        // function operator:
        int operator()(long event);

        // members
        virtual void BeginJob();
        virtual void EndJob();
        virtual void BookHists();

    private:
        // members
        float m_lumi;
        bool m_verbose;
        unsigned int m_nbtags;
        bool m_directb;
		std::string m_fr_file_name;

		FakeRate m_fr;
        std::vector<SF> m_sf;
        std::vector<DF> m_df;
};

#endif // SS_FAKEPREDLOOPER_H
