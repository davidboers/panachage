#include <map>
#include <string>
#include <vector>

#include "candidate.hpp"

#pragma once

namespace panachage
{

    class partylist
    {
    public:
        typedef unsigned int id_type;

        const id_type id;
        const std::string name;
        int at_large_votes;
        std::map<candidate::id_type, int> candidate_votes;

        partylist(const partylist::id_type id,
                  const std::string name,
                  const std::vector<candidate::id_type> candidates)
            : id(id), name(name), at_large_votes(0)
        {
            for (candidate::id_type cand_id : candidates)
            {
                this->candidate_votes[cand_id] = 0;
            }
        }

        std::vector<candidate::id_type> candidateList()
        {
            std::vector<candidate::id_type> cs;
            for (auto pair : this->candidate_votes)
            {
                cs.push_back(pair.first);
            }
            return cs;
        }
    };

}