// bison -dy partylist.y -b partylist

%define api.prefix {pl}
%parse-param {const char* filename}
%parse-param {panachage::partylist* pl}

%{

#include "yacc_tools.c"

#include "partylist.cpp"

#define YY_DEFAULT_TEMP_PLNAME ""
#define YY_DEFAULT_TEMP_PLID 1
#define YY_DEFAULT_TEMP_ALV 0

static std::string yy_temp_plname = YY_DEFAULT_TEMP_PLNAME;
static panachage::partylist::id_type yy_temp_plid = YY_DEFAULT_TEMP_PLID;
static int yy_temp_alv = YY_DEFAULT_TEMP_ALV;

inline void plerror(const char *filename, panachage::partylist *pl, char const *s)
{
    yacc_error(filename, s, "party list");
}

%}

%union {
       char *s;
       char c;
       int i;
}

%type <s> string cand_name
%type <i> cand_id cand_votes

%token init_cmd

%token opt_name
%token opt_id
%token opt_alv

%token <s> text

%token <i> number

%start start

%%

start : options init candidates ;

// Options

options : option
        | options option
        ;

option : opt_name '=' string { yy_temp_plname = $3; }
       | opt_id '=' number   { yy_temp_plid = $3;   }
       | opt_alv '=' number  { yy_temp_alv = $3;    }
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

candidate : cand_id cand_name cand_votes { pl->newCandidate($1, $3); } 
          | cand_id cand_votes           { pl->newCandidate($1, $2); } 
          ;

cand_id : '#' number { $$ = $2; } ;

cand_name : '@' text { $$ = $2; } ;

cand_votes : '+' number { $$ = $2; } ;

// Data types

string : '\'' text '\'' { $$ = $2; }
       | '\"' text '\"' { $$ = $2; }
       ;

%%