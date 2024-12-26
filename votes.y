// bison -dy votes.y -b votes

%define api.prefix {v}
%parse-param {const char* filename}
%parse-param {std::vector<panachage::Vote*>* votes}
%parse-param {std::vector<panachage::partylist*> lists}

%{

#include <vector>

#include "yacc_tools.cpp"

using panachage::yy_listById;
using panachage::yy_lst_init;
using panachage::yy_lst_append;

%}

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