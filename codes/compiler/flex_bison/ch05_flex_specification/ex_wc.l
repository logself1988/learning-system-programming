/* just like UNIX wc */
%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%
%{
  printf("start lexing\n");  
%}

[0-9]+       |
[a-zA-Z]+    { words++; chars += strlen(yytext); }
\n           { chars++; lines++; }

%%

int main(int argc, char **argv)
{
  yylex();
  printf("%8d%8d%8d\n", lines, words, chars);
}
