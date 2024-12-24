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

    /* | List: 1   ALV: 0        | List: 2   ALV: 0
       | 1   | 101   | 1     |   | 1   | 201   | 2     |
       | 2   | 102   | 2     |   | 2   | 202   | 1     |
       | 3   | 103   | 0     |   | 3   | 203   | 1     |
       | 4   | 104   | 2     |   | 4   | 204   | 2     |
       | 5   | 105   | 1     |   | 5   | 205   | 1     |
       | 6   | 106   | 1     |   | 6   | 206   | 1     |
       | Party total | 7     |   | Party total | 8     |
    */
}