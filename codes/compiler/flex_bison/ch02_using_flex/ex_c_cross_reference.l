/* use symbol table to track c cross reference */
%option noyywrap nodefault yylineno

%x COMMENT
%x IFILE

/* some named patterns */
/* Universal Character Name */
UCN	(\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
/* float exponent */
EXP ([Ee][-+]?[0-9]+)
/* integer length */
ILEN    ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)

%{
    /* the symbol table */
    struct symbol                   /* variable name */
    {
        struct ref *reflist;
        char *name;
    };

    struct ref 
    {
        struct ref *next;
        char *filename;
        int flags;                  /* 01-definition */
        int lineno;
    };

    #define NHASH 9997
    struct symbol symtab[NHASH];

    struct symbol *loopup(char*);
    void addref(int, char*, char*, int);

    char *curfilename;              /* current file name */

    /* include file stack */
    struct bufstack
    {
        struct bufstack *prev;
        YY_BUFFER_STATE bs;
        int lineno;
        char *filename;
        FILE *f;
    } *curbs;

    int newfile(char *fn);
    int popfile(void);

    int defining;                  /* names are probably definition*/
%}

%%
 /* comment */
"/*"                    { BEGIN COMMENT; }
<COMMENT>"*/"           { BEGIN INITIAL;}
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>        { printf("%s:%d: Unterminated comment\n", curfilename, yylineno); return 0; }
"//".*\n

 /* declaration keywords */
_Bool |
_Complex |
_Imaginary |
auto |
char |
const |
double |
enum |
extern |
float |
inline |
int |
long |
register |
restrict |
short |
signed |
static |
struct |
typedef |
union |
unsigned |
void |
volatite                                { defining = 1; }

break
case
continue
default
do
else
for
goto
if
return
sizeof
switch
while

 /* constants */

 /* integers */
0[0-7]*{ILEN}?
[1-9][0-9]*{ILEN}?
0[Xx][0-9a-fA-F]+{ILEN}?


 /* decimals */
([0-9]*\.[0-9]+|[0-9]+\.){EXP}?[flFL]?
[0-9]+{EXP}[flFL]?

 /* hex */
0[Xx]([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]?

 /* char */
\'([^'\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})+\'

 /* string literal */
L?\"([^\"\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})+\"

 /* punctuations */
"{"|"<%"|";"                            { defining = 0; }


"["|"]"|"("|")"|"{"|"}"|"."|"->"
"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"
"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"
"?"|":"|";"|"..."
"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^=""|="
","|"#"|"##"
"<:"|":>"|"%>"|"%:"|"%:%:"

 /* identifier */
([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*      { addref(yylineno, curfilename, yytext, defining); }

 /* whitespace */
[ \t\n]+

 /* continues line */
\\$

 /* preprocessor directives */
"#"" "*if.*\n
"#"" "*else.*\n
"#"" "*endif.*\n
"#"" "*define.*\n
"#"" "*line.*\n

 /* includes */
^"#"[ \t]*include[ \t]*[\"<]    { BEGIN IFILE; }
<IFILE>[^ \t\n\">]+             { 
                                    {
                                        int c;
                                        while ((c = input()) && c != '\n') ;
                                    }
                                    if (!newfile(yytext))
                                        yyterminate();
                                    BEGIN INITIAL;
                                }
<IFILE>.|\n                     { 
                                    fprintf(stderr, "%4d bad include line\n", yylineno);
                                    BEGIN INITIAL;
                                }
<<EOF>>                         { if(!popfile()) yyterminate(); }

 /* invalid character */
.                               { printf("%s:%d: Mystery character '%s'\n", curfilename, yylineno, yytext); }

%%

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

static unsigned symhash(char *sym)
{
  unsigned int hash = 0;
  unsigned c;

  while(c = *sym++) hash = hash*9 ^ c;

  return hash;
}

struct symbol * lookup(char* sym)
{
  struct symbol *sp = &symtab[symhash(sym)%NHASH];
  int scount = NHASH;		/* how many have we looked at */

  while(--scount >= 0) {
    if(sp->name && !strcmp(sp->name, sym)) { return sp; }

    if(!sp->name) {		/* new entry */
      sp->name = strdup(sym);
      sp->reflist = 0;
      return sp;
    }

    if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
  }
  fputs("symbol table overflow\n", stderr);
  abort(); /* tried them all, table is full */

}

void addref(int lineno, char *filename, char *word, int flags)
{
    struct ref *r;
    struct symbol *sp = lookup(word);

    /* don't do dups of same line and file */
    if(sp->reflist && 
    sp->reflist->lineno == lineno &&
    sp->reflist->filename == filename) 
        return;

    r = malloc(sizeof(struct ref));
    if(!r) { fputs("out of space\n", stderr); abort(); }
    r->next = sp->reflist;
    r->filename = filename;
    r->lineno = lineno;
    r->flags = flags;
    sp->reflist = r;
}

/* aux function for sorting */
static int symcompare(const void *xa, const void *xb)
{
    const struct symbol *a = xa;
    const struct symbol *b = xb;
    if(!a->name) 
    {
        if(!b->name) return 0; /* both empty */
        return 1; /* put empties at the end */
    }
    if(!b->name) return -1;
    return strcmp(a->name, b->name);
}

void printrefs()
{
  struct symbol *sp;

  qsort(symtab, NHASH, sizeof(struct symbol), symcompare); /* sort the symbol table */

  for(sp = symtab; sp->name && sp < symtab+NHASH; sp++) {
    char *prevfn = NULL;	/* last printed filename, to skip dups */

    /* reverse the list of references */
    struct ref *rp = sp->reflist;
    struct ref *rpp = 0;	/* previous ref */
    struct ref *rpn;	/* next ref */

    do {
      rpn = rp->next;
      rp->next = rpp;
      rpp = rp;
      rp = rpn;
    } while(rp);

    /* now print the word and its references */
    printf("%10s", sp->name);
    for(rp = rpp; rp; rp = rp->next) {
      if(rp->filename == prevfn) {
	printf(" %d", rp->lineno);
      } else {
	printf(" %s:%d", rp->filename, rp->lineno);
	prevfn = rp->filename;
      }
      if(rp->flags & 01) printf("*");
    }
    printf("\n");
  }
}

int main(int argc, char **argv)
{
    int i;
    
    if (argc < 2)
    {
        fprintf(stderr, "need filename\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        if (newfile(argv[i]))
            yylex();
    }

    printrefs();
    
    return 0;
}