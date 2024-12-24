#include <vector>

#define JUST_PARTYLIST

#include "../parse_file.cpp"

using namespace panachage;

int main(void)
{
    std::vector<partylist *> lists = {parsePartyListFile("liechtenstein/vu.txt"),
                                      parsePartyListFile("liechtenstein/fbp.txt"),
                                      parsePartyListFile("liechtenstein/fl.txt"),
                                      parsePartyListFile("liechtenstein/dpl.txt"),
                                      parsePartyListFile("liechtenstein/du.txt")};
}