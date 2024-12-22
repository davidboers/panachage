#include "vote.hpp"
#include "partylist.cpp"

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
                plist->candidate_votes[id]++;
            }
        }

        inline bool validate()
        {
            return true;
        }

        inline FullListVote(partylist *plist) : plist(plist) {}
    };

}