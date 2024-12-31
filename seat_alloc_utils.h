#pragma once

#ifndef party_id_type
#define party_id_type unsigned int
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        party_id_type id;
        int votes;
        int seats;
    } party;

    party party_new(const party_id_type id, int votes);
    int party_get_seats(const int partyc, party *parties, const party_id_type id);
    int total_valid_poll(const int partyc, party *parties);
    int threshold(const int partyc, party *parties, double pct);

#ifdef __cplusplus
}
#endif