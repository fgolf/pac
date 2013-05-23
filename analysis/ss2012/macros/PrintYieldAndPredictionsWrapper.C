void PrintYieldAndPredictionsWrapper
(
    const std::string& output_path, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "exclusive",
    const std::string& output_file_name = ""
)
{
    if (output_file_name.empty())
    {
        cout << "no outpath given, quiting" << endl;
    }

    gROOT->ProcessLine(".L macros/PrintYields.C+");
    PrintYieldAndPredictions(output_path, analysis_type_name, signal_region_type_name, output_file_name);
}
