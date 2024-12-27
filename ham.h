#include "seat_alloc_utils.c"

double dhondt(party p);
double sainte_laguë(party p);

typedef double (*__quotient_func)(party);

void ham(const int partyc, party *parties, int seats, __quotient_func method);