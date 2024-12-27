#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "ham.h"

// Quotient functions

double dhondt(party p)
{
    return p.votes / (double)(p.seats + 1);
}

double sainte_laguë(party p)
{
    return p.votes / (double)(2 * p.seats + 1);
}

// Procedure

void ham(const int partyc, party *parties, int seats, __quotient_func method)
{
    auto int comp();
    party *p;
    for (int i = 0; i < seats; i++)
    {
        qsort(parties, partyc, sizeof(party), comp);
        p = parties;
        p->seats++;
    }

    int comp(const void *elem1, const void *elem2)
    {
        double i = method(*((party *)elem1));
        double j = method(*((party *)elem2));
        return (i > j) ? -1 : (i < j) ? 1
                                      : 0;
    }
}

// Display

void ham_print_table(const int partyc, party *parties)
{
    int total_seats = 0;
    for (int i = 0; i < partyc; i++)
    {
        party p = parties[i];
        printf("| %-8i | %-3i |\n", p.votes, p.seats);
        total_seats += p.seats;
    }
    printf("  %-8c | %-3i |", ' ', total_seats);
}