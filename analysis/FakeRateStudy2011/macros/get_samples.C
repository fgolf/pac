{
    gSystem->Load("$PAC/bin/release/libfake_rate_tools_int.so");
    using namespace fr;

    TChain* c_data  = GetSampleTChain(Sample::data); rt::PrintFilesFromTChain(c_data);
    TChain* c_qcd   = GetSampleTChain(Sample::qcd);  rt::PrintFilesFromTChain(c_qcd);
    TChain* c_ttbar = GetSampleTChain(Sample::ttbar);  rt::PrintFilesFromTChain(c_ttbar);

    // standard selections
    TCut is_mu   = "abs(id)==13";
    TCut fo_id   = "fo_mu_ssV5_noIso";
    TCut fo_iso  = "cpfiso03_db<0.4";
    TCut num_id  = "num_mu_ssV5_noIso";
    TCut num_iso = "cpfiso03_db<0.1";
    TCut kin     = "pt>20 && pt<55 && abs(eta)<2.4";
    //TCut kin     = "pt>20 && pt<35 && abs(eta)<2.4";
    TCut no_z    = "(mz_fo_ctf<76 || mz_fo_ctf>106) && (mupsilon_fo_mu<8 || mupsilon_fo_mu>12)";
    TCut no_w    = "pfmet<20 && pfmt<25";
    TCut no_fos  = "nFOmus==0";
    TCut j20     = "ptpfcL1Fj1res>20";
    TCut j40     = "ptpfcL1Fj1res>40";
    TCut j60     = "ptpfcL1Fj1res>60";

    TCut fo   = is_mu && fo_id && fo_iso && kin && no_z && no_w && no_fos; 
    TCut fo20 = fo && j20; 
    TCut fo40 = fo && j40; 
    TCut fo60 = fo && j60; 

    TCut num   = is_mu && num_id && num_iso && kin && no_z && no_w && no_fos; 
    TCut num20 = num && j20; 
    TCut num40 = num && j40; 
    TCut num60 = num && j60; 

    // trigger cut
    TCut trig = "((pt > 30 && (mu30_eta2p1_vstar > 1 || mu24_eta2p1_vstar > 1 || mu17_vstar>1 || mu8_vstar>1)) || "
    		    "(pt > 24 && (mu24_eta2p1_vstar > 1 || mu17_vstar>1 || mu8_vstar>1)) || " 
    		    "(pt > 17 && (mu17_vstar>1 || mu8_vstar>1)) || "
    		    "(pt > 8  && (mu8_vstar>1)))";

    // from mcSelections.h
    // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/JRibnik/CMS2/NtupleMacros/CORE/mcSelections.h?revision=1.9&view=markup
    // leptonFromW:  2 = from W/Z incorrect charge
    //               1 = from W/Z   correct charge
    //               0 = not matched to a lepton (= fake)
    //              -1 = lepton from b decay
    //              -2 = lepton from c decay
    //              -3 = lepton from some other source
    TCut not_from_w = "leptonIsFromW<1";

    // additional selections
	TCut btag      = fo && "btagpfcL1Fres";
	TCut btag_no_w = btag && not_from_w;
}
