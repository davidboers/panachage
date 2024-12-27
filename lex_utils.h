#pragma once

#include <stdlib.h>
#include <string.h>

int yycolumn = 1;

#define YY_MAX_CANDS 32

#define YY_USER_ACTION yycolumn += yyleng;

#define YY_MAKE_INT(intval) \
    intval = atoi(yytext);  \
    return number;

#define YY_MAKE_SELF return yytext[0];

#define YY_RESET_COLUMN yycolumn = 1;

#define YY_END_FILE yyterminate();

#define YY_ALLOC_VAL_MEM (char *)malloc(yyleng)

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
