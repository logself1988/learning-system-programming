/* symbol table */
struct symbol
{
    char *name;             /* variable name */
    double value;           
    struct ast *func;       /* stmt for function */
    struct symlist *syms;   /* list of function args */
};

/* fixed sized symtab */
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);

/* list of symbols, for an argument list*/
struct symlist
{
    struct symbol *sym;
    struct symlist *next;
};

struct symlist * newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/* node types
* + - * / |
* 0-7 comparison ops, bit coded: 04 equal, 02 less, 01 greater
* M unary minus
* L statement list
* I IF statement
* W WHILE statement
* N symbol ref
* = assignment
* S list of symbols
* F built in function call
* C user function call
*/

/* built-in functions */
enum bifs
{
    B_sqrt = 1,
    B_exp,
    B_log,
    B_print
};

/* nodes in AST */
struct ast 
{
    int nodetype;
    struct ast *l;
    struct ast *r;
};
/* built-in function */
struct fncall
{
    int nodetype;           /* F */
    struct ast *l;
    enum bifs functype;
};
/* user function */
struct ufncall
{
    int nodetype;           /* C */
    struct ast *l;
    struct symbol *s;
};
/* control flow */
struct flow
{
    int nodetype;           /* I or W */
    struct ast *cond;       /* condition */
    struct ast *tl;         /* then or do list */
    struct ast *el;         /* optional else list */
};
struct numval
{
    int nodetype;           /* K */
    double number;
};
struct symref
{
    int nodetype;           /* N */
    struct symbol *s;
};
struct symasgn
{
    int nodetype;           /* = */
    struct symbol *s;
    struct ast *v;          /* value */
};

/* build AST */
struct ast * newast(int nodetype, struct ast *l, struct ast *r);
struct ast * newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast * newfunc(int functype, struct ast *l);
struct ast * newcall(struct symbol *s, struct ast *l);
struct ast * newref(struct symbol *s);
struct ast * newasgn(struct symbol *s, struct ast *v);
struct ast * newnum(double d);
struct ast * newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate AST */
double eval(struct ast *);

/* delete and free AST */
void treefree(struct ast *);

/* interface to lexer */
extern int yylineno;        /* from lexer */
void yyerror(char *s, ...);

extern int debug;
void dumpast(struct ast *a, int level);