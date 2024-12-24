%option noyywrap
%option yylineno
%option prefix="v"

%{

// flex -o votes_lexer.c votes.l

#include "lex_utils.h"
#include "votes.tab.h"

%}

%%

[0-9]+  { vlval.ival = std::atoi(yytext); return number; }
[ \t]   ;
#.*     ;
[\n\r]  { yycolumn = 1;     }
<<EOF>> { yyterminate();    }
.       { return yytext[0]; }

%%