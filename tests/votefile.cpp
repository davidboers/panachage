#include <vector>

#include "templates.hpp"

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
}