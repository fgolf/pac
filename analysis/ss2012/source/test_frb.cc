#include "myBabyMaker.h"
#include "TChain.h"

int main()
{
        // create chain
    TChain chain("Events");
    chain.Add("/nfs-7/userdata/rwkelley/test_data/*.root");
    //chain.Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-18/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged/merged_ntuple_999999_1.root");
    //chain.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-13_slim/merged_ntuple_100.root");

    // run babymaker
    myBabyMaker babymaker;
    babymaker.SetNumEvents(-1);
    babymaker.SetVerbose(false);
    babymaker.SetGoodRunList("json/final_19p49fb_cms2.txt");
    //babymaker.SetGoodRunList("");
    //babymaker.ScanChain(&chain, "output/test_frb.root", /*eormu = */-1, /*apply fo filter =*/true, /*jet corr path = */"BatchSubmitFRB/job_input/data");
    babymaker.ScanChain(&chain, "output/test_frb.root", /*eormu = */-1, /*apply fo filter =*/true, /*jet corr path = */"../../externals/source/cms2_core/HEAD/CORE/jetcorr/data");
}
