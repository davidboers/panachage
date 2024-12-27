%option noyywrap
%option yylineno
%option prefix="pl"

%{

// flex -o partylist_lexer.c partylist.l

#include "lex_utils.h"
#include "partylist.tab.h"

#define YY_MAKE_TEXT pllval.s=yytext;return text;

%}

anything          .*

%%

".name"           return opt_name;
".id"             return opt_id;
".at-large-votes" return opt_alv;
".at_large_votes" return opt_alv;
".alv"            return opt_alv;
"begin"           return init_cmd;

[0-9]+            YY_MAKE_INT(pllval.i)
[ \t]             ;
[\n\r]            YY_RESET_COLUMN
<<EOF>>           YY_END_FILE
\"{anything}\"    YY_MAKE_TEXT
\'{anything}\'    YY_MAKE_TEXT
.                 YY_MAKE_SELF

%%