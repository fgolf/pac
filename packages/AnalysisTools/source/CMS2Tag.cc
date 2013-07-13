#include "at/CMS2Tag.h"
#include "CMS2.h"
#include <string>
#include <vector>
#include "boost/lexical_cast.hpp"
#include "rt/MiscTools.h"

namespace at
{
    // method to return the cms2 tag from the cms2 ntuple
    CMS2Tag GetCMS2Tag()
    {
        using namespace std;
        using namespace tas;

        vector<string> cms2_tag = rt::string_split(evt_CMS2tag().front().Data(), "-");
        if (cms2_tag.size() < 3)
        {
            throw std::invalid_argument("[CMS2Tag] Error: cannot parse cms2 tag from ntuple");
        }

        // strip off V
        cms2_tag.at(0) = rt::string_remove_all(cms2_tag.at(0), "V");
        CMS2Tag result = 
        {
            boost::lexical_cast<int>(cms2_tag.at(0)), 
            boost::lexical_cast<int>(cms2_tag.at(1)), 
            boost::lexical_cast<int>(cms2_tag.at(2))
        };
        return result;
    }

} // namepsace at
