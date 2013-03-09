#ifndef AT_STATUS3EVENTIDENTFIER_H
#define AT_STATUS3EVENTIDENTFIER_H

#include <set>

class CMS2;

namespace at
{
    // this is a workaround for not having unique event id's in Status3 
    struct Status3EventIdentifier 
    {
        // construct:
        Status3EventIdentifier(class CMS2& cms2);

        // methods:
        bool operator < (const Status3EventIdentifier &) const;
        //bool operator == (const Status3EventIdentifier &) const;
        //bool operator > (const Status3EventIdentifier &) const;

        // members:
        unsigned long int run, event, lumi_section;
        std::multiset<float> pts;
    };

    // none member methods:
    extern std::set<Status3EventIdentifier> already_seen_stat3;
    bool is_duplicate(const Status3EventIdentifier &id);
    //bool operator == (const Status3EventIdentifier &, const Status3EventIdentifier &);

} // namespace at

#endif // AT_STATUS3EVENTIDENTFIER_H
