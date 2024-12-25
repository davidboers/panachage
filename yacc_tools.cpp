#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#include "candidate.hpp"
#include "partylist.cpp"
#include "vote.hpp"
#include "full_list.cpp"
#include "partial_list.cpp"
#include "free_list.cpp"

namespace panachage
{

    typedef std::vector<Vote *> *yy_votes_param;
    typedef std::vector<partylist *> yy_lists_param;

    partylist *yy_listById(yy_lists_param lists, partylist::id_type id)
    {
        partylist *plist;
        for (partylist *i : lists)
        {
            if (i->id == id)
            {
                plist = i;
                break;
            }
        }

        if (!plist)
        {
            printf("Warning: could not find partylist of id: %i\n", id);
            exit(100);
        }

        return plist;
    }

    inline void yy_lst_init(candidate::id_type *cand_list, int id)
    {
        *cand_list = id;
    }

    inline void yy_lst_append(candidate::id_type *cand_list, int id)
    {
        // ew.
        for (int i = 0; i < YY_MAX_CANDS; i++)
        {
            if (!cand_list[i])
            {
                cand_list[i] = id;
                break;
            }
        }
    }

}

void yacc_error(const char *filename, char const *s, const char *t)
{
    extern int yylineno;
    extern int yycolumn;
    extern char *yytext;
    const int expr_size = 255;
    char expr[expr_size];
    FILE *file = fopen(filename, "r");
    for (int l = 1; l <= yylineno; l++)
    {
        fgets(expr, expr_size, file);
        char *lb = strchr(expr, '\n');
        if (lb)
            *lb = 0;
    }

    printf("Error parsing %s file:\n", t);
    printf("%s:%i:%i: %s\n", filename, yylineno, yycolumn, s);
    printf("%i: %s\n", yylineno, expr);

    const int num_wspc = 2 + std::to_string(yylineno).length() + (yycolumn - 1);
    std::string lead_wspc(num_wspc, ' ');
    printf("%s^\n", lead_wspc.c_str());

    printf("Char dumps (yytext): ");
    char h;
    while (*yytext)
    {
        h = *yytext++;
        printf("%i", h);
        if (h >= ' ' && h <= '~')
        {
            printf("(%c) ", h);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}

#ifndef JUST_PARTYLIST
inline void verror(const char *filename, panachage::yy_votes_param votes, panachage::yy_lists_param lists, char const *s)
{
    yacc_error(filename, s, "vote");
}
#endif
#ifndef JUST_VOTES
inline void plerror(const char *filename, panachage::partylist *pl, char const *s)
{
    yacc_error(filename, s, "party list");
}
#endif