#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern int yycolumn;
extern char *yytext;
extern int yyleng;
extern FILE *yyin;

void yacc_error(const char *filename, char const *s, const char *t)
{
    const int expr_size = 255;
    char expr[expr_size];
    rewind(yyin);
    for (int l = 1; l <= yylineno; l++)
    {
        fgets(expr, expr_size, yyin);
        char *lb = strchr(expr, '\n');
        if (lb)
            *lb = 0;
    }
    fclose(yyin);

    char *e = strstr(expr, yytext);
    int error_begin;
    if (e != NULL)
    {
        error_begin = (int)(e - expr) + 1;
    }
    else
    {
        error_begin = yycolumn;
    }

    printf("Error parsing %s file:\n", t);
    printf("%s:%i:%i: %s\n", filename, yylineno, error_begin, s);
    printf("%-3i | %s\n", yylineno, expr);

    const int extra_spc = 6;
    const int x = error_begin + yyleng;
    for (int i = -extra_spc; i < x; i++)
    {
        if (i == 0)
        {
            continue;
        }
        else if (i < error_begin)
        {
            printf(" ");
        }
        else if (i == error_begin)
        {
            printf("^");
        }
        else
        {
            printf("~");
        }
    }

    printf("\n");

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
