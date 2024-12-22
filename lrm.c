#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int votes;
    int full_quotas;
    int residual;
    int extra_seats;
    int total_seats;
} lrm_party;

lrm_party lrm_party_new(int votes)
{
    lrm_party p;
    p.votes = votes;
    p.full_quotas = p.residual = p.extra_seats = p.total_seats = 0;
    return p;
}

int total_valid_poll(const int partyc, lrm_party parties[partyc])
{
    int tvp = 0;
    for (int i = 0; i < partyc; i++)
    {
        tvp += parties[i].votes;
    }
    return tvp;
}

double hare(const int partyc, lrm_party parties[partyc], int seats)
{
    return floor(total_valid_poll(partyc, parties) / (double)seats);
}

int comp_residual(const void *elem1, const void *elem2)
{
    lrm_party i = *((lrm_party *)elem1);
    lrm_party j = *((lrm_party *)elem2);
    return (i.residual > j.residual) ? -1 : (i.residual < j.residual) ? 1
                                                                      : 0;
}

void lrm(const int partyc, lrm_party parties[partyc], int seats)
{
    double quota = hare(partyc, parties, seats);
    lrm_party *p;
    for (int i = 0; i < partyc; i++)
    {
        p = &parties[i];
        p->full_quotas = floor(p->votes / quota);
        p->residual = p->votes - (p->full_quotas * quota);
        p->total_seats = p->full_quotas;
        seats -= p->total_seats;
    }
    qsort(parties, partyc, sizeof(lrm_party), comp_residual);
    for (p = parties; seats > 0; p++)
    {
        p->extra_seats++;
        p->total_seats++;
        seats--;
    }
}

// Display

void lrm_print_table(const int partyc, lrm_party parties[partyc])
{
    for (int i = 0; i < partyc; i++)
    {
        lrm_party p = parties[i];
        printf("| %-8i | %-3i | %-8i | %-3i | %-3i |\n", p.votes, p.full_quotas, p.residual, p.extra_seats, p.total_seats);
    }
}
