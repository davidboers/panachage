#include <bits/stdc++.h>

#include "vote.hpp"
#include "partylist.cpp"
#include "candidate.hpp"
#include "settings.h"

namespace panachage
{
    class PartialListVote : public Vote
    {
        partylist *plist;
        std::vector<candidate::id_type> struckthrough;
        std::vector<candidate::id_type> added;

    public:
        void count(std::vector<partylist *> lists)
        {
            for (auto c : plist->candidate_votes)
            {
                candidate::id_type id = c.first;
                if (std::count(struckthrough.begin(), struckthrough.end(), id) == 0)
                {
                    plist->candidate_votes[id] += this->copies;
                }
            }

            for (candidate::id_type id : added)
            {
                for (partylist *listi : lists)
                {
                    std::vector<candidate::id_type> cs = listi->candidateList();
                    if (!!std::count(cs.begin(), cs.end(), id))
                    {
                        listi->candidate_votes[id] += this->copies;
                    }
                }
            }

            plist->at_large_votes += (struckthrough.size() - added.size()) * this->copies;
        }

        /*
         * * No candidate can be found in both `struckthrough` and `added`.
         * * No candidate can be voted for more than the specified number of times.
         * * No candidate can appear more than once in `struckthrough`.
         * * `added` cannot be longer than `struckthrough`.
         *
         */
        bool validate()
        {
            std::vector<candidate::id_type> res;
            std::set_intersection(struckthrough.begin(), struckthrough.end(), added.begin(), added.end(), std::back_inserter(res));
            if (res.size() > 0)
            {
                return false;
            }

            for (candidate::id_type id : added)
            {
                int substitutions = std::count(added.begin(), added.end(), id);
                std::vector<candidate::id_type> cs = plist->candidateList();
                int onlist = !!(std::count(cs.begin(), cs.end(), id));
                int votes_for = substitutions + onlist;
                if (votes_for > max_4_cand)
                {
                    return false;
                }
            }

            for (candidate::id_type id : struckthrough)
            {
                if (std::count(struckthrough.begin(), struckthrough.end(), id) > 1)
                {
                    return false;
                }
            }

            if (added.size() > struckthrough.size())
            {
                return false;
            }

            return true;
        }

        inline bool operator<(const Vote &vote) const
        {
            const PartialListVote *f = dynamic_cast<const PartialListVote *>(&vote);
            if (!f)
                return true;
            return this->plist->id < f->plist->id ||
                   this->struckthrough < f->struckthrough ||
                   this->added < f->added;
        }

        std::string encode() const
        {
            std::string c = copies == 1 ? "" : std::to_string(copies) + "*";
            std::string lid = std::to_string(plist->id);
            std::string s = std::accumulate(struckthrough.begin(), struckthrough.end(), std::string(),
                                            [](std::string a, candidate::id_type b)
                                            { return a + std::to_string(b) + ","; });
            std::string a = std::accumulate(added.begin(), added.end(), std::string(), [](std::string a, candidate::id_type b)
                                            { return a + std::to_string(b) + ","; });
            s.pop_back();
            a.pop_back();
            return c + "p|" + lid + "|" + s + "|" + a;
        }

        inline PartialListVote(partylist *plist,
                               std::vector<candidate::id_type> struckthrough,
                               std::vector<candidate::id_type> added = {})
            : plist(plist), struckthrough(struckthrough), added(added) {};

        PartialListVote(partylist *plist,
                        const candidate::id_type *struckthrough,
                        const candidate::id_type *added = nullptr)
            : plist(plist)
        {
            candidate::id_type h;
            while (*struckthrough)
            {
                h = *struckthrough++;
                this->struckthrough.push_back(h);
            }

            if (added == nullptr)
            {
                this->added;
            }
            else
            {
                while (*added)
                {
                    h = *added++;
                    this->added.push_back(h);
                }
            }
        };
    };

}