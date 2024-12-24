#pragma once

int yycolumn = 1;

#define YY_MAX_CANDS 32
#define YY_USER_ACTION yycolumn+=yyleng;