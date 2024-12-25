#include "../lrm.c"
#include "../ham.c"

void test_lrm(void)
{
    party parties[] = {
        party_new(613), // 62
        party_new(323), // 32
        party_new(43),  // 4
        party_new(13),  // 1
        party_new(8)};  // 1
    lrm(5, parties, 100);
    lrm_print_table(5, parties);
}

void test_ham(void)
{
    party parties[] = {
        party_new(613), // 66
        party_new(323), // 34
        party_new(43),
        party_new(13),
        party_new(8)};
    int partyc = 5;
    partyc = threshold(partyc, parties, 0.05);
    ham(partyc, parties, 100, dhondt);
    ham_print_table(partyc, parties);
}

int main(void)
{
    test_lrm();
    printf("\n");
    test_ham();
}