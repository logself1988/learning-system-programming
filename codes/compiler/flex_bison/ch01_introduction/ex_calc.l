%{
/* use tokens defined in bison */
#include "ex_calc.tab.h"
%}

%%
"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"|"     { return ABS; }
"("     { return OP; }
")"     { return CP; }
[0-9]+  { yylval = atoi(yytext);
          printf("yylval = %d\n", yylval); /* DEBUG */
          return NUMBER;
        }
\n      { return EOL; }
[ \t]   { /* ignore whitespace */}
.       { printf("Mystery character %c\n", *yytext); }

%%
