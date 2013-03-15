#include <iostream>
#include <fstream>
#include "rt/RootTools.h" 
#include "TCanvas.h" 
#include "TFile.h" 
//#include "TF1.h" 
//#include "TMath.h" 
//#include "TROOT.h" 
#include "TROOT.h"
#include "TH1D.h"
#include "TTree.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooKeysPdf.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooSimultaneous.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooExtendPdf.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
#include "RooPlot.h"

#include "PerformFits.h"
#include "CTable.h"

using namespace std;
using namespace tp;

// needs to be automated somehowe
const float mlow  = 60.0;
const float mhigh = 120.0;
const size_t npt_bins  = 6; const float pt_bins [] = {10, 15, 20, 30, 40, 50, 200};
const size_t neta_bins = 5; const float eta_bins[] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};

// models for the ID
const tp::Model::value_type id_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    }, 
    {
        /*eta0, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      }, 
        /*eta2, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }
    },
    {
        /*eta0, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta2, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }
    },
    {
        /*eta0, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta1, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta2, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }, // not used, electron crack
        /*eta3, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta4, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }
    },
    {
        /*eta0, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta1, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta2, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }, // not used, electron crack
        /*eta3, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta4, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }
    }
};

// models for the Iso
const tp::Model::value_type iso_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    }, 
    {
        /*eta0, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      }, 
        /*eta2, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta4, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }
    },
    {
        /*eta0, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta2, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      }
    },
    {
        /*eta0, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta1, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta2, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }, // not used, electron crack
        /*eta3, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta4, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }
    },
    {
        /*eta0, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta1, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta2, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }, // not used, electron crack
        /*eta3, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta4, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }
    }
};

// models for the Iso+iso
const tp::Model::value_type both_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    }, 
    {
        /*eta0, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp      , Model::ErfExp    },
        /*eta1, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp      , Model::ErfExp    }, 
        /*eta2, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp      , Model::ErfExp    }, // not used, electron crack
        /*eta3, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp      , Model::ErfExp    },
        /*eta4, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp      , Model::ErfExp    }
    },
    {
        /*eta0, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta2, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta4, pt3 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }
    },
    {
        /*eta0, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta1, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta2, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }, // not used, electron crack
        /*eta3, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta4, pt4 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }
    },
    {
        /*eta0, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta1, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta2, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }, // not used, electron crack
        /*eta3, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  },
        /*eta4, pt5 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Chebychev  , Model::Chebychev  }
    }
};


//CTable FitMassPlots(const std::string& data_filename = "", const std::string& mc_filename = "", const string& output_path = "test", const std::string& measurement = "id", const std::string& suffix = "eps")
CTable FitMassPlots(const std::string& data_filename = "", const std::string& mc_filename = "", const string& output_path = "test", const tp::Model::value_type models[npt_bins][neta_bins][4] = id_models, const std::string& suffix = "eps")
{
    // histograms
    rt::TH1Container hc_data(data_filename); 
    rt::TH1Container hc_mc(mc_filename); 

    // make the output dir
    //rt::mkdir("plots/" + output_path + "/" + measurement, /*force=*/true);
    //rt::CopyIndexPhp("plots/" + output_path+ "/" + measurement);
    rt::mkdir("plots/" + output_path, /*force=*/true);
    rt::CopyIndexPhp("plots/" + output_path);
    
    CTable t;
    t.useTitle();
    t.setTitle("data/MC efficiency and scale factor");

    //size_t pt_bin = 1;
    //size_t eta_bin = 1;
    for (size_t pt_bin = 0; pt_bin != npt_bins; pt_bin++)
    //for (size_t pt_bin = 0; pt_bin != 1; pt_bin++)
    {
        const float pt_min = pt_bins[pt_bin];
        const float pt_max = pt_bins[pt_bin+1];
        const string pt_label = Form("%1.0f GeV < p_{T} < %1.0f GeV", pt_min, pt_max); 
        t.setColLabel(pt_label, pt_bin);

        for (size_t eta_bin = 0; eta_bin != neta_bins; eta_bin++)
        //for (size_t eta_bin = 0; eta_bin != 1; eta_bin++)
        {
            // set the models
            const tp::Model::value_type sig_pass_model = models[pt_bin][eta_bin][0];
            const tp::Model::value_type sig_fail_model = models[pt_bin][eta_bin][1];
            const tp::Model::value_type bkg_pass_model = models[pt_bin][eta_bin][2];
            const tp::Model::value_type bkg_fail_model = models[pt_bin][eta_bin][3];

            const float eta_min = eta_bins[eta_bin];
            const float eta_max = eta_bins[eta_bin+1];
            const string eta_label = Form("%1.2f < |\\eta| < %1.2f", eta_min, eta_max); 
            t.setRowLabel(eta_label, eta_bin);

            cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            cout << Form("fitting for bin: %s %s -- pt%lu_eta%lu", pt_label.c_str(), eta_label.c_str(), pt_bin, eta_bin) << endl;
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;

            const string hist_pass_name = Form("h_pass_pt%lu_eta%lu", pt_bin, eta_bin);
            const string hist_fail_name = Form("h_fail_pt%lu_eta%lu", pt_bin, eta_bin);
            
            TH1F* h_data_pass = dynamic_cast<TH1F*>(hc_data[hist_pass_name]);
            TH1F* h_data_fail = dynamic_cast<TH1F*>(hc_data[hist_fail_name]);
            TH1F* h_mc_pass   = dynamic_cast<TH1F*>(hc_mc  [hist_pass_name]);
            TH1F* h_mc_fail   = dynamic_cast<TH1F*>(hc_mc  [hist_fail_name]);

            if (eta_bin != 2) // skip crack
            {
                // do the fit
                tp::Result dr = tp::PerformSimultaneousFit(sig_pass_model, sig_fail_model, bkg_pass_model, bkg_fail_model, h_data_pass, h_data_fail, pt_label, eta_label, mlow, mhigh, h_mc_pass, h_mc_fail);
                dr.cpass->cd();
                dr.cpass->Draw();
                dr.cpass->Print(Form("plots/%s/p_data_pass_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));
                dr.cfail->cd();
                dr.cfail->Draw();
                dr.cfail->Print(Form("plots/%s/p_data_fail_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));

                // count the MC
                tp::Result mr = tp::PerformSimpleCount(h_mc_pass, h_mc_fail, pt_label, eta_label, mlow, mhigh);
                mr.cpass->cd();
                mr.cpass->Draw();
                mr.cpass->Print(Form("plots/%s/p_mc_pass_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));
                mr.cfail->cd();
                mr.cfail->Draw();
                mr.cpass->Print(Form("plots/%s/p_mc_fail_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));

                // scale factor
                float dr_err = std::max(dr.eff_err_high, dr.eff_err_low);
                float mr_err = std::max(mr.eff_err_high, mr.eff_err_low);
                float sf_val = dr.eff/mr.eff;
                float sf_err = sf_val * sqrt(pow(dr_err/dr.eff, 2) + pow(mr_err/mr.eff, 2));
                string sf    = rt::pm(sf_val, sf_err, "1.3");

                // set the table
                t.setCell(sf, eta_bin, pt_bin); 
            }
            else
            {
                cout << "skipping electron crack bin" << endl;
                t.setCell("NA", eta_bin, pt_bin); 
            }
        }
    }

    return t;
}

#ifndef __CINT__
int main()
try
{
    //const std::string input_path = "plots/Egamma_orig";
    //CTable t_id   = FitMassPlots(input_path +"/id/data/plots.root", input_path + "/id/mc/plots.root", "fits/test", id_models, "png");
    const std::string input_path = "plots/Egamma_orig";
    const std::string output_label = "fits/egamma_orig_v10"; 
    CTable t_id   = FitMassPlots(input_path +"/id/data/plots.root"  , input_path + "/id/mc/plots.root"  , output_label + "/id"  , id_models  , "eps");
    CTable t_iso  = FitMassPlots(input_path +"/iso/data/plots.root" , input_path + "/iso/mc/plots.root" , output_label + "/iso" , iso_models , "eps");
    CTable t_both = FitMassPlots(input_path +"/both/data/plots.root", input_path + "/both/mc/plots.root", output_label + "/both", both_models, "eps");

    t_id.setTitle("data/MC eff and SF for electron ID");
    t_iso.setTitle("data/MC eff and SF for electron Iso");
    t_both.setTitle("data/MC eff and SF for electron Iso+ID");
    
    rt::mkdir("tables/" + output_label + "/id"  , /*force=*/true); 
    rt::mkdir("tables/" + output_label + "/iso" , /*force=*/true); 
    rt::mkdir("tables/" + output_label + "/both", /*force=*/true); 
    t_id.saveAs  ("tables/" + output_label + "/id/sf.txt"  ); t_id.print();
    t_iso.saveAs ("tables/" + output_label + "/iso/sf.txt" ); t_iso.print();
    t_both.saveAs("tables/" + output_label + "/both/sf.txt"); t_both.print();

    return 0;
}
catch(std::exception& e)
{
    cout << e.what() << endl;
}
#endif

