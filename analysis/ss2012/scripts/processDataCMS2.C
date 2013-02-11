// datatype and realdata not used
void processData(std::string fileid, int datatype, std::string filename, int realdata, std::string runlist)
{
    std::cout << "arguments:" << std::endl;
    std::cout << "fileid  : " << fileid   << std::endl;
    std::cout << "datatype: " << datatype << std::endl;
    std::cout << "filename: " << filename << std::endl;
    std::cout << "realdata: " << realdata << std::endl;  // not using this here as a good runlist
    std::cout << "runlist : " << runlist  << std::endl;
	
    const char* fake_rate_file = "ssFR_data_standard_26Nov2012.root";
    //const char* fake_rate_file = "ssFR_data_standard_24Sep2012.root";
    const char* flip_rate_file = "fliprate42X.root";

    // command
    std::string command = "./ss2012_analysis ";
    command.append(Form(" --input %s"       , filename.c_str())); 
    command.append(Form(" --output %s.root" , fileid.c_str()  )); 
    command.append(Form(" --fr %s"          , fake_rate_file  )); 
    command.append(Form(" --fl %s"          , flip_rate_file  )); 
    command.append(" --njets 2 "); 
    //command.append(" --nev 1000 "); 

    //if (!runlist.empty())
    //{
    //	command.append(Form(" --run_list %s", runlist.c_str()));
    //}
    if (!runlist.empty())
    {
        command.append(Form(" --sample %s", runlist.c_str()));
    }
    switch(datatype)
    {
    case 1: command.append(" --isFastSim 1"); break;
    case 2: command.append(" --anal_type low_pt"); break;
    case 3: command.append(" --anal_type low_pt --isFastSim 1"); break;
    case 5: command.append(" --anal_type high_pt_eth"); break;
    default: break;
    };
    switch(realdata)
    {
    case 1: 
        command.append(" --sparms 1"); 
        break;
    default: break;
    }
    cout << command << endl;

    // execute
    gSystem->AddDynamicPath(gSystem->Getenv("$PWD"));
    gSystem->Exec(command.c_str());
}
