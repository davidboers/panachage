#include <map>
#include <string>
#include <vector>

#include "candidate.hpp"

namespace panachage
{

    typedef struct
    {
        typedef unsigned int id_type;

        const id_type id;
        const std::string name;
        int list_votes;
        std::map<candidate::id_type, int> candidate_votes;

    } partylist;

    std::vector<candidate::id_type> candidateList(partylist *plist)
    {
        std::vector<candidate::id_type> cs;
        for (auto pair : plist->candidate_votes)
        {
            cs.push_back(pair.first);
        }
        return cs;
    }

}