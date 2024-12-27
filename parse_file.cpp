#include <stdio.h>
#include <iostream>
#include <vector>

#include "vote.hpp"
#include "partylist.cpp"

#ifndef JUST_PARTYLIST
#include "votes_lexer.c"
#include "votes.tab.c"
#include "display.cpp"
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

    void reset_buffer()
    {
        yylineno = 1;
        yycolumn = 1;
        YY_FLUSH_BUFFER;
    }

#ifndef JUST_PARTYLIST

    std::vector<Vote *> *parseVoteFile(const char *filename, std::vector<Vote *> *votes, std::vector<partylist *> lists)
    {
        reset_buffer();
        yyin = fopen(filename, "r");
        if (!yy_doesFileExist(filename))
            return votes;
        vparse(filename, votes, lists);
        fclose(yyin);
        return votes;
    }

    void parseSingleVote(const char *text, std::vector<partylist *> lists)
    {
        std::vector<Vote *> votes;
        const char *temp_filename = "tempparsedoc.txt";
        yyin = fopen(temp_filename, "w");
        fputs(text, yyin);
        fclose(yyin);
        parseVoteFile(temp_filename, &votes, lists);
        if (votes.size() == 0)
        {
            std::cout << "No (valid) votes could be parsed." << std::endl;
        }
        else if (votes.size() == 1)
        {
            Vote *vote = votes.front();
            if (vote->validate())
            {
                vote->count(lists);
                displayAllCandidates(lists);
            }
            else
            {
                std::cout << "That vote is invalid." << std::endl;
            }
        }
        else
        {
            std::cout << "Try parsing again with only one vote." << std::endl;
        }
        remove(temp_filename);
    }

#endif
#ifndef JUST_VOTES

    partylist parsePartyListFile(const char *filename, const char *ext = ".txt")
    {
        yy_temp_plid = YY_DEFAULT_TEMP_PLID;
        yy_temp_alv = YY_DEFAULT_TEMP_ALV;
        yy_temp_plname = std::string(filename);
        const int name_len = strlen(filename) - strlen(ext);
        yy_temp_plname = yy_temp_plname.substr(0, name_len);
        reset_buffer();
        yyin = fopen(filename, "r");
        partylist pl;
        if (!yy_doesFileExist(filename))
            return pl;
        plparse(filename, pl);
        fclose(yyin);
        return pl;
    }

#endif

}