// C++
#include <iostream>
#include <stdexcept>
#include <string>

// BOOST
#include <boost/program_options.hpp>

// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TDirectory.h"
#include "rt/MiscTools.h"

 using namespace std;

int TTreeDrawTest
(
    const std::string& input_file_name, 
    const std::string& tree_name,
    const std::string& draw_cmd,
    const int num_events = 10000000
)
{
    // check the input
    //-------------------------------------------------------------`
    std::cout << "Processing File " << input_file_name << std::endl;
    TFile input_file(input_file_name.c_str());
    if (input_file.IsZombie()) 
    {
        throw std::invalid_argument("[ttree_draw_test] File does not exist! exiting..."); 
    }

    TTree* tree = dynamic_cast<TTree*>(input_file.Get(tree_name.c_str()));
    if (!tree || tree->IsZombie()) 
    {
        throw std::invalid_argument("[ttree_draw_test] TTree \"Events\" does not exist! exiting..."); 
    }

    // draw it
    //-------------------------------------------------------------
        
    cout << "[ttree_draw_test] executing:" << endl;
    cout << Form("%s->Draw(\"%s\", \"\", \"\", %d, 0)", tree_name.c_str(), draw_cmd.c_str(), num_events) << endl; 

    tree->Draw(draw_cmd.c_str(), "", "", num_events);

    // wrap up
    //-------------------------------------------------------------

    input_file.Close();
    std::cout << "Tree draw is complete" << std::endl; 
    return 0;
}

int main(int argc, char* argv[])
try
{

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string input_file  = "";
    std::string tree_name   = "";
    std::string draw_cmd    = "";
    int num_events          = 10000000;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help" , "print this menu")
        ("input", po::value<std::string>(&input_file)->required(), "REQUIRED: input ntuple file" )
        ("tree" , po::value<std::string>(&tree_name)->required() , "REQUIRED: name of the tree"  )
        ("cmd"  , po::value<std::string>(&draw_cmd)->required()  , "REQUIRED: command to draw"   )
        ("nev"  , po::value<int>(&num_events)                    , "number of generated events"  )
        ;

    // parse it
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) 
        {
            cout << desc << "\n";
            return 1;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        cout << desc << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << "\n";
        return false;
    }


    cout << "inputs:" << endl;
    cout << "input_file :\t" << input_file << endl;
    cout << "tree_name  :\t" << tree_name  << endl;
    cout << "draw_cmd   :\t" << draw_cmd   << endl;

    // do it 
    // -------------------------------------------------------------------------------------------------//

    TTreeDrawTest(input_file, tree_name, draw_cmd, num_events); 
    return 0;
}
catch (std::exception& e)
{
    cerr << "ss2012_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

