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

// Electrons
// --------------------------------------------------------------------------------- //

// models for the ID
const tp::Model::value_type el_id_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    }, 
    {
        /*eta0, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta1, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      }, 
        /*eta2, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
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
const tp::Model::value_type el_iso_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}
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
const tp::Model::value_type el_both_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }
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

// Muons
// --------------------------------------------------------------------------------- //

// models for the ID
const tp::Model::value_type mu_id_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    }, 
    {
        /*eta0, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      },
        /*eta1, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Poly3      , Model::Poly3      }, 
        /*eta2, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt2 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
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
const tp::Model::value_type mu_iso_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta1, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential}
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
const tp::Model::value_type mu_both_models[npt_bins][neta_bins][4] =
{
    {                  //           sig pass,             sig fail,           bkg pass,            bkg fail,
        /*eta0, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta1, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta2, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}, // not used, electron crack
        /*eta3, pt0 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::Exponential, Model::Exponential},
        /*eta4, pt0 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential}
    },
    {
        /*eta0, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     },
        /*eta1, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::Exponential, Model::Exponential},
        /*eta2, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }, // not used, electron crack
        /*eta3, pt1 =*/{Model::BreitWignerCB, Model::BreitWignerCB, Model::ErfExp     , Model::ErfExp     },
        /*eta4, pt1 =*/{Model::MCTemplate   , Model::MCTemplate   , Model::ErfExp     , Model::ErfExp     }
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

void PrintCanvas(TCanvas* const canvas, const std::string& filename, const std::string& suffix = "png")
{
    const std::string dirname  = rt::dirname(filename);
    const std::string basename = rt::basename(filename);
    if (suffix == "all")
    {
        rt::mkdir(dirname + "/png", /*force=*/true);
        rt::mkdir(dirname + "/eps", /*force=*/true);
        rt::mkdir(dirname + "/pdf", /*force=*/true);
        canvas->Print(Form("%s/png/%s.eps", dirname.c_str(), basename.c_str()));
        canvas->Print(Form("%s/eps/%s.png", dirname.c_str(), basename.c_str()));
        canvas->Print(Form("%s/pdf/%s.pdf", dirname.c_str(), basename.c_str()));
    }
    else
    {
        rt::mkdir(dirname + "/" + suffix, /*force=*/true);
        canvas->Print(Form("%s/%s/%s.%s", dirname.c_str(), suffix.c_str(), filename.c_str(), suffix.c_str()));
    }
}

// returns the num/den hists
rt::TH1Container FitMassPlots(const std::string& data_filename = "", const std::string& mc_filename = "", const string& output_path = "test", const tp::Model::value_type models[npt_bins][neta_bins][4] = el_id_models, const std::string& suffix = "eps")
{
    // histograms
    rt::TH1Container hc_data(data_filename); 
    rt::TH1Container hc_mc(mc_filename); 

    // make the output dir
    rt::mkdir("plots/" + output_path + "/id/png"  , /*force=*/true);
    rt::mkdir("plots/" + output_path + "/iso/png" , /*force=*/true);
    rt::mkdir("plots/" + output_path + "/both/png", /*force=*/true);
    rt::CopyIndexPhp("plots/" + output_path);

    // hist for num counts
    rt::TH1Container hc;
    hc.Add(new TH2F("h_data_num", "Numerator Counts;|#eta|;p_{T} (GeV)", neta_bins, eta_bins, npt_bins, pt_bins));
    hc.Add(new TH2F("h_mc_num"  , "Numerator Counts;|#eta|;p_{T} (GeV)", neta_bins, eta_bins, npt_bins, pt_bins));

    // hist for den counts
    hc.Add(new TH2F("h_data_den", "Denominator Counts;|#eta|;p_{T} (GeV)", neta_bins, eta_bins, npt_bins, pt_bins));
    hc.Add(new TH2F("h_mc_den"  , "Denominator Counts;|#eta|;p_{T} (GeV)", neta_bins, eta_bins, npt_bins, pt_bins));

    // hist for eff
    hc.Add(new TH2F("h_data_eff", "Efficiency;|#eta|;p_{T} (GeV)", neta_bins, eta_bins, npt_bins, pt_bins));
    hc.Add(new TH2F("h_mc_eff"  , "Efficiency;|#eta|;p_{T} (GeV)", neta_bins, eta_bins, npt_bins, pt_bins));

/*     size_t pt_bin = 0; */
/*     size_t eta_bin = 1; */
    for (size_t pt_bin = 0; pt_bin != npt_bins; pt_bin++)
    //for (size_t pt_bin = 0; pt_bin != 2; pt_bin++)
    {
        const float pt_min = pt_bins[pt_bin];
        const float pt_max = pt_bins[pt_bin+1];
        const string pt_label = Form("%1.0f GeV < p_{T} < %1.0f GeV", pt_min, pt_max); 

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
                //tp::Result dr = tp::PerformSimpleCount(h_data_pass, h_data_fail, pt_label, eta_label, mlow, mhigh);
                dr.cpass->cd();
                dr.cpass->Draw();
                PrintCanvas(dr.cpass, Form("plots/%s/p_data_pass_pt%lu_eta%lu", output_path.c_str(), pt_bin, eta_bin), "all");
                dr.cfail->cd();
                dr.cfail->Draw();
                PrintCanvas(dr.cfail, Form("plots/%s/p_data_fail_pt%lu_eta%lu", output_path.c_str(), pt_bin, eta_bin), "all");

                // count the MC
                tp::Result mr = tp::PerformSimpleCount(h_mc_pass, h_mc_fail, pt_label, eta_label, mlow, mhigh);
                mr.cpass->cd();
                mr.cpass->Draw();
                PrintCanvas(mr.cpass, Form("plots/%s/p_mc_pass_pt%lu_eta%lu", output_path.c_str(), pt_bin, eta_bin), "all");
                mr.cfail->cd();
                mr.cfail->Draw();
                PrintCanvas(mr.cfail, Form("plots/%s/p_mc_fail_pt%lu_eta%lu", output_path.c_str(), pt_bin, eta_bin), "all");

                // ROOT counts bins from 1-N not 0-(N-1) like C++ 
                hc["h_data_num"]->SetBinContent(eta_bin+1, pt_bin+1, dr.num.value);
                hc["h_data_num"]->SetBinError  (eta_bin+1, pt_bin+1, dr.num.error);
                hc["h_data_den"]->SetBinContent(eta_bin+1, pt_bin+1, dr.den.value);
                hc["h_data_den"]->SetBinError  (eta_bin+1, pt_bin+1, dr.den.error);
                hc["h_data_eff"]->SetBinContent(eta_bin+1, pt_bin+1, dr.eff.value);
                hc["h_data_eff"]->SetBinError  (eta_bin+1, pt_bin+1, dr.eff.error);
                hc["h_mc_num"  ]->SetBinContent(eta_bin+1, pt_bin+1, mr.num.value);
                hc["h_mc_num"  ]->SetBinError  (eta_bin+1, pt_bin+1, mr.num.error);
                hc["h_mc_den"  ]->SetBinContent(eta_bin+1, pt_bin+1, mr.den.value);
                hc["h_mc_den"  ]->SetBinError  (eta_bin+1, pt_bin+1, mr.den.error);
                hc["h_mc_eff"  ]->SetBinContent(eta_bin+1, pt_bin+1, mr.eff.value);
                hc["h_mc_eff"  ]->SetBinError  (eta_bin+1, pt_bin+1, mr.eff.error);
            }
            else
            {
                // ROOT counts bins from 1-N not 0-(N-1) like C++
                cout << "skipping electron crack bin" << endl;
                hc["h_data_num"]->SetBinContent(eta_bin+1, pt_bin+1, 0);
                hc["h_data_num"]->SetBinError  (eta_bin+1, pt_bin+1, 0);
                hc["h_data_den"]->SetBinContent(eta_bin+1, pt_bin+1, 0);
                hc["h_data_den"]->SetBinError  (eta_bin+1, pt_bin+1, 0);
                hc["h_data_eff"]->SetBinContent(eta_bin+1, pt_bin+1, 0);
                hc["h_data_eff"]->SetBinError  (eta_bin+1, pt_bin+1, 0);
                hc["h_mc_num"  ]->SetBinContent(eta_bin+1, pt_bin+1, 0);
                hc["h_mc_num"  ]->SetBinError  (eta_bin+1, pt_bin+1, 0);
                hc["h_mc_den"  ]->SetBinContent(eta_bin+1, pt_bin+1, 0);
                hc["h_mc_den"  ]->SetBinError  (eta_bin+1, pt_bin+1, 0);
                hc["h_mc_eff"  ]->SetBinContent(eta_bin+1, pt_bin+1, 0);
                hc["h_mc_eff"  ]->SetBinError  (eta_bin+1, pt_bin+1, 0);
            }
        }
    }

    // make eff projection plots
    for (size_t pt_bin = 0; pt_bin != npt_bins; pt_bin++)
    {
        const float pt_min = pt_bins[pt_bin];
        const float pt_max = pt_bins[pt_bin+1];
        const string title = Form("Efficiency (%1.0f GeV < p_{T} < %1.0f GeV);|#eta|;#varepsilon", pt_min, pt_max);
        TH1D* h_data_proj = dynamic_cast<TH2*>(hc["h_data_eff"])->ProjectionX(Form("h_data_eff_vs_eta_pt%lu", pt_bin), pt_bin+1, pt_bin+1);
        TH1D* h_mc_proj   = dynamic_cast<TH2*>(hc["h_mc_eff"  ])->ProjectionX(Form("h_mc_eff_vs_eta_pt%lu"  , pt_bin), pt_bin+1, pt_bin+1);
        h_data_proj->SetTitle(("Data " + title).c_str());
        h_mc_proj->SetTitle(("MC " + title).c_str());
        hc.Add(h_data_proj);
        hc.Add(h_mc_proj);

        const string sf_title = Form("Data/MC scalefactor (%1.0f GeV < p_{T} < %1.0f GeV);|#eta|;#varepsilon", pt_min, pt_max);
        hc.Add(rt::DivideHists(h_data_proj, h_mc_proj, Form("h_sf_vs_eta_pt%lu", pt_bin), sf_title));
    }
    for (size_t eta_bin = 0; eta_bin != neta_bins; eta_bin++)
    {
        const float eta_min = eta_bins[eta_bin];
        const float eta_max = eta_bins[eta_bin+1];
        const string title  = Form("Efficiency (%1.2f < |\\eta| < %1.2f);p_{T} (GeV);#varepsilon", eta_min, eta_max);
        TH1D* h_data_proj = dynamic_cast<TH2*>(hc["h_data_eff"])->ProjectionY(Form("h_data_eff_vs_pt_eta%lu", eta_bin), eta_bin+1, eta_bin+1);
        TH1D* h_mc_proj   = dynamic_cast<TH2*>(hc["h_mc_eff"  ])->ProjectionY(Form("h_mc_eff_vs_pt_eta%lu" , eta_bin), eta_bin+1, eta_bin+1);
        h_data_proj->SetTitle(("Data " + title).c_str());
        h_mc_proj->SetTitle(("MC " + title).c_str());
        hc.Add(h_data_proj);
        hc.Add(h_mc_proj);

        const string sf_title = Form("Data/MC scalefactor (%1.2f < |\\eta| < %1.2f);p_{T} (GeV);#varepsilon", eta_min, eta_max);
        hc.Add(rt::DivideHists(h_data_proj, h_mc_proj, Form("h_sf_vs_pt_eta%lu", eta_bin), sf_title));
    }

    // make scale factor plots
    hc.Add(rt::DivideHists(hc["h_data_eff"], hc["h_mc_eff"], "h_sf", "data/MC scale Factor"));

    return hc;
}


#ifndef __CINT__
int main()
try
{
/*     const std::string input_path  = "plots/Egamma_orig"; */
/*     const std::string output_label = "fits/test";  */
/*     rt::TH1Container hc_id = FitMassPlots(input_path + "/id/data/plots.root", input_path + "/id/mc/plots.root"  , output_label + "/id", id_models  , "png"); */
/*     hc_id.Write("plots/fits/test/id_results.root"); */
/*     CTable t_id = rt::CreateTableFromHist(hc_id["h_sf"], "Data/MC ScaleFactor ID", "p_{T}", "\\eta", "GeV", "", "1.3", "1.0", "1.2", true); */
/*     t_id.print(); */

    // do the fits
    //const std::string input_path = "plots/Egamma_orig";
    //const std::string output_label = "fits/egamma_orig_v10";
    const std::string input_path = "plots/SameSign_orig";
    const std::string output_label = "fits/SameSign_orig_v2";
/*     const std::string input_path = "plots/SameSignMu_orig"; */
/*     const std::string output_label = "fits/SameSignMu_v1"; */

    rt::TH1Container hc_id   = FitMassPlots(input_path +"/id/data/plots.root"  , input_path + "/id/mc/plots.root"  , output_label + "/id"  , el_id_models  , "all");
    rt::TH1Container hc_iso  = FitMassPlots(input_path +"/iso/data/plots.root" , input_path + "/iso/mc/plots.root" , output_label + "/iso" , el_iso_models , "all");
    rt::TH1Container hc_both = FitMassPlots(input_path +"/both/data/plots.root", input_path + "/both/mc/plots.root", output_label + "/both", el_both_models, "all");

    TH1* h_sf_prod = rt::MultiplyHists(hc_id["h_sf"], hc_iso["h_sf"], "h_sf_prod", "data/MC scale Factor (ID*Iso)");

    // make the tables
    CTable t_id   = rt::CreateTableFromHist(hc_id  ["h_sf"], "Data/MC ScaleFactor ID"    , "\\eta", "p_{T}", "GeV", "", "1.3", "1.0", "1.2", true);
    CTable t_iso  = rt::CreateTableFromHist(hc_iso ["h_sf"], "Data/MC ScaleFactor ISO"   , "\\eta", "p_{T}", "GeV", "", "1.3", "1.0", "1.2", true);
    CTable t_prod = rt::CreateTableFromHist(h_sf_prod      , "Data/MC ScaleFactor ID*ISO", "\\eta", "p_{T}", "GeV", "", "1.3", "1.0", "1.2", true);
    CTable t_both = rt::CreateTableFromHist(hc_both["h_sf"], "Data/MC ScaleFactor ID+ISO", "\\eta", "p_{T}", "GeV", "", "1.3", "1.0", "1.2", true);

    // print to screen
    t_id.print();
    t_iso.print();
    t_prod.print();
    t_both.print();

    //hc_id.SetMinMax(0, 1.1);
    //hc_iso.SetMinMax(0, 1.1);
    //hc_both.SetMinMax(0, 1.1);

    hc_id.Write  (Form("plots/%s/id/results.root"  , output_label.c_str()));
    hc_iso.Write (Form("plots/%s/iso/results.root" , output_label.c_str()));
    hc_both.Write(Form("plots/%s/both/results.root", output_label.c_str()));

    rt::mkdir("tables/" + output_label + "/id"  , /*force=*/true);
    rt::mkdir("tables/" + output_label + "/iso" , /*force=*/true);
    rt::mkdir("tables/" + output_label + "/prod", /*force=*/true);
    rt::mkdir("tables/" + output_label + "/both", /*force=*/true);
    t_id.saveAs   ("tables/" + output_label + "/id/sf.txt"  ); t_id.print();
    t_iso.saveAs  ("tables/" + output_label + "/iso/sf.txt" ); t_iso.print();
    t_prod.saveAs ("tables/" + output_label + "/prod/sf.txt" ); t_iso.print();
    t_both.saveAs ("tables/" + output_label + "/both/sf.txt"); t_both.print();
    t_id.print();
    t_iso.print();
    t_prod.print();
    t_both.print();

    return 0;
}
catch(std::exception& e)
{
    cout << e.what() << endl;
}
#endif

