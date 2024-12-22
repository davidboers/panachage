#include <iostream>
#include <vector>

#include "../free_list.cpp"
#include "../full_list.cpp"
#include "../partial_list.cpp"
#include "../partylist.cpp"
#include "../display.cpp"

using namespace panachage;

int main(void)
{
    partylist listA = partylist(1, "Party A", {101, 102, 103, 104, 105, 106});
    partylist listB = partylist(2, "Party B", {201, 202, 203, 204, 205, 206});
    std::vector<partylist *> lists = {&listA, &listB};

    PartialListVote partial(&listA, {101, 103}, {104, 201});
    if (partial.validate())
    {
        std::cout << "Partial vote is valid." << std::endl;
        partial.count(lists);
        displayAllCandidates(lists);
    }
    else
    {
        std::cout << "Partial vote is not valid." << std::endl;
    }

    FullListVote full(&listB);
    if (full.validate())
    {
        std::cout << "Full vote is valid." << std::endl;
        full.count(lists);
        displayAllCandidates(lists);
    }
    else
    {
        std::cout << "Full vote is not valid." << std::endl;
    }

    FreeVote free({101, 102, 204});
    if (free.validate())
    {
        std::cout << "Free vote is valid." << std::endl;
        free.count(lists);
        displayAllCandidates(lists);
    }
    else
    {
        std::cout << "Free vote is not valid." << std::endl;
    }
}