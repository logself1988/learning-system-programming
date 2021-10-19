%{
#define YY_DECL int yylex(int *fruitp)
%}
%%
apple|orange    { (*fruitp)++; }
%%