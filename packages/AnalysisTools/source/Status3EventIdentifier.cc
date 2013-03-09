#include "at/Status3EventIdentifier.h"

#include "CMS2.h" 
#include <iostream>

namespace at
{
    Status3EventIdentifier::Status3EventIdentifier(CMS2& cms2)
        : run(cms2.evt_run())
        , event(cms2.evt_event())
        , lumi_section(cms2.evt_lumiBlock())
    {
        for (unsigned int i = 0; i < std::min(size_t(4), cms2.genps_p4().size()); ++i)
        {
            pts.insert(cms2.genps_p4()[i].pt());
            // only go up to the W for this exercise
            if (i+1 < cms2.genps_p4().size() && abs(cms2.genps_id()[i+1]) == 24)
            {
                break;
            }
        }
    }

    bool Status3EventIdentifier::operator < (const Status3EventIdentifier &rhs) const
    {
        std::multiset<float>::const_iterator ipts = pts.begin();
        std::multiset<float>::const_iterator irhs = rhs.pts.begin();
        for (unsigned int i = 0; i < std::max(pts.size(), rhs.pts.size()); ++i, ++ipts, ++irhs) 
        {
            if (i >= pts.size())     {return true;}
            if (i >= rhs.pts.size()) {return false;}
            if (*ipts != *irhs)      {return *ipts < *irhs;}
        }
        return false;
    }

    std::set<Status3EventIdentifier> already_seen_stat3;
    bool is_duplicate(const Status3EventIdentifier &id)
    {
        std::pair<std::set<Status3EventIdentifier>::const_iterator, bool> ret = already_seen_stat3.insert(id);
        if (!ret.second) 
        {
            std::cout << std::setprecision(8);
            std::cout << "new entry (" << id.run << " " << id.lumi_section << " " << id.event << ") ";
            for (std::multiset<float>::const_iterator i = id.pts.begin();i != id.pts.end(); ++i) 
            {
                std::cout << *i << " ";
            }
            std::cout << std::endl;
            std::cout << "old entry (" << ret.first->run << " " << ret.first->lumi_section << " " << ret.first->event << ") ";
            for (std::multiset<float>::const_iterator i = ret.first->pts.begin(); i != ret.first->pts.end(); ++i)
            {
                std::cout << *i << " ";
            }
            std::cout << std::endl;
            return true;
        }
        return false;
    }

} // namespace at
