{
    using namespace at;
    for (int i = 0; i != Sample::static_size; i++)
    {
        Sample::value_type sample = static_cast<Sample::value_type>(i);
        string sample_name = GetSampleInfo(sample).name;
        if (GetSampleInfo(sample).type == SampleType::data)
        {
            continue;
        }
        TChain chain("tree");
        chain.Add(Form("babies/hpt/%s.root", sample_name.c_str()));
        chain.Draw("scale1fb>>h1", "", "goff", 1);
        cout << Form("%s : %1.2f /fb", sample_name.c_str(), 1.0/h1->GetMean()) << endl;
    }
}
