#include <stdio.h>
#include <stdlib.h>

void yacc_error(const char *filename, char const *s, const char *t)
{
    extern int yylineno;
    extern int yycolumn;
    extern char *yytext;
    const int expr_size = 255;
    char expr[expr_size];
    FILE *file = fopen(filename, "r");
    for (int l = 1; l <= yylineno; l++)
    {
        fgets(expr, expr_size, file);
        char *lb = strchr(expr, '\n');
        if (lb)
            *lb = 0;
    }

    printf("Error parsing %s file:\n", t);
    printf("%s:%i:%i: %s\n", filename, yylineno, yycolumn, s);
    printf("%i: %s\n", yylineno, expr);

    char linenumstr[10];
    sprintf(linenumstr, "%s", yylineno);
    const int num_wspc = 2 + strlen(linenumstr) + (yycolumn - 1);
    for (int i = 0; i < num_wspc; i++)
        printf(" ");
    printf("^\n");

    printf("Char dumps (yytext): ");
    char h;
    while (*yytext)
    {
        h = *yytext++;
        printf("%i", h);
        if (h >= ' ' && h <= '~')
        {
            printf("(%c) ", h);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}
