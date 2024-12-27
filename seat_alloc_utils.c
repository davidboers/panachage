#pragma once

#ifndef party_id_type
#define party_id_type unsigned int
#endif

typedef struct
{
    party_id_type id;
    int votes;
    int seats;
} party;

party party_new(const party_id_type id, int votes)
{
    party p;
    p.id = id;
    p.votes = votes;
    p.seats = 0;
    return p;
}

int party_get_seats(const int partyc, party *parties, const party_id_type id)
{
    for (int i = 0; i < partyc; i++)
    {
        party p = parties[i];
        if (p.id == id)
        {
            return p.seats;
        }
    }
    return -1;
}

int total_valid_poll(const int partyc, party *parties)
{
    int tvp = 0;
    for (int i = 0; i < partyc; i++)
    {
        tvp += parties[i].votes;
    }
    return tvp;
}

int threshold(const int partyc, party *parties, double pct)
{
    int tv = total_valid_poll(partyc, parties);
    int th = floor(tv * pct);
    party filtered[partyc];
    int new_size = 0;
    for (int i = 0; i < partyc; i++)
    {
        party p = parties[i];
        if (p.votes >= th)
        {
            *filtered = p;
            new_size++;
        }
    }
    parties = filtered;
    return new_size;
}