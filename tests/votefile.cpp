#include <vector>

#include "templates.hpp"

#define JUST_VOTES

#include "../parse_file.cpp"
#include "../display.cpp"

using namespace panachage;

int main(void)
{
    partylist listA = TEMP_LIST_A;
    partylist listB = TEMP_LIST_B;
    std::vector<partylist *> lists = {&listA, &listB};
    std::vector<Vote *> votes;

    parseVoteFile("votes.txt", &votes, lists);
    int invalid = 0;
    for (auto it = votes.begin(); it != votes.end(); it++)
    {
        Vote *vote = *it;
        if (vote->validate())
            vote->count(lists);
        else
            invalid++;
    }
    displayAllCandidates(lists);
    std::cout << invalid << " invalid votes.";

    /* | List: 1   ALV: 0        | List: 2   ALV: 0
       | 1   | 101   | 1     |   | 1   | 201   | 2     |
       | 2   | 102   | 2     |   | 2   | 202   | 1     |
       | 3   | 103   | 0     |   | 3   | 203   | 1     |
       | 4   | 104   | 2     |   | 4   | 204   | 2     |
       | 5   | 105   | 1     |   | 5   | 205   | 1     |
       | 6   | 106   | 1     |   | 6   | 206   | 1     |
       | Party total | 7     |   | Party total | 8     |
       0 invalid votes.
    */
}