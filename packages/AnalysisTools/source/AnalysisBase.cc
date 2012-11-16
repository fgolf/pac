#include "at/AnalysisBase.h"
#include "rt/MiscTools.h"
#include <iostream>

using namespace std;

namespace at
{
    // construct:
    AnalysisBase::AnalysisBase(const std::string& root_file_name)
        : m_root_file(TFile::Open(rt::mkdir_from_filename(root_file_name).c_str(), "RECREATE"))
    {
        BeginJob();
    }

    // destroy:
    AnalysisBase::~AnalysisBase()
    {
        EndJob();
        m_root_file->Close();
    }

    // function operator 
    int AnalysisBase::operator () (long event)
    {
        return Analyze(event);
    }

    int AnalysisBase::operator () (long event, const std::string& filename)
    {
        return Analyze(event, filename);
    }

    // methods
    void AnalysisBase::BeginJob()
    {
    }

    int AnalysisBase::Analyze(long event)
    {
        return 0;
    }

    int AnalysisBase::Analyze(long event, const std::string& filename)
    {
        return 0;
    }

    void AnalysisBase::EndJob()
    {
    }

} // namespace at
