{
    TChain e1("tree"); 
    e1.Add("babies/lpt/data.root");
    //e1.Add("/home/users/rwkelley/Data/hadoop/babies/ss2012/26Sep/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged_ntuple_999999_1.root");
    //e1.Add("/home/users/rwkelley/Data/hadoop/babies/ss2012/26Sep/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged_ntuple_999999_1.root");
    e1->SetScanField(0);
    e1->Scan("dataset:run:ls:evt", "is_ss && nbtags>1", "colsize=15 col=60:");
}
