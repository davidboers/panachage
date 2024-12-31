// bison -dy partylist.y -b partylist

%define api.prefix {pl}
%parse-param {const char* filename}
%parse-param {panachage::partylist& pl}

%{

#include "yacc_tools.c"

#include "partylist.cpp"

#define YY_DEFAULT_TEMP_PLNAME ""
#define YY_DEFAULT_TEMP_PLID 1
#define YY_DEFAULT_TEMP_ALV 0

static std::string yy_temp_plname = YY_DEFAULT_TEMP_PLNAME;
static panachage::partylist::id_type yy_temp_plid = YY_DEFAULT_TEMP_PLID;
static int yy_temp_alv = YY_DEFAULT_TEMP_ALV;

inline void plerror(const char *filename, panachage::partylist &pl, char const *s)
{
    yacc_error(filename, s, "party list");
}

%}

%code requires {
#include "vote.hpp"
#include "partylist.cpp"
}

%define parse.error verbose

%union {
       char *s;
       char c;
       int i;
}

%type <i> cand_id cand_votes

%token init_cmd

%token opt_name
%token opt_id
%token opt_alv

%token <s> cand_name

%token <s> text
%token <i> number

%start start

%%

start : options init candidates ;

// Options

options : option
        | options option
        ;

option : opt_name '=' text   { yy_temp_plname = $3; }
       | opt_id '=' number   { yy_temp_plid = $3;   }
       | opt_alv '=' number  { yy_temp_alv = $3;    }
       ;

// Initiator

init : init_cmd { pl = panachage::partylist(yy_temp_plid, yy_temp_plname); 
                  pl.at_large_votes = yy_temp_alv;
                } 
                ;

// Candidates

candidates : candidate 
           | candidates candidate
           ;

candidate : cand_id cand_name cand_votes { pl.newCandidate($1, $3); } 
          | cand_id cand_votes           { pl.newCandidate($1, $2); } 
          ;

cand_id : '#' number { $$ = $2; } ;

cand_votes : '+' number { $$ = $2; } ;

%%

namespace panachage {

std::string nameFromFile(const char *filename, const char *ext = ".txt")
{
       char name[strlen(filename)];
       strcpy(name, filename);
       sanitize_path(name);
       if (strstr(filename, ext))
       {
              int dot_index = strlen(name) - strlen(ext);
              name[dot_index] = 0;
       }
       return std::string(name);
}

partylist parsePartyListFile(const char *filename, const char *ext = ".txt")
{
       yy_temp_plid = YY_DEFAULT_TEMP_PLID;
       yy_temp_alv = YY_DEFAULT_TEMP_ALV;
       yy_temp_plname = YY_DEFAULT_TEMP_PLNAME;
       yy_temp_plname = nameFromFile(filename, ext);
       reset_buffer();
       yyin = fopen(filename, "r");
       partylist pl;
       if (!yy_doesFileExist(filename))
       return pl;
       plparse(filename, pl);
       fclose(yyin);
       return pl;
}

}