{
    std::string lib_path = gSystem->Getenv("LD_LIBRARY_PATH");
    std::string pac_path = gSystem->Getenv("PAC");
    pac_path += "/lib";

    if (lib_path.empty())
    {
        std::cout << "LD_LIBRARY_PATH is empty.  Exiting." << std::endl;
        return 1;
    }
    if (pac_path.empty())
    {
        std::cout << "PAC is empty.  Exiting." << std::endl;
        return 2;
    }

    if (lib_path.find(pac_path) == std::string::npos)
    {
        pac_path = gSystem->Getenv("PAC");
        pac_path += "/bin/release/";
    }
    
    gSystem->AddIncludePath("-D'__RTINT__'");
    gSystem->AddIncludePath("-I$PAC/packages/RootTools/include");
    gSystem->AddIncludePath("-I$PAC/packages/RootTools/source");
    gSystem->AddIncludePath("-I$BOOST_CURRENT/boost");
    gSystem->Load("$BOOST_CURRENT/stage/lib/libboost_system.so");
    gSystem->Load("$BOOST_CURRENT/stage/lib/libboost_filesystem.so");
    gSystem->Load(Form("%s/libRootTools.so", pac_path.c_str()));

    // Analysis Tools
    gSystem->AddIncludePath("-I$PAC/packages/AnalysisTools/include");
    gSystem->AddIncludePath("-I$PAC/packages/AnalysisTools/source");
    gSystem->Load(Form("%s/libAnalysisTools.so", pac_path.c_str()));

    // SS2012 Tools
    gSystem->AddIncludePath("-I$PAC/analysis/ss2012/include");
    gSystem->Load(Form("%s/libss2012_tools.so", pac_path.c_str()));
    gSystem->Load(Form("%s/libssb2012.so"     , pac_path.c_str()));

    // Ian's Simple table
    gSystem->AddIncludePath("-I$PAC/externals/source/SimpleTable");
    gSystem->Load(Form("%s/libSimpleTable.so", pac_path.c_str()));

    // load mini FW lite
    gSystem->Load(Form("%s/libMiniFWLite.so", pac_path.c_str()));
}
