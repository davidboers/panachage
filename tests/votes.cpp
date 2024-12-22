#include <iostream>
#include <vector>

#include "templates.hpp"

#include "../free_list.cpp"
#include "../full_list.cpp"
#include "../partial_list.cpp"
#include "../partylist.cpp"
#include "../display.cpp"

using namespace panachage;

int main(void)
{
    partylist listA = TEMP_LIST_A;
    partylist listB = TEMP_LIST_B;
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