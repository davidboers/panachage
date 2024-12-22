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

        void count(std::vector<partylist*> lists)
        {
            for (candidate::id_type cand_id : votes)
            {
                for (partylist* plist : lists)
                {
                    std::vector<candidate::id_type> candidates = candidateList(plist);
                    if (!!std::count(candidates.begin(), candidates.end(), cand_id))
                    {
                        plist->candidate_votes[cand_id]++;
                    }
                }
            }
        }

        bool validate()
        {
            return votes.size() <= seats;
        }
    };
}