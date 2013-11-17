void processData(std::string output_file, int datatype, std::string input_file, int num_events, std::string run_list)
{
    // add local path to LD_LIBRARY_PATH 
    gSystem->AddDynamicPath(gSystem->Getenv("PWD"));
    gSystem->Exec("LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD");
    gSystem->Exec("PATH=$PATH:$PWD");
/*     cout << "gSystem->Getenv("LD_LIBRARY_PATH") << endl; */
/*     cout << "Dynamic path = " << gSystem->GetDynamicPath() << endl; */

    // construct command string
    std::string cmd = "./create_fake_rate_baby";
    cmd += Form(" --output %s.root" , output_file.c_str()); 
    cmd += Form(" --input %s"       , input_file.c_str() ); 
    cmd += Form(" --nev %d"         , num_events         ); 
    cmd += Form(" --eormu %d"       , datatype           ); 
    cmd += Form(" --filter %d"      , 0                  ); 
    cmd += Form(" --verbose %d"     , 0                  ); 
    cmd += Form(" --jetcorr %s"     , "data"             ); 
    if (!run_list.empty())
    {
        cmd += Form(" --run_list %s", run_list.c_str()); 
    }

    // run the command
    cout << "Running the following command:\n" << cmd << endl;
    gSystem->Exec(cmd.c_str());
}
