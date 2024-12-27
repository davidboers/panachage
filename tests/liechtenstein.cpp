/*
Full Liechtenstein test.
Oberland Constituency
2021 Election
https://www.landtagswahlen.li/resultat/12//12
*/

#define NOMAIN
#include "partylistfile.cpp"
#include "../ham.h"

int main(void)
{
    std::vector<partylist> pls = test_all_pls();
    const int partyc = pls.size();
    party parties[partyc];
    for (int i = 0; i < partyc; i++)
        parties[i] = pls[i].toCParty();
    ham(partyc, parties, 15, dhondt);

    for (partylist pl : pls)
    {
        const int seats = party_get_seats(partyc, parties, pl.id);
        std::vector<candidate::id_type> el = pl.elected(seats);
        for (candidate::id_type cand_id : el)
        {
            std::cout << std::setw(5) << pl.name << " " << cand_id << std::endl;
        }
    }
}