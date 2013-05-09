{
    std::string lib_path = gSystem->Getenv("LD_LIBRARY_PATH");
    std::string pac_path = gSystem->Getenv("PAC");
    pac_path += "/lib";

    // cmsssw
    const bool cmssw = (TString(gSystem->Getenv("CMSSW_BASE")).Length() > 0);

    // set debug if debug ROOT build
    TString rootsys = gSystem->Getenv("ROOTSYS");
    if (rootsys.Contains("debug"))
    {
        gSystem->SetAclicMode(TSystem::kDebug);
    }
    const bool is_debug = (gSystem->GetAclicMode()==TSystem::kDebug);

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

    //if (lib_path.find(pac_path.c_str()) == std::string::npos)
    std::string pac_path = gSystem->Getenv("PAC");
    std::string cms2core = gSystem->Getenv("CMS2CORE");
    if (cmssw)
    {
        pac_path += (is_debug ? "/bin/cmssw/debug" : "/bin/cmssw/release");
    }
    else
    {
        pac_path += (is_debug ? "/bin/debug" : "/bin/release");
    }
    if (is_debug)
    {
        cout << "PAC path set to: " << pac_path << endl;
    }

    // CMS2 header
    gSystem->AddIncludePath("-I$PAC/packages/cms2/05.03.23/header");
    gSystem->Load(Form("%s/libcms2_header.so", pac_path.c_str()));

    // CMS2 CORE
    gSystem->AddIncludePath(Form("-I%s/externals/source/cms2_core/%s/CORE", pac_path.c_str(), cms2core.c_str()));
    gSystem->Load(Form("%s/libcms2_core.so", pac_path.c_str()));

    // Ian's Simple table
    gSystem->AddIncludePath("-I$PAC/externals/source/SimpleTable");
    gSystem->Load(Form("%s/libSimpleTable.so", pac_path.c_str()));

    // RootTools
    gSystem->AddIncludePath("-D'__RTINT__'");
    gSystem->AddIncludePath("-I$PAC/packages/RootTools/include");
    gSystem->AddIncludePath("-I$PAC/packages/RootTools/source");
    gSystem->AddIncludePath("-I$BOOST_CURRENT/boost");
    gSystem->Load(Form("%s/libboost_system.so"    , pac_path.c_str()));
    gSystem->Load(Form("%s/libboost_filesystem.so", pac_path.c_str()));
    gSystem->Load(Form("%s/libRootTools.so"       , pac_path.c_str()));

    // AnalysisTools
    gSystem->AddIncludePath("-I$PAC/packages/AnalysisTools/include");
    gSystem->AddIncludePath("-I$PAC/packages/AnalysisTools/source");
    gSystem->Load(Form("%s/libAnalysisTools.so", pac_path.c_str()));

    // SS2012 Tools
    gSystem->AddIncludePath("-I$PAC/analysis/ss2012/include");
    gSystem->Load(Form("%s/libssb2012.so"     , pac_path.c_str()));
    gSystem->Load(Form("%s/libss2012_tools.so", pac_path.c_str()));

    // load mini FW lite
    if (!cmssw)
    {
        gSystem->Load(Form("%s/libMiniFWLite.so", pac_path.c_str()));
    }
}
