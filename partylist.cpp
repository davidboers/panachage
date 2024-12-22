#include <map>
#include <string>
#include <vector>

#include "candidate.hpp"

#pragma once

namespace panachage
{

    struct partylist
    {
        typedef unsigned int id_type;

        const id_type id;
        const std::string name;
        int at_large_votes;
        std::map<candidate::id_type, int> candidate_votes;
    };

    partylist new_partylist(const partylist::id_type id,
                            const std::string name,
                            const std::vector<candidate::id_type> candidates)
    {
        std::map<candidate::id_type, int> candidate_votes;
        for (candidate::id_type cand_id : candidates)
        {
            candidate_votes[cand_id] = 0;
        }
        return partylist{id, name, 0, candidate_votes};
    }

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