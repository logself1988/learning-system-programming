/* interface to the lexer */
extern int yylineno;            /* from lexer */
void yyerror(char *s, ...);

/* nodes in the AST */
struct ast 
{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval 
{
    int nodetype; /* type 'K' for constant */
    double number;
};

/* build AST */
struct ast * newast(int nodetype, struct ast* l, struct ast* r);
struct ast * newnum(double d);

/* evaluate AST */
double eval(struct ast *);

/* delete and free AST */
void treefree(struct ast *);
