#include <vector>
#include <iomanip>
#include <iostream>

#define JUST_PARTYLIST

#include "../parse_file.cpp"

using namespace panachage;

void test_pl_file(const char *path)
{
    partylist pl = parsePartyListFile(path);

    std::cout << "Successfully parsed " << std::string(path) << std::endl;
    std::cout << std::setw(5) << pl.name
              << std::setw(5) << pl.id
              << std::setw(10) << pl.at_large_votes
              << std::setw(5) << pl.candidate_votes.size()
              << std::endl
              << std::endl;
}

int main(void)
{
    test_pl_file("liechtenstein/vu.txt");
    test_pl_file("liechtenstein/fbp.txt");
    test_pl_file("liechtenstein/fl.txt");
    test_pl_file("liechtenstein/dpl.txt");
    test_pl_file("liechtenstein/du.txt");

    /*
    Successfully parsed liechtenstein/vu.txt
       vu    1      9404   14

    Successfully parsed liechtenstein/fbp.txt
      fbp    2     12480   12

    Successfully parsed liechtenstein/fl.txt
       fl    3      8250    8

    Successfully parsed liechtenstein/dpl.txt
      dpl    4      6143    8

    Successfully parsed liechtenstein/du.txt
       du    5      4793    3
    */
}