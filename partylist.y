// bison -dy partylist.y -b partylist

%define api.value.type {char*}
%define api.prefix {pl}
%parse-param {const char* filename}
%parse-param {panachage::partylist* pl}

%{

#include "yacc_tools.cpp"
#include "partylist.cpp"

#define YY_DEFAULT_TEMP_PLNAME nullptr
#define YY_DEFAULT_TEMP_PLID 1
#define YY_DEFAULT_TEMP_ALV 0

static char* yy_temp_plname = YY_DEFAULT_TEMP_PLNAME;
static panachage::partylist::id_type yy_temp_plid = YY_DEFAULT_TEMP_PLID;
static int yy_temp_alv = YY_DEFAULT_TEMP_ALV;

%}

%token pound '#'
%token at '@'
%token plus '+'

%token init_cmd

%token opt_name
%token opt_id
%token opt_alv
%token assign

%token text1
%token number

%start start

%%

start : options init candidates ;

// Options

options : option
        | options option
        ;

option : opt_name assign string { yy_temp_plname = $3;          }
       | opt_id assign number   { yy_temp_plid = std::atoi($3); }
       | opt_alv assign number  { yy_temp_alv = std::atoi($3);  }
       ;

// Initiator

init : init_cmd { pl = new panachage::partylist(yy_temp_plid, yy_temp_plname); 
                  pl->at_large_votes = yy_temp_alv;
                } 
                ;

// Candidates

candidates : candidate 
           | candidates candidate
           ;

candidate : cand_id cand_name cand_votes { pl->newCandidate(std::atoi($1), std::atoi($3)); } 
          | cand_id cand_votes           { pl->newCandidate(std::atoi($1), std::atoi($2)); } 
          ;

cand_id : pound number { $$ = $2; } ;

cand_name : at string { $$ = $2; } ;

cand_votes : plus number { $$ = $2; } ;

// Data types

string : '\'' text '\'' { $$ = $2; }
       | '\"' text '\"' { $$ = $2; }
       | text           { $$ = $1; }
       ;

text : text1      { $$ = $1;                 }
     | text text1 { std::strncat($1, $2, 1); }
     ;

%%