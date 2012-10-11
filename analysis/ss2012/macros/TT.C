void TT(int sample, int channel = 4, bool do_weight = true)
{
    
    TChain* e = new TChain("tree"); 
    switch (sample)
    {
        case 1: e->Add("babies_test/ttjets_52X_skim.root");   break;
        case 2: e->Add("babies_test/ttjets_52X_noskim.root"); break;
        case 3: e->Add("babies_test/ttjets_massive.root");    break;
        case 4: e->Add("babies_test/tt_powheg.root");         break;
    };

    float den = 0.0;
    switch (sample)
    {
        case 1: den = 6726135; break;
        case 2: den = 6726135; break;
        case 3: den = 6863750; break;
        case 4: den = 6215039; break;
    }

    TCut chan;
    switch (channel)
    {
        case 1: chan = "dilep_type==1"; break;
        case 2: chan = "dilep_type==2"; break;
        case 3: chan = "dilep_type==3"; break;
    }

    e->SetAlias("sr1"    , "nbtags>1 && (is_os||is_ss) && pfmet>30 && (lep1_is_fromw>0 && lep2_is_fromw>0)");
    e->SetAlias("weight" , "sf_nbtag");
    //e->SetAlias("weight", "sf_dileptrig");
    //e->SetAlias("weight", "sf_nbtag * sf_dileptrig");
    TCut sel = do_weight ? "sr1*weight" : "sr1";
    sel = sel && chan;

    e->Draw("1>>h_num", sel);
    float num = h_num->Integral();

    cout << "num = " << num << endl;
    cout << "den = " << den << endl;
    cout << "ratio = " << num/den << endl;
}
