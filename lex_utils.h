#pragma once

#include <stdlib.h>

int yycolumn = 1;

#define YY_MAX_CANDS 32

#define YY_USER_ACTION yycolumn += yyleng;

#define YY_MAKE_INT(intval)     \
    intval = std::atoi(yytext); \
    return number;

#define YY_MAKE_SELF return yytext[0];

#define YY_RESET_COLUMN yycolumn = 1;

#define YY_END_FILE yyterminate();