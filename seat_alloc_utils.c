#pragma once

typedef struct
{
    int votes;
    int seats;
} party;

party party_new(int votes)
{
    party p;
    p.votes = votes;
    p.seats = 0;
    return p;
}

int total_valid_poll(const int partyc, party parties[partyc])
{
    int tvp = 0;
    for (int i = 0; i < partyc; i++)
    {
        tvp += parties[i].votes;
    }
    return tvp;
}

int threshold(const int partyc, party parties[partyc], double pct)
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