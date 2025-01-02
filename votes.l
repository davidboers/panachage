%option noyywrap
%option yylineno
%option prefix="v"

%{

int vcolumn = 1;
#define yycolumn vcolumn

#include "lex_utils.h"
#include "votes.tab.c"

%}

%%

[0-9]+  YY_MAKE_INT(vlval.i, vnumber)
[ \t]   ;
#.*     ;
[\n\r]  YY_RESET_COLUMN
<<EOF>> YY_END_FILE
.       YY_MAKE_SELF

%%