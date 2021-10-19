/* simple version of calculator */
%{
#include <stdio.h>
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token OP CP                /* open and close parentheses */
%token EOL


%%
root: /* nothing */
  | root exp EOL      { printf("= %d\n", $2); }
  | root EOL          { printf("> "); }
  ;

exp: factor
  | exp ADD factor    { $$ = $1 + $3; }
  | exp SUB factor    { $$ = $1 - $3; }
  ;

factor: term
  | factor MUL term   { $$ = $1 * $3; }
  | factor DIV term   { $$ = $1 / $3; }
  ;

term: NUMBER
  | ABS term          { $$ = $2 >= 0 ? $2 : -$2; }
  | OP exp CP         { $$ = $2; }
  ;

%%
int main(int argc, char **argv)
{
  printf("> ");
  yyparse();
}

void yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
}
