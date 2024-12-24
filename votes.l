%option noyywrap
%option yylineno

%{

// flex -o votes_lexer.c votes.l

#include <stdlib.h>

#include "lex_utils.h"
#include "votes.tab.h"

%}

%%

[0-9]+  { yylval.ival = std::atoi(yytext); return number; }
[ \t]   ;
#.*     ;
[\n\r]  { yycolumn = 1;     }
<<EOF>> { yyterminate();    }
.       { return yytext[0]; }

%%