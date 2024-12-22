#include <iostream>
#include <vector>

#include "../free_list.cpp"
#include "../full_list.cpp"
#include "../partial_list.cpp"
#include "../partylist.cpp"
#include "../display.cpp"

using namespace panachage;

int main(void) {
    partylist listA = new_partylist(1, "Party A", {101, 102, 103, 104, 105, 106}); 
    partylist listB = new_partylist(2, "Party B", {201, 202, 203, 204, 205, 206}); 
    std::vector<partylist*> lists = {&listA, &listB};

    PartialListVote partial(&listA, {101, 103}, {104, 201});
    if (partial.validate()) {
        std::cout << "Partial vote is valid." << std::endl;
        partial.count(lists);
        displayAllCandidates(lists);
    } else {
        std::cout << "Partial vote is not valid." << std::endl;
    }
    
}