
#ifndef EFF_H
#define EFF_H

#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include "TString.h"
#include <vector> 
#include <string>          

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// Handle Classes to handle branch loading 
// ------------------------------------------------------------------------------------------------- //

namespace eff
{
    struct BranchType
    {
        enum value_type
        {
            CLASS,
            BUILTIN,
            NOT_SET,

            static_size
        };
    };

    template <typename T>
    class Handle
    {
        public:
            
            // construct: 
            explicit Handle(const std::string& branch_name);

            // destroy:
            virtual ~Handle() {}

            // set the branch's entry 
            void GetEntry(const unsigned int entry);

            // initialize the handle's branches
            void Init(TTree& tree);

            // is the branch already loaded
            bool IsLoaded() const;

            // load the branch
            void Load();

            // clear the branch
            void Clear();

            // get the value
            const T& get();

        protected:

            // set the branch type private member (based on the TBranch) 
            void SetBranchType(const std::string& branch_class);

            // members:
            bool                   m_is_loaded;
            unsigned int           m_entry;
            std::string            m_branch_name;
            T*                     m_object_ptr;
            T                      m_object;
            BranchType::value_type m_branch_type;

            // the TTree owns the branch (this is only a reference pointer)
            TBranch*     m_branch;

        private:
            // no default constructor
            Handle() {}
    };

    template <typename T>
    /*explicit*/ Handle<T>::Handle(const std::string& branch_name)
        : m_is_loaded(false)
        , m_entry(0)
        , m_branch_name(branch_name)
        , m_object_ptr(NULL)
        , m_object()
        , m_branch_type(BranchType::NOT_SET)
        , m_branch(NULL)
    {
    }

    template <typename T>
    void Handle<T>::GetEntry(const unsigned int entry)
    {
        Clear();
        m_entry = entry;
    }

    template <typename T>
    bool Handle<T>::IsLoaded() const
    {
        return m_is_loaded;
    }
   
    template <typename T>
    void Handle<T>::Clear()
    {
        m_is_loaded = false;
    }

    template <typename T>
    void Handle<T>::Load()
    {
        if (m_branch)
        {
            m_branch->GetEntry(m_entry);
            m_is_loaded = true;
        }
        else
        {
            throw std::runtime_error("[EFF] ERROR: branch " + m_branch_name + " does not exist!"); 
        }
    }

    template <typename T>
    void Handle<T>::SetBranchType(const std::string& branch_class)
    {
        if (branch_class.find("edm::Wrapper")!=std::string::npos)
        {
            m_branch_type = BranchType::BUILTIN;
        }
        else if 
        (
            branch_class.find("/B")!=std::string::npos || // char
            branch_class.find("/b")!=std::string::npos || // unsigned char
            branch_class.find("/S")!=std::string::npos || // short
            branch_class.find("/s")!=std::string::npos || // unsigned short
            branch_class.find("/I")!=std::string::npos || // int
            branch_class.find("/i")!=std::string::npos || // unsigned int
            branch_class.find("/F")!=std::string::npos || // float
            branch_class.find("/D")!=std::string::npos || // double
            branch_class.find("/L")!=std::string::npos || // long
            branch_class.find("/l")!=std::string::npos || // unsigned long
            branch_class.find("/O")!=std::string::npos    // bool
        )
        {
            m_branch_type = BranchType::BUILTIN;
        }
        else
        {
            m_branch_type = BranchType::CLASS;
        }
    }

    template <typename T>
    void Handle<T>::Init(TTree& tree)
    {
        // no protection if the branch pointer is NULL
        // (so you can use this if the branch doesn't exist
        // as long as you don't call it).
        m_branch = tree.GetBranch(m_branch_name.c_str());
        if (m_branch)
        {
            if (m_branch_type == BranchType::NOT_SET)
            {
                std::string branch_class = m_branch->GetClassName();
                if (branch_class.empty())  // built in types don't have a ClassName --> using title
                {
                    branch_class = m_branch->GetTitle();
                }
                SetBranchType(branch_class);
            }
            switch (m_branch_type)
            {
                case BranchType::CLASS  : m_branch->SetAddress(&m_object_ptr); break;
                case BranchType::BUILTIN: m_branch->SetAddress(&m_object)    ; break;
                default: throw std::runtime_error("[EFF] ERROR: branch type not supported!"); 
            }
        }
    }

    template <typename T>
    const T& Handle<T>::get()
    {
        if (not IsLoaded())
        {
            Load();
        }
        switch (m_branch_type)
        {
            case BranchType::CLASS  : return *m_object_ptr;
            case BranchType::BUILTIN: return m_object;
            default: throw std::runtime_error("[EFF] ERROR: branch type not supported!"); 
        }
    }
    
} // namespace eff


// EFF to handle all the branches for the TTree 
// ------------------------------------------------------------------------------------------------- //

class EFF
{
    public:
        EFF();

        // methods:
        void Init(TTree* const tree);
        void Init(TTree& tree);
        void GetEntry(const unsigned int entry);
		void LoadAllBranches();


       	// static methods:
       	static void progress(const int nEventsTotal, const int nEventsChain);

        // branch accessors
        const unsigned int& run();
        const unsigned int& ls();
        const unsigned int& evt();
        const bool& is_real_data();
        const int& sample();
        const int& nvtxs();
        const int& vtx_idx();
        const float& pfmet();
        const float& pfmet_phi();
        const float& uncorpfmet();
        const float& uncorpfmet_phi();
        const float& pu_nvtxs();
        const float& pu_ntrueint();
        const float& scale1fb();
        const float& xsec();
        const unsigned int& nevts();
        const float& kfactor();
        const float& gen_met();
        const float& gen_met_phi();
        const TString& dataset();
        const TString& filename();
        const int& gen_nleps();
        const int& gen_nels();
        const int& gen_nmus();
        const int& gen_ntaus();
        const int& gen_nleps_with_fromtau();
        const int& gen_nels_with_fromtau();
        const int& gen_nmus_with_fromtau();
        const int& gen_ntaus_with_fromtau();
        const bool& filt_csc();
        const bool& filt_hbhe();
        const bool& filt_hcallaser();
        const bool& filt_ecallaser();
        const bool& filt_ecaltp();
        const bool& filt_trkfail();
        const bool& filt_eebadsc();
        const bool& passes_metfilters();
        const bool& passes_id();
        const bool& passes_iso();
        const bool& is_num();
        const bool& is_den();
        const bool& is_fo();
        const bool& is_mu();
        const bool& is_el();
        const bool& exists();
        const int& is_fromw();
        const int& charge();
        const int& pdgid();
        const int& type();
        const float& d0();
        const float& d0err();
        const float& dz();
        const float& ip3d();
        const float& ip3derr();
        const float& dzerr();
        const float& mt();
        const float& corpfiso();
        const float& pfiso();
        const float& chiso();
        const float& emiso();
        const float& nhiso();
        const float& corpfiso04();
        const float& pfiso04();
        const float& chiso04();
        const float& emiso04();
        const float& nhiso04();
        const float& cordetiso();
        const float& detiso();
        const float& trkiso();
        const float& ecaliso();
        const float& hcaliso();
        const float& cordetiso04();
        const float& detiso04();
        const float& trkiso04();
        const float& ecaliso04();
        const float& hcaliso04();
        const float& effarea();
        const float& effarea04();
        const float& dbeta();
        const float& dbeta04();
        const float& sf_lepeff();
        const float& sf_trig();
        const int& mcid();
        const int& mc3id();
        const int& momid();
        const int& mc3_momid();
        const bool& q3agree();
        const bool& is_conv();
        const int& qsc();
        const int& qctf();
        const int& qgsf();
        const int& nmhits();
        const int& eleid_veto();
        const int& eleid_loose();
        const int& eleid_medium();
        const int& eleid_tight();
        const bool& is_eleid_veto();
        const bool& is_eleid_loose();
        const bool& is_eleid_medium();
        const bool& is_eleid_tight();
        const float& dphiin();
        const float& detain();
        const float& sieie();
        const float& hoe();
        const float& ooemoop();
        const float& conv_dist();
        const float& conv_dcot();
        const bool& is_global();
        const bool& is_tracker();
        const bool& is_stamu();
        const bool& is_pfmu();
        const bool& is_loosemu();
        const bool& is_tightmu();
        const int& npixelhits();
        const int& nsihits();
        const int& nsilayers();
        const int& nstahits();
        const int& nstations();
        const float& chi2();
        const float& ndof();
        const float& pterr();
        const float& ecal_vetodep();
        const float& hcal_vetodep();
        const LorentzVector& p4();
        const LorentzVector& mcp4();
        const LorentzVector& mc3p4();
        const LorentzVector& mc_momp4();
        const LorentzVector& gsf_p4();
        const LorentzVector& ctf_p4();
        const LorentzVector& sc_p4();
        const LorentzVector& gfit_p4();

    private:
    
        // handles
        eff::Handle< unsigned int > run_handle;
        eff::Handle< unsigned int > ls_handle;
        eff::Handle< unsigned int > evt_handle;
        eff::Handle< bool > is_real_data_handle;
        eff::Handle< int > sample_handle;
        eff::Handle< int > nvtxs_handle;
        eff::Handle< int > vtx_idx_handle;
        eff::Handle< float > pfmet_handle;
        eff::Handle< float > pfmet_phi_handle;
        eff::Handle< float > uncorpfmet_handle;
        eff::Handle< float > uncorpfmet_phi_handle;
        eff::Handle< float > pu_nvtxs_handle;
        eff::Handle< float > pu_ntrueint_handle;
        eff::Handle< float > scale1fb_handle;
        eff::Handle< float > xsec_handle;
        eff::Handle< unsigned int > nevts_handle;
        eff::Handle< float > kfactor_handle;
        eff::Handle< float > gen_met_handle;
        eff::Handle< float > gen_met_phi_handle;
        eff::Handle< TString > dataset_handle;
        eff::Handle< TString > filename_handle;
        eff::Handle< int > gen_nleps_handle;
        eff::Handle< int > gen_nels_handle;
        eff::Handle< int > gen_nmus_handle;
        eff::Handle< int > gen_ntaus_handle;
        eff::Handle< int > gen_nleps_with_fromtau_handle;
        eff::Handle< int > gen_nels_with_fromtau_handle;
        eff::Handle< int > gen_nmus_with_fromtau_handle;
        eff::Handle< int > gen_ntaus_with_fromtau_handle;
        eff::Handle< bool > filt_csc_handle;
        eff::Handle< bool > filt_hbhe_handle;
        eff::Handle< bool > filt_hcallaser_handle;
        eff::Handle< bool > filt_ecallaser_handle;
        eff::Handle< bool > filt_ecaltp_handle;
        eff::Handle< bool > filt_trkfail_handle;
        eff::Handle< bool > filt_eebadsc_handle;
        eff::Handle< bool > passes_metfilters_handle;
        eff::Handle< bool > passes_id_handle;
        eff::Handle< bool > passes_iso_handle;
        eff::Handle< bool > is_num_handle;
        eff::Handle< bool > is_den_handle;
        eff::Handle< bool > is_fo_handle;
        eff::Handle< bool > is_mu_handle;
        eff::Handle< bool > is_el_handle;
        eff::Handle< bool > exists_handle;
        eff::Handle< int > is_fromw_handle;
        eff::Handle< int > charge_handle;
        eff::Handle< int > pdgid_handle;
        eff::Handle< int > type_handle;
        eff::Handle< float > d0_handle;
        eff::Handle< float > d0err_handle;
        eff::Handle< float > dz_handle;
        eff::Handle< float > ip3d_handle;
        eff::Handle< float > ip3derr_handle;
        eff::Handle< float > dzerr_handle;
        eff::Handle< float > mt_handle;
        eff::Handle< float > corpfiso_handle;
        eff::Handle< float > pfiso_handle;
        eff::Handle< float > chiso_handle;
        eff::Handle< float > emiso_handle;
        eff::Handle< float > nhiso_handle;
        eff::Handle< float > corpfiso04_handle;
        eff::Handle< float > pfiso04_handle;
        eff::Handle< float > chiso04_handle;
        eff::Handle< float > emiso04_handle;
        eff::Handle< float > nhiso04_handle;
        eff::Handle< float > cordetiso_handle;
        eff::Handle< float > detiso_handle;
        eff::Handle< float > trkiso_handle;
        eff::Handle< float > ecaliso_handle;
        eff::Handle< float > hcaliso_handle;
        eff::Handle< float > cordetiso04_handle;
        eff::Handle< float > detiso04_handle;
        eff::Handle< float > trkiso04_handle;
        eff::Handle< float > ecaliso04_handle;
        eff::Handle< float > hcaliso04_handle;
        eff::Handle< float > effarea_handle;
        eff::Handle< float > effarea04_handle;
        eff::Handle< float > dbeta_handle;
        eff::Handle< float > dbeta04_handle;
        eff::Handle< float > sf_lepeff_handle;
        eff::Handle< float > sf_trig_handle;
        eff::Handle< int > mcid_handle;
        eff::Handle< int > mc3id_handle;
        eff::Handle< int > momid_handle;
        eff::Handle< int > mc3_momid_handle;
        eff::Handle< bool > q3agree_handle;
        eff::Handle< bool > is_conv_handle;
        eff::Handle< int > qsc_handle;
        eff::Handle< int > qctf_handle;
        eff::Handle< int > qgsf_handle;
        eff::Handle< int > nmhits_handle;
        eff::Handle< int > eleid_veto_handle;
        eff::Handle< int > eleid_loose_handle;
        eff::Handle< int > eleid_medium_handle;
        eff::Handle< int > eleid_tight_handle;
        eff::Handle< bool > is_eleid_veto_handle;
        eff::Handle< bool > is_eleid_loose_handle;
        eff::Handle< bool > is_eleid_medium_handle;
        eff::Handle< bool > is_eleid_tight_handle;
        eff::Handle< float > dphiin_handle;
        eff::Handle< float > detain_handle;
        eff::Handle< float > sieie_handle;
        eff::Handle< float > hoe_handle;
        eff::Handle< float > ooemoop_handle;
        eff::Handle< float > conv_dist_handle;
        eff::Handle< float > conv_dcot_handle;
        eff::Handle< bool > is_global_handle;
        eff::Handle< bool > is_tracker_handle;
        eff::Handle< bool > is_stamu_handle;
        eff::Handle< bool > is_pfmu_handle;
        eff::Handle< bool > is_loosemu_handle;
        eff::Handle< bool > is_tightmu_handle;
        eff::Handle< int > npixelhits_handle;
        eff::Handle< int > nsihits_handle;
        eff::Handle< int > nsilayers_handle;
        eff::Handle< int > nstahits_handle;
        eff::Handle< int > nstations_handle;
        eff::Handle< float > chi2_handle;
        eff::Handle< float > ndof_handle;
        eff::Handle< float > pterr_handle;
        eff::Handle< float > ecal_vetodep_handle;
        eff::Handle< float > hcal_vetodep_handle;
        eff::Handle< LorentzVector > p4_handle;
        eff::Handle< LorentzVector > mcp4_handle;
        eff::Handle< LorentzVector > mc3p4_handle;
        eff::Handle< LorentzVector > mc_momp4_handle;
        eff::Handle< LorentzVector > gsf_p4_handle;
        eff::Handle< LorentzVector > ctf_p4_handle;
        eff::Handle< LorentzVector > sc_p4_handle;
        eff::Handle< LorentzVector > gfit_p4_handle;

};


// public interface 
// ------------------------------------------------------------------------------------------------- //

namespace eff
{

    const unsigned int& run();
    const unsigned int& ls();
    const unsigned int& evt();
    const bool& is_real_data();
    const int& sample();
    const int& nvtxs();
    const int& vtx_idx();
    const float& pfmet();
    const float& pfmet_phi();
    const float& uncorpfmet();
    const float& uncorpfmet_phi();
    const float& pu_nvtxs();
    const float& pu_ntrueint();
    const float& scale1fb();
    const float& xsec();
    const unsigned int& nevts();
    const float& kfactor();
    const float& gen_met();
    const float& gen_met_phi();
    const TString& dataset();
    const TString& filename();
    const int& gen_nleps();
    const int& gen_nels();
    const int& gen_nmus();
    const int& gen_ntaus();
    const int& gen_nleps_with_fromtau();
    const int& gen_nels_with_fromtau();
    const int& gen_nmus_with_fromtau();
    const int& gen_ntaus_with_fromtau();
    const bool& filt_csc();
    const bool& filt_hbhe();
    const bool& filt_hcallaser();
    const bool& filt_ecallaser();
    const bool& filt_ecaltp();
    const bool& filt_trkfail();
    const bool& filt_eebadsc();
    const bool& passes_metfilters();
    const bool& passes_id();
    const bool& passes_iso();
    const bool& is_num();
    const bool& is_den();
    const bool& is_fo();
    const bool& is_mu();
    const bool& is_el();
    const bool& exists();
    const int& is_fromw();
    const int& charge();
    const int& pdgid();
    const int& type();
    const float& d0();
    const float& d0err();
    const float& dz();
    const float& ip3d();
    const float& ip3derr();
    const float& dzerr();
    const float& mt();
    const float& corpfiso();
    const float& pfiso();
    const float& chiso();
    const float& emiso();
    const float& nhiso();
    const float& corpfiso04();
    const float& pfiso04();
    const float& chiso04();
    const float& emiso04();
    const float& nhiso04();
    const float& cordetiso();
    const float& detiso();
    const float& trkiso();
    const float& ecaliso();
    const float& hcaliso();
    const float& cordetiso04();
    const float& detiso04();
    const float& trkiso04();
    const float& ecaliso04();
    const float& hcaliso04();
    const float& effarea();
    const float& effarea04();
    const float& dbeta();
    const float& dbeta04();
    const float& sf_lepeff();
    const float& sf_trig();
    const int& mcid();
    const int& mc3id();
    const int& momid();
    const int& mc3_momid();
    const bool& q3agree();
    const bool& is_conv();
    const int& qsc();
    const int& qctf();
    const int& qgsf();
    const int& nmhits();
    const int& eleid_veto();
    const int& eleid_loose();
    const int& eleid_medium();
    const int& eleid_tight();
    const bool& is_eleid_veto();
    const bool& is_eleid_loose();
    const bool& is_eleid_medium();
    const bool& is_eleid_tight();
    const float& dphiin();
    const float& detain();
    const float& sieie();
    const float& hoe();
    const float& ooemoop();
    const float& conv_dist();
    const float& conv_dcot();
    const bool& is_global();
    const bool& is_tracker();
    const bool& is_stamu();
    const bool& is_pfmu();
    const bool& is_loosemu();
    const bool& is_tightmu();
    const int& npixelhits();
    const int& nsihits();
    const int& nsilayers();
    const int& nstahits();
    const int& nstations();
    const float& chi2();
    const float& ndof();
    const float& pterr();
    const float& ecal_vetodep();
    const float& hcal_vetodep();
    const LorentzVector& p4();
    const LorentzVector& mcp4();
    const LorentzVector& mc3p4();
    const LorentzVector& mc_momp4();
    const LorentzVector& gsf_p4();
    const LorentzVector& ctf_p4();
    const LorentzVector& sc_p4();
    const LorentzVector& gfit_p4();

} // namespace eff

#ifndef __CINT__
extern EFF eff_obj;
#endif


#endif // EFF_H
