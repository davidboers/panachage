#include <map>
#include <string>
#include <bits/stdc++.h>
#include <vector>

#include "candidate.hpp"
#include "seat_alloc_utils.c"

#pragma once

namespace panachage
{
    class partylist
    {
    public:
        typedef unsigned int id_type;

        id_type id;
        std::string name;
        int at_large_votes;
        std::map<candidate::id_type, int> candidate_votes;

        inline partylist() {}

        partylist(const partylist::id_type id,
                  const std::string name,
                  const std::vector<candidate::id_type> candidates = {},
                  const int at_large_votes = 0)
            : id(id), name(name), at_large_votes(at_large_votes)
        {
            for (candidate::id_type cand_id : candidates)
            {
                this->candidate_votes[cand_id] = 0;
            }
        }

        void newCandidate(const candidate::id_type cand_id, const int votes = 0)
        {
            this->candidate_votes[cand_id] = votes;
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

        int totalVotes()
        {
            int tv = this->at_large_votes;
            for (auto p : this->candidate_votes)
            {
                tv += p.second;
            }
            return tv;
        }

        std::vector<candidate::id_type> elected(const int seats_won)
        {
            std::vector<std::pair<candidate::id_type, int>> temp_cands(this->candidate_votes.begin(), this->candidate_votes.end());
            std::sort(temp_cands.begin(), temp_cands.end(), [](std::pair<candidate::id_type, int> a, std::pair<candidate::id_type, int> b)
                      { return a.second > b.second; });
            std::vector<candidate::id_type> out;
            for (auto p : temp_cands)
            {
                if (out.size() == seats_won)
                    break;
                out.push_back(p.first);
            }
            return out;
        }

        inline party toCParty()
        {
            return party_new(this->id, this->totalVotes());
        }
    };
}

#ifndef party_id_type
#define party_id_type panachage::partylist::id_type
#endif