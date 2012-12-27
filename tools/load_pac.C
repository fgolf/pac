{
    // ROOT Tools    gSystem->AddIncludePath("-D'__RTINT__'");
    gSystem->AddIncludePath("-I$PAC/packages/RootTools/include");
    gSystem->AddIncludePath("-I$PAC/packages/RootTools/source");
    //gSystem->Load("$BOOST_CURRENT/stage/lib/libboost_system.so");
    //gSystem->Load("$BOOST_CURRENT/stage/lib/libboost_filesystem.so");
    gSystem->Load("$PAC/lib/libRootTools.so");

    // Analysis Tools
    gSystem->AddIncludePath("-I$PAC/packages/AnalysisTools/include");
    gSystem->AddIncludePath("-I$PAC/packages/AnalysisTools/source");
    gSystem->Load("$PAC/lib/libAnalysisTools.so");

    // SS2012 Tools
    gSystem->AddIncludePath("-I$PAC/analysis/ss2012/include");
    gSystem->Load("$PAC/lib/libss2012_tools.so");

    // Ian's Simple table
    gSystem->AddIncludePath("-I$PAC/externals/source/SimpleTable");
    gSystem->Load("$PAC/lib/libSimpleTable.so");
}
