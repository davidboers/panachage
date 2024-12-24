%option noyywrap
%option yylineno
%option prefix="pl"

%{

// flex -o partylist_lexer.c partylist.l

#include "lex_utils.h"
#include "partylist.tab.h"

#define YY_MAKE_INT pllval=yytext;return number;
#define YY_MAKE_TEXT pllval=yytext;return text1;

%}

%%

".name"           { return opt_name;  }
".id"             { return opt_id;    }
".at-large-votes" { return opt_alv;   }
".at_large_votes" { return opt_alv;   }
".alv"            { return opt_alv;   }
"begin"           { return init_cmd;  }
" = "             { return assign;    }

[\n\r]            { yycolumn = 1;     }
<<EOF>>           { yyterminate();    }
[0-9]+            { YY_MAKE_INT       }
.                 { YY_MAKE_TEXT      }

%%