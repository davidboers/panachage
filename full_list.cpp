#include "vote.hpp"
#include "partylist.cpp"
#include "settings.h"

#pragma once

namespace panachage
{

    class FullListVote : public Vote
    {
        partylist *plist;

    public:
        void count(std::vector<partylist *> lists)
        {
            for (auto c : plist->candidate_votes)
            {
                candidate::id_type id = c.first;
                plist->candidate_votes[id] += this->copies;
            }

            plist->at_large_votes += (seats - plist->candidate_votes.size()) * this->copies;
        }

        inline bool validate()
        {
            return true;
        }

        inline FullListVote(partylist *plist) : plist(plist) {}
    };

}