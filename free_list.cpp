#include <vector>
#include <bits/stdc++.h>

#include "vote.hpp"
#include "candidate.hpp"
#include "settings.h"

namespace panachage
{
    class FreeVote : public Vote
    {
        std::vector<candidate::id_type> votes;

    public:
        void count(std::vector<partylist *> lists)
        {
            for (candidate::id_type cand_id : votes)
            {
                for (partylist *plist : lists)
                {
                    std::vector<candidate::id_type> candidates = plist->candidateList();
                    if (!!std::count(candidates.begin(), candidates.end(), cand_id))
                    {
                        plist->candidate_votes[cand_id] += this->copies;
                    }
                }
            }
        }

        inline bool validate()
        {
            return votes.size() <= seats;
        }

        inline bool operator<(const Vote &vote) const
        {
            const FreeVote *f = dynamic_cast<const FreeVote *>(&vote);
            if (!f)
                return true;
            return this->votes < f->votes;
        }

        std::string encode() const
        {
            std::string c = copies == 1 ? "" : std::to_string(copies) + "*";
            std::string v = std::accumulate(votes.begin(), votes.end(), std::string(),
                                            [](std::string a, candidate::id_type b)
                                            { return a + std::to_string(b) + ","; });
            v.pop_back();
            return c + "b|" + v;
        }

        inline FreeVote(std::vector<candidate::id_type> votes) : votes(votes) {}

        FreeVote(candidate::id_type *votes)
        {
            while (*votes)
            {
                candidate::id_type h = *votes++;
                this->votes.push_back(h);
            }
        }
    };
}