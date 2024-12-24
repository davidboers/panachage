#include <stdio.h>
#include <iostream>
#include <vector>

#include "vote.hpp"
#include "partylist.cpp"

#ifndef JUST_PARTYLIST
#include "votes_lexer.c"
#include "votes.tab.c"
#endif
#ifndef JUST_VOTES
#include "partylist_lexer.c"
#include "partylist.tab.c"
#endif

namespace panachage
{

    bool yy_doesFileExist(const char *filename)
    {
        if (!yyin)
        {
            fclose(yyin);
            std::cout << filename << " does not exist." << std::endl;
            return false;
        }
        return true;
    }

#ifndef JUST_PARTYLIST

    std::vector<Vote *> *parseVoteFile(const char *filename, std::vector<Vote *> *votes, std::vector<partylist *> lists)
    {
        yyin = fopen(filename, "r");
        if (!yy_doesFileExist(filename))
            return votes;
        vparse(filename, votes, lists);
        fclose(yyin);
        return votes;
    }

#endif
#ifndef JUST_VOTES

    partylist *parsePartyListFile(const char *filename)
    {
        yy_temp_plname = YY_DEFAULT_TEMP_PLNAME;
        yy_temp_plid = YY_DEFAULT_TEMP_PLID;
        yy_temp_alv = YY_DEFAULT_TEMP_ALV;
        yyin = fopen(filename, "r");
        partylist* pl;
        if (!yy_doesFileExist(filename))
            return pl;
        plparse(filename, pl);
        fclose(yyin);
        return pl;
    }

#endif

}