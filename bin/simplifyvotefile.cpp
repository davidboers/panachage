#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <bits/stdc++.h>

#define JUST_VOTES
#include "../parse_file.cpp"

using namespace panachage;

#ifdef TEST
void create_test_in()
{
    std::ofstream out("temp.txt");
    out << "f|1" << std::endl
        << "f|1" << std::endl
        << "p|2|11,12,13|4,5" << std::endl
        << "p|2|11,12,13|4,6" << std::endl
        << "2*b|1,2,3,4,5" << std::endl
        << "b|1,2,3,4,5" << std::endl
        << "b|1,2,3,4,5" << std::endl;
    out.close();
}

int check_out()
{
    std::ifstream in("temp.txt");
    std::vector<std::string> content;
    std::string line;
    while (std::getline(in, line))
    {
        content.push_back(line);
    }
    in.close();
    const std::vector<std::string> correct_content = {
        "4*b|1,2,3,4,5",
        "p|2|11,12,13|4,5",
        "p|2|11,12,13|4,6",
        "2*f|1"};
    if (content == correct_content)
    {
        std::cout << "Test passed!" << std::endl;
    }
    else
    {
        std::cout << "Test failed with output:" << std::endl;
        for (std::string i : content)
        {
            std::cout << i << std::endl;
        }
    }
    std::remove("temp.txt");
    return content == correct_content ? 0 : 1;
}
#endif

int main(int argc, char **argv)
{
#ifdef TEST
    std::cout << "Running in test mode!" << std::endl;
    create_test_in();
    const char *file = "temp.txt";
#else
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <votes_file>" << std::endl;
        return 1;
    }
    const char *file = argv[1];
#endif

    std::vector<Vote *> votes;
    std::vector<partylist *> lists = {
        new partylist(1, "List 1", {1, 2, 3, 4, 5, 6}),
        new partylist(2, "List 2", {11, 12, 13, 14, 15, 16})};
    parseVoteFile(file, &votes, lists, true);

    std::set<Vote *, Vote::PtrComparator> uniqueVotes;
    for (Vote *i : votes)
    {
        auto p = uniqueVotes.insert(i);
        if (!p.second)
        {
            Vote *j = *p.first;
            j->setCopies(j->getCopies() + i->getCopies());
        }
    }

    if (uniqueVotes.size() == votes.size())
    {
        std::cout << "No duplicates found. " << votes.size() << " total lines." << std::endl;
#ifdef TEST
        std::remove("temp.txt");
#endif
        return 0;
    }
    else
    {
        std::cout << "Reducing " << votes.size() << " lines to " << uniqueVotes.size() << " lines." << std::endl;
    }

    std::ofstream out(file);
    for (Vote *i : uniqueVotes)
    {
        out << i->encode() << std::endl;
    }
    out.close();

#ifdef TEST
    return check_out();
#else
    return 0;
#endif
}