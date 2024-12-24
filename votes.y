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
      int ival;
      panachage::Vote* vval;
      panachage::candidate::id_type clval[YY_MAX_CANDS];
      panachage::partylist* plval;
}

%token full 102    // f
%token partial 112 // p
%token blank 98    // b

%token star 42     // *
%token sep 124     // |
%token numsep 44   // ,

%token number

%start start

%%

start : parcel       
      | start parcel
      ;

parcel : number star vote { $<vval>3->setCopies($<ival>1); votes->push_back($<vval>3); }
       | vote             { votes->push_back($<vval>1);                                }
       ;

vote : full sep partylist                            { $<vval>$ = new panachage::FullListVote($<plval>3);                          }
     | partial sep partylist sep numbers             { $<vval>$ = new panachage::PartialListVote($<plval>3, $<clval>5);            }
     | partial sep partylist sep numbers sep numbers { $<vval>$ = new panachage::PartialListVote($<plval>3, $<clval>5, $<clval>7); }
     | blank sep numbers                             { $<vval>$ = new panachage::FreeVote($<clval>3);                              }
     ;

partylist : number { $<plval>$ = yy_listById(lists, $<ival>1); } ;

numbers : number                { yy_lst_init($<clval>$, $<ival>1);   }
        | numbers numsep number { yy_lst_append($<clval>$, $<ival>3); }
        ;

%%