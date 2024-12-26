%option noyywrap
%option yylineno
%option prefix="pl"

%{

// flex -o partylist_lexer.c partylist.l

#include "lex_utils.h"
#include "partylist.tab.h"

#define YY_MAKE_INT pllval.i=std::atoi(yytext);return number;
#define YY_MAKE_TEXT pllval.s=yytext;return text;
#define YY_MAKE_SELF return yytext[0];

%}

%%

".name"           { return opt_name;  }
".id"             { return opt_id;    }
".at-large-votes" { return opt_alv;   }
".at_large_votes" { return opt_alv;   }
".alv"            { return opt_alv;   }
"begin"           { return init_cmd;  }

[0-9]+            { YY_MAKE_INT       }
[ \t]             ;
[\n\r]            { yycolumn = 1;     }
<<EOF>>           { yyterminate();    }
[a-zA-Z ]+        { YY_MAKE_TEXT      }
.                 YY_MAKE_SELF

%%