%option noyywrap
%option yylineno
%option prefix="pl"

%{

int plcolumn = 1;
#define yycolumn plcolumn

#include "lex_utils.h"
#include "partylist.tab.c"

void handle_anything_q(char *dest, char *buffer)
{
    const size_t len = strlen(buffer);
    memmove(dest, buffer + 1, len - 1);
    dest[len - 2] = 0;
}

void handle_anything_a(char *dest, char *buffer)
{
    const size_t len = strlen(buffer);
    memmove(dest, buffer + 1, len - 1);
}

#define YY_MAKE_TEXT_Q                   \
    pllval.s = YY_ALLOC_VAL_MEM;         \
    handle_anything_q(pllval.s, yytext); \
    return text;

#define YY_MAKE_TEXT_A                   \
    pllval.s = YY_ALLOC_VAL_MEM;         \
    handle_anything_a(pllval.s, yytext); \
    return cand_name;

%}

anything          .*

%%

".name"           return opt_name;
".id"             return opt_id;
".at-large-votes" return opt_alv;
".at_large_votes" return opt_alv;
".alv"            return opt_alv;
"begin"           return init_cmd;

[0-9]+              YY_MAKE_INT(pllval.i, plnumber)
[ \t]               ;
[\n\r]              YY_RESET_COLUMN
<<EOF>>             YY_END_FILE
\"{anything}\"      YY_MAKE_TEXT_Q
\'{anything}\'      YY_MAKE_TEXT_Q
"@"{anything}/"+"   YY_MAKE_TEXT_A
.                   YY_MAKE_SELF

%%