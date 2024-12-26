%option noyywrap
%option yylineno
%option prefix="v"

%{

// flex -o votes_lexer.c votes.l

#include "lex_utils.h"
#include "votes.tab.h"

%}

%%

[0-9]+  YY_MAKE_INT(vlval.i)
[ \t]   ;
#.*     ;
[\n\r]  YY_RESET_COLUMN
<<EOF>> YY_END_FILE
.       YY_MAKE_SELF

%%