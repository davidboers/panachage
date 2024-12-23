#include <stdio.h>
#include <iostream>
#include <vector>

#include "vote.hpp"
#include "partylist.cpp"

#include "lex.yy.c"
#include "y.tab.c"

extern FILE *yyin;
extern int yyparse(const char *, panachage::yy_votes_param, panachage::yy_lists_param);

namespace panachage
{

    std::vector<Vote *> *parseVoteFile(const char *filename, std::vector<Vote *> *votes, std::vector<partylist *> lists)
    {
        yyin = fopen(filename, "r");
        if (!yyin)
        {
            fclose(yyin);
            std::cout << filename << " does not exist." << std::endl;
            return votes;
        }

        yyparse(filename, votes, lists);
        fclose(yyin);
        return votes;
    }

}