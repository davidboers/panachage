#include "../partylist.cpp"
#include "../candidate.hpp"

namespace panachage
{
    partylist *makeTemp(const partylist::id_type plist_id, const std::string name, const int n_candidates, const int base = 100)
    {
        std::vector<candidate::id_type> cand_ids;
        for (int i = 0; i < n_candidates; i++)
        {
            cand_ids.push_back(plist_id * base + i);
        }
        return new partylist(plist_id, name, cand_ids);
    }
}

#define TEMP_LIST_A partylist(1, "Party A", {101, 102, 103, 104, 105, 106})
#define TEMP_LIST_B partylist(2, "Party B", {201, 202, 203, 204, 205, 206})

#define LIECHTENSTEIN_VU makeTemp(1, "VU", 14)
#define LIECHTENSTEIN_FBP makeTemp(2, "FBP", 12)
#define LIECHTENSTEIN_FL makeTemp(3, "FL", 8)
#define LIECHTENSTEIN_DPL makeTemp(4, "DPL", 8)
#define LIECHTENSTEIN_DU makeTemp(5, "DU", 3)