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
                    plist->candidate_votes[id]++;
                }
            }

            for (candidate::id_type id : added)
            {
                for (partylist *listi : lists)
                {
                    std::vector<candidate::id_type> cs = listi->candidateList();
                    if (!!std::count(cs.begin(), cs.end(), id))
                    {
                        listi->candidate_votes[id]++;
                    }
                }
            }

            plist->at_large_votes += struckthrough.size() - added.size();
        }

        /*
         * * No candidate can be found in both `struckthrough` and `added`.
         * * No candidate can appear in `added` more than the specified number of times.
         * * No candidate can appear more than once in `struckthrough`.
         * * Added cannot be longer than `struckthrough`.
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

        inline PartialListVote(partylist *plist,
                               std::vector<candidate::id_type> struckthrough,
                               std::vector<candidate::id_type> added = {})
            : plist(plist), struckthrough(struckthrough), added(added) {};

        PartialListVote(partylist *plist,
                        candidate::id_type *struckthrough,
                        candidate::id_type *added = {})
            : plist(plist)
        {
            while (*struckthrough)
            {
                candidate::id_type h = *struckthrough++;
                this->struckthrough.push_back(h);
            }

            while (*added)
            {
                candidate::id_type h = *added++;
                this->added.push_back(h);
            }
        };
    };

}