%option noyywrap
%option yylineno

%{

// flex -o votes_lexer.c votes.l

#include <stdlib.h>

int yycolumn = 1;

#define YY_MAX_CANDS 32
#define YY_USER_ACTION yycolumn+=yyleng;

#include "y.tab.h"

%}

%%

[0-9]+  { yylval.ival = std::atoi(yytext); return number; }
[ \t]   ;
#.*     ;
[\n\r]  { yycolumn = 1;     }
<<EOF>> { yyterminate();    }
.       { return yytext[0]; }

%%