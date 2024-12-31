%option noyywrap
%option yylineno
%option prefix="v"

%{

#include "lex_utils.h"
#include "votes.tab.c"

YY_INIT_COLUMN;

%}

%%

[0-9]+  YY_MAKE_INT(vlval.i)
[ \t]   ;
#.*     ;
[\n\r]  YY_RESET_COLUMN
<<EOF>> YY_END_FILE
.       YY_MAKE_SELF

%%