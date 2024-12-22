#include "../lrm.c"
#include "../ham.c"

void test_lrm(void)
{
    lrm_party parties[] = {
        lrm_party_new(613), // 62
        lrm_party_new(323), // 32
        lrm_party_new(43),  // 4
        lrm_party_new(13),  // 1
        lrm_party_new(8)};  // 1
    lrm(5, parties, 100);
    lrm_print_table(5, parties);
}

void test_ham(void)
{
    ham_party parties[] = {
        ham_party_new(613), // 65
        ham_party_new(323), // 35
        ham_party_new(43),
        ham_party_new(13),
        ham_party_new(8)};
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