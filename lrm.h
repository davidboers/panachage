#include "seat_alloc_utils.c"

#ifdef __cplusplus
extern "C"
{
#endif

    double hare(const int partyc, party *parties, int seats);
    double droop(const int partyc, party *parties, int seats);

    void lrm(const int partyc, party *parties, int seats);

#ifdef __cplusplus
}
#endif