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

        inline bool operator<(const Vote &vote) const
        {
            const FullListVote *f = dynamic_cast<const FullListVote *>(&vote);
            if (!f)
                return true;
            return this->plist->id < f->plist->id;
        }

        inline std::string encode() const
        {
            return (copies == 1 ? "" : std::to_string(copies) + "*") + "f|" + std::to_string(plist->id);
        }

        inline FullListVote(partylist *plist) : plist(plist) {}
    };

}