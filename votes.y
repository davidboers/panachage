%define api.prefix {v}
%parse-param {const char* filename}
%parse-param {std::vector<panachage::Vote*>* votes}
%parse-param {std::vector<panachage::partylist*> lists}
%parse-param {bool create_new_lists}

%{

#include <vector>

#include "yacc_tools.h"

#include "candidate.hpp"
#include "full_list.cpp"
#include "partial_list.cpp"
#include "free_list.cpp"

using panachage::partylist;
using panachage::Vote;
using panachage::candidate;

extern int vlex();

typedef std::vector<Vote *> *yy_votes_param;
typedef std::vector<partylist *> yy_lists_param;

inline void verror(const char *filename, yy_votes_param votes, yy_lists_param lists, bool create_new_lists, char const *s)
{
    yacc_error(filename, s, "vote", yyin, yylineno, yycolumn, yyleng, yytext);
}

partylist *yy_listById(yy_lists_param &lists, partylist::id_type id, bool create_new_lists)
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
            if (create_new_lists) 
            {
                  plist = new partylist(id, std::to_string(id));
                  lists.push_back(plist);
                  return plist;
            } 
            else 
            {
                  printf("Warning: could not find partylist of id: %i\n", id);
                  exit(100);
            }
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

void make_new_copied_vote(yy_votes_param votes, Vote *v, int copies) 
{
      v->setCopies(copies);
      v->setLnParsed(yylineno);
      votes->push_back(v);
}

inline void make_new_vote(yy_votes_param votes, Vote *v) 
{
      v->setLnParsed(yylineno);
      votes->push_back(v);
}

%}

%code requires {
#include "vote.hpp"
#include "partylist.cpp"
#include "lex_utils.h"

namespace panachage {
std::vector<Vote *> *parseVoteFile(const char *filename, std::vector<Vote *> *votes, std::vector<partylist *> lists, bool create_new_lists = false);
void parseSingleVote(const char *input, std::vector<partylist *> lists);
}
}

%define parse.error verbose

%union {
      int i;
      panachage::Vote* v;
      panachage::candidate::id_type cl[YY_MAX_CANDS];
      panachage::partylist* pl;
}

%token full 102    // f
%token partial 112 // p
%token blank 98    // b

%token star 42     // *
%token sep 124     // |
%token numsep 44   // ,

%token <i> vnumber

%type <pl> partylist
%type <v> vote
%type <cl> numbers

%start start

%%

start : parcel       
      | start parcel
      ;

parcel : vnumber star vote { make_new_copied_vote(votes, $3, $1); }
       | vote              { make_new_vote(votes, $1);            }
       ;

vote : full sep partylist                            { $$ = new panachage::FullListVote($3);            }
     | partial sep partylist sep numbers             { $$ = new panachage::PartialListVote($3, $5);     }
     | partial sep partylist sep numbers sep numbers { $$ = new panachage::PartialListVote($3, $5, $7); }
     | blank sep numbers                             { $$ = new panachage::FreeVote($3);                }
     ;

partylist : vnumber { $$ = yy_listById(lists, $1, create_new_lists); } ;

numbers : vnumber                { yy_lst_init($$, $1);   }
        | numbers numsep vnumber { yy_lst_append($$, $3); }
        ;

%%

namespace panachage {

void displayAllCandidates(std::vector<partylist *> lists);

std::vector<Vote *> *parseVoteFile(const char *filename, std::vector<Vote *> *votes, std::vector<partylist *> lists, bool create_new_lists)
{
      RESET_BUFFER;
      yyin = fopen(filename, "r");
      if (!yy_doesFileExist(filename, yyin))
            return votes;
      vparse(filename, votes, lists, create_new_lists);
      fclose(yyin);
      return votes;
}

void parseSingleVote(const char *input, std::vector<partylist *> lists)
{
      std::vector<Vote *> votes;
      const char *temp_filename = "tempparsedoc.txt";
      yyin = fopen(temp_filename, "w");
      fputs(input, yyin);
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

}