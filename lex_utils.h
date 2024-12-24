#pragma once

#include <stdlib.h>

int yycolumn = 1;

#ifndef YY_MAX_CANDS
#define YY_MAX_CANDS 32
#endif
#define YY_USER_ACTION yycolumn+=yyleng;