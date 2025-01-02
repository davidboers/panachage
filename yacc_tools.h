
#ifdef __cplusplus
extern "C"
{
#endif

    void yacc_error(const char *filename, char const *s, const char *t, FILE *yyin, int yylineno, int yycolumn, int yyleng, char *yytext);
    bool yy_doesFileExist(const char *filename, FILE *yyin);
    void sanitize_path(char *path);

#ifdef __cplusplus
}
#endif