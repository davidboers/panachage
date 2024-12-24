#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int votes;
    int seats;
} ham_party;

ham_party ham_party_new(int votes)
{
    ham_party p;
    p.votes = votes;
    p.seats = 0;
    return p;
}

// Quotient functions

typedef double (*__quotient_func)(ham_party);

double dhondt(ham_party p)
{
    return p.votes / (double)(p.seats + 1);
}

double sainte_laguë(ham_party p)
{
    return p.votes / (double)(2 * p.seats + 1);
}

static __quotient_func __qf;

// Procedure

int comp(const void *elem1, const void *elem2)
{
    double i = __qf(*((ham_party *)elem1));
    double j = __qf(*((ham_party *)elem2));
    return (i > j) ? -1 : (i < j) ? 1
                                  : 0;
}

void ham(const int partyc, ham_party parties[partyc], int seats, __quotient_func method)
{
    __qf = method;
    ham_party *p;
    for (int i = 0; i < seats; i++)
    {
        qsort(parties, partyc, sizeof(ham_party), comp);
        p = parties;
        p->seats++;
    }
}

// Threshold

int total_votes(const int partyc, ham_party parties[partyc])
{
    int tv = 0;
    for (int i = 0; i < partyc; i++)
    {
        ham_party p = parties[i];
        tv += p.votes;
    }
    return tv;
}

int threshold(const int partyc, ham_party parties[partyc], double pct)
{
    int tv = total_votes(partyc, parties);
    int th = floor(tv * pct);
    ham_party filtered[partyc];
    int new_size = 0;
    for (int i = 0; i < partyc; i++)
    {
        ham_party p = parties[i];
        if (p.votes >= th)
        {
            *filtered = p;
            new_size++;
        }
    }
    parties = filtered;
    return new_size;
}

// Display

void ham_print_table(const int partyc, ham_party parties[partyc])
{
    int total_seats = 0;
    for (int i = 0; i < partyc; i++)
    {
        ham_party p = parties[i];
        printf("| %-8i | %-3i |\n", p.votes, p.seats);
        total_seats += p.seats;
    }
    printf("  %-8c | %-3i |", ' ', total_seats);
}