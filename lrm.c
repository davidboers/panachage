#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "lrm.h"
#include "seat_alloc_utils.c"

// Quota functions

double hare(const int partyc, party *parties, int seats)
{
    return floor(total_valid_poll(partyc, parties) / (double)seats);
}

double droop(const int partyc, party *parties, int seats)
{
    return floor(total_valid_poll(partyc, parties) / (double)(seats + 1)) + 1;
}

// Procedure

void lrm(const int partyc, party *parties, int seats)
{
    double quota = hare(partyc, parties, seats);
    auto int comp_residual();

    party *p;
    for (int i = 0; i < partyc; i++)
    {
        p = &parties[i];
        p->seats = floor(p->votes / quota);
        seats -= p->seats;
    }
    qsort(parties, partyc, sizeof(party), comp_residual);
    for (p = parties; seats > 0; p++)
    {
        p->seats++;
        seats--;
    }

    int comp_residual(const void *elem1, const void *elem2)
    {
        party i = *((party *)elem1);
        party j = *((party *)elem2);
        int i_residual = i.votes - (i.seats * quota);
        int j_residual = j.votes - (j.seats * quota);
        return (i_residual > j_residual) ? -1 : (i_residual < j_residual) ? 1
                                                                          : 0;
    }
}

// Display

void lrm_print_table(const int partyc, party *parties)
{
    for (int i = 0; i < partyc; i++)
    {
        party p = parties[i];
        printf("| %-8i | %-3i |\n", p.votes, p.seats);
    }
}
