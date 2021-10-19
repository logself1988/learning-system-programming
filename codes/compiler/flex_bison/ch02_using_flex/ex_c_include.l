/* process c include directive */
%option noyywrap
%x IFILE

%{
    struct bufstack
    {
        struct bufstack *prev;      /* previous entry */
        YY_BUFFER_STATE bs;         /* saved buffer */
        int lineno;                 /* saved line number */
        char *filename;             /* name of this file */
        FILE *f;                    /* current file */
    } *curbs = 0;

    char *curfilename;              /* name of current input file */

    int newfile(char *fn);
    int popfile(void);
%}

%%
^"#"[ \t]*include[ \t]*[\"<]    { BEGIN IFILE; }
<IFILE>[^ \t\n\">]+             { 
                                    {
                                        int c;
                                        while ((c = input()) && c != '\n') ;
                                    }
                                    yylineno++;
                                    if (!newfile(yytext))
                                        yyterminate();
                                    BEGIN INITIAL;
                                }
<IFILE>.|\n                     { 
                                    fprintf(stderr, "%4d bad include line\n", yylineno);
                                    yyterminate();
                                }
<<EOF>>                         { if(!popfile()) yyterminate(); }
^.                              { fprintf(yyout, "[%20s] %4d %s", curfilename, yylineno, yytext); }
^\n                             { fprintf(yyout, "[%20s] %4d %s", curfilename, yylineno++, yytext); }
\n                              { ECHO; yylineno++; }
.                               { ECHO; }

%%
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "need filename\n");
        return 1;
    }
    if (newfile(argv[1]))
    {
        yylex();
    }
}

int newfile(char *fn)
{
    FILE *f = fopen(fn, "r");
    struct bufstack *bs = malloc(sizeof(struct bufstack));

    if (!f)
    {
        perror(fn);
        return 0;
    }
    if (!bs) 
    {
        perror("malloc");
        exit(1);
    }

    if (curbs) curbs->lineno = yylineno;
    bs->prev = curbs;

    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);  /* setup current entry */
    bs->f = f;
    bs->filename = fn;
    yy_switch_to_buffer(bs->bs);
    
    curbs = bs;
    yylineno = 1;
    curfilename = fn;
    return 1;
}

int popfile(void)
{
    struct bufstack *bs = curbs;
    struct bufstack *prevbs;

    if (!bs) return 0;

    fclose(bs->f);                          /* destroy current entry */
    yy_delete_buffer(bs->bs);

    prevbs = bs->prev;                      /* switch to previous */
    free(bs);

    if (!prevbs) return 0;

    yy_switch_to_buffer(prevbs->bs);
    curbs = prevbs;
    yylineno = curbs->lineno;
    curfilename = curbs->filename;
    return 1;
}