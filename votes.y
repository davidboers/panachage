// bison -dy votes.y -b votes

%define api.prefix {v}
%parse-param {const char* filename}
%parse-param {std::vector<panachage::Vote*>* votes}
%parse-param {std::vector<panachage::partylist*> lists}

%{

#include <vector>

#include "yacc_tools.c"

#include "candidate.hpp"
#include "full_list.cpp"
#include "partial_list.cpp"
#include "free_list.cpp"

using panachage::partylist;
using panachage::Vote;
using panachage::candidate;

typedef std::vector<Vote *> *yy_votes_param;
typedef std::vector<partylist *> yy_lists_param;

inline void verror(const char *filename, yy_votes_param votes, yy_lists_param lists, char const *s)
{
    yacc_error(filename, s, "vote");
}

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

%}

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

%token <i> number

%type <pl> partylist
%type <v> vote
%type <cl> numbers

%start start

%%

start : parcel       
      | start parcel
      ;

parcel : number star vote { $3->setCopies($1); votes->push_back($3); }
       | vote             { votes->push_back($1);                    }
       ;

vote : full sep partylist                            { $$ = new panachage::FullListVote($3);            }
     | partial sep partylist sep numbers             { $$ = new panachage::PartialListVote($3, $5);     }
     | partial sep partylist sep numbers sep numbers { $$ = new panachage::PartialListVote($3, $5, $7); }
     | blank sep numbers                             { $$ = new panachage::FreeVote($3);                }
     ;

partylist : number { $$ = yy_listById(lists, $1); } ;

numbers : number                { yy_lst_init($$, $1);   }
        | numbers numsep number { yy_lst_append($$, $3); }
        ;

%%