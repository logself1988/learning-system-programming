# Notes of Flex & Bison


|时间|内容|
|:---|:---|
|20210902|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1. Introducing Flex and Bison

Flex example: `ex_wc.l`

```
/* just like UNIX wc */
%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%

[a-zA-Z]+ { words++; chars += strlen(yytext); }
\n        { chars++; lines++; }
.         { chars++; }

%%

int main(int argc, char **argv)
{
  yylex();
  printf("%8d%8d%8d\n", lines, words, chars);
}
```

- `%%`: flex程序由三部分构成, 按`%%`分隔;
- 声明段中的`%{%}`中代码, 会直接拷贝到生成的C代码中(例如`lex.yy.c`);
- 模式段中以模式开启一行, 动作(action)`{}`中包含C代码(单个语句或语句块);
- `yytext`: 指向匹配模式的输入文本的变量;
- `yylex()`: 由flex提供给扫描器程序的函数. 如果在动作中使用了`return`, 扫描在下一次调用`yylex()`时恢复; 如果没有使用`return`, 扫描立即恢复;
- `yylval`: flex扫描器返回token的流, token有编号(`enum yytokentype`)和值(`yylval`).

BNF(Backus-Naur Form)是编写CFG(Context-Free Grammar)的标准形式, 例:

```
<exp>    ::= <factor>
         | <exp> + <factor>
<factor> ::= NUMBER
         | <factor> * NUMBER
```

Bison example: `ex_calc.y`, `ex_calc.l`

```
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
```

```
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
```

### 2. Using Flex

Flex's regular expression language:

- `.`: 匹配除换行符`\n`之外的任一字符;
- `[]`: 字符类, 例如`[0123456789]`、`[0-9]`、`[a-z]`;
- `[a-z]{-}[jv]`: 字符类的差集;
- `^`: 匹配行首;
- `$`: 匹配行尾;
- `{}`: 包含一个或两个数字时, 表示其之前的模式出现的最小和最大次数, 例如`A{1,3}`、`0{5}`; 包含名称时表示引用命名的模式;
- `\`: 用于转义字符, 例如`\n`、`\*`;
- `*`: 匹配其之前的正则表达式的零次或多次出现, 例如`[ \t]*`;
- `+`: 匹配其之前的正则表达式的一次或多次出现, 例如`[0-9]+`;
- `?`: 匹配其之前的正则表达式的零次或一次出现, 例如`-?[0-9]+`;
- `|`: 备选操作符, 例如`faith|hope|charity`;
- `"..."`: 字面量匹配`""`中的内容;
- `()`: 将一组正则表达式组装成一个新的正则表达式, 例如`(01)`、`a(bc|de)`;
- `/`: 后继上下文(trailing context), 只在匹配`/`之后的正则表达式时匹配`/`之前的正则表达式, 例如`0/1`在`01`中匹配`0`, 但不会在`0`或`02`中获得匹配.

Example: Fortran-style numbers

```
.12, 12, 12., .12E2

[-+]? ([0-9]*\.?[0-9]+ | [0-9]+\.) (E(+|-)?[0-9]+)?
```

处理规则间歧义的方式:

- 每次扫描器匹配输入时匹配最长的可能字符串;
- 仍存在歧义时, 选择在程序中首先出现的规则.

```
"+"                     { return ADD; }
"="                     { return ASSIGN; }
"+="                    { return ASSIGNADD; }

"if"                    { return KEYWORDIF; }
"else"                  { return KEYWORDELSE; }
[a-zA-Z_][a-zA-Z0-9_]*  { return IDENTIFIER; }
```

Flex扫描器中的文件I/O:

- `yyin`: 除非有其他安排, 扫描器从`FILE yyin`中读取内容, 默认为`stdin`; 需要读取文件时, 在首次调用`yylex()`之前设置`yyin`.
- `%option noyywrap`: 当扫描器达到`yyin`的尾部时, 会调用`yywrap()`以调整`yyin`并恢复扫描; `noyywrap`关闭这一特性.
- `yyrestart(f)`: 告知扫描器读取文件`f`, `YY_NEW_FILE`等价于`yyrestart(yyin)`.
- 输入: 三层输入系统. <br/>
(1) 设置`yyin`为所需读取的文件;<br/>
(2) 创建和使用`YY_BUFFER_STATE`输入缓冲区: `YY_BUFFER_STATE bp = yy_create_buffer(yyin, YY_BUF_SIZE)`, `yy_switch_to_buffer(bp);`<br/>
(3) 重定义`YY_INPUT`: `#define YY_INPUT(buf, result, max_size) ...`.
- 输出: 动作代码中可以使用宏`input()`和`unput()`, 分别是返回输入流中的下一个字符、将字符放回到输入流中.
- `%option nodefault`: 关闭无匹配模式时的`ECHO`特性(`#define ECHO fwrite(yytext, yyleng, 1, yyout)`).
- `yyterminate()`: 立即从扫描器返回.

开始状态(start states):

- `%x IFILE`: 标记`IFILE`为独占的(exclusive)开始状态, 独占的含义是当状态活跃时, 只有标记了该状态的模式可以用于匹配. `%s`表示包含的(inclusive)开始状态.

### 3. Using Bison

Flex将输入流拆分为token, Bison将这些token逻辑的组织在一起.

Bison只处理文法(grammar), 文法规则例:

```
statement: NAME '=' expression
expression: NUMBER '+' NUMBER
          | NUMBER '-' NUMBER
```

- LHS: `:`左边; RHS: `:`右边.
- 几个规则可以有相同的LHS.
- 由lexer返回的符号是终结符号(terminal symbols)或tokens; 出现在LHS中的符号是非终结符号(nonterminal symbols). 终结符号与非终结符号必须是不同的.

移进/规约(shift/reduce)解析:

- Bison处理解析时, 创建一组状态(state), 每个状态反映了一个或多个部分解析的规则中的可能位置.
- 当解析器每次读到一个没有完成规则的token时, 将该token压入内部栈中, 并切换到一个反映读取了该token的新状态; 这个动作称为 **移进**.
- 当解析器发现所有的符号构成一条规则的RHS, 将这些符号从栈中弹出, 将规则的LHS符号压入栈中, 并切换到一个反映该新符号在栈中的新状态; 这个动作称为 **规约**.
- 每当Bison规则一条规则时, 会执行与该规则关联的用户代码. 对于没有显式动态代码的规则, 有默认动作`$$ = $1;`.

Bison使用两种解析方法:

- LALR(1): Look Ahead Left to Right with a one-token lookahead;
- GLR: Generalized Left to Right.

LALR(1)不能处理存在歧义的文法(ambiguous grammars), 在该文法中相同的输入可以匹配多个规则; <br/>也无法处理需要预读多个token的文法, 例:

```
# 该文法处理输入HORSE AND CART时, 需要预读2个token来消歧.
phrase: cart_animal AND CART
      | work_animal AND PLOW
cart_animal: HORSE | GOAT
work_animal: HORSE | OX
```

Bison的规格描述由三部分构成:

- (1) 定义段: 处理解析器的控制信息, 设置解析器操作的执行环境;
- (2) 规则段: 包含解析器的规则;
- (3) 代码段: 直接拷贝入生成的C程序中的C代码.

AST(Abstrace syntax tree): 抽象语法树, 移除了无存在意义节点的解析树.


```
%union {
  struct ast *a;
  double d;
}

%token <d> NUMBER
%token EOL
%type <a> exp factor term
```

- `%union`: 默认情况下, Bison解析器中的每个符号(包括token和非终结符)有一个关联的整数值. `%union`构造(construct)用于创建符号值的C语言`union`声明. 在词法中可以使用`yylval.d`引用符号值.
- `<d>`、`<a>`告知Bison特定符号的类型; `%type`将`<a>`赋值给`exp`、`factor`和`term`.

```
exp: factor
   | exp '+' factor { $$ = newast('+', $1, $3); }
   | exp '-' factor { $$ = newast('-', $1, $3); }
   ;
```

- 规则中可以使用字面量的token, 例如这里的`+`和`-`.

移进/规约冲突(conflicts)与操作符优先级(operator precedence):

```
# 处理如下输入时有冲突
# 2 + 3 * 4
# 3 - 4 - 5 - 6

exp: exp '+' exp
  | exp '-' exp
  | exp '*' exp
  | exp '/' exp
  | '|' exp
  | '(' exp ')'
  | '-' exp
  | NUMBER
  ;
```

- 优先级(precedence): 控制表达式中哪个操作符首先执行; 例`a+b*c`意义为`a+(b*c)`;
- 结合性(associativity): 控制同一优先级下操作符的分组; 例C语言中`a-b-c`意义为`(a-b)-c`, `a=b=c`意义为`a=(b=c)`.

在文法中指定优先级和结合性的两种方式:

- 隐式的: 对每个优先级使用不同的非终结符号;
- 显式的: 依赖定义顺序和`%left`、`%nonassoc`, 例:

```
# 从上往下, 优先级从低到高
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

exp: exp '+' exp
  | exp '-' exp
  | exp '*' exp
  | exp '/' exp
  | '|' exp
  | '(' exp ')'
  | '-' exp %prec UMINUS
  | NUMBER
  ;
```

- Bison将RHS中最右边token的优先级赋值给规则, 如果该token没有赋予优先级则该规则也没有优先级;
- 当遇到移进/规约冲突时, 咨询优先级表, 如果存在冲突的所有规则均被赋予了优先级, 则使用优先级解决冲突.
- `%prec UMINUS`告知Bison该规则使用`UMINUS`的优先级.
- 优先级规则适用于: (1) 表达式文法; (2) if/then/else语言构造文法中悬挂的else冲突.
- 规则段中`%start`声明指出顶级规则.

基本的解析器错误恢复:

```
calclist: /* nothing */
        | calclist stmt EOL                               
          { printf("= %4.4g\n> ", eval($2)); treefree($2); }
        | calclist LET NAME '(' symlist ')' '=' list EOL  
          { dodef($3, $5, $8); printf("Defined %s\n> ", $3->name); }
        | calclist error EOL                              
          { yyerrok; printf("> "); }
        ;
```

- `error`: 特殊的伪token指示出错误恢复点;
- 当Bison解析器遇到错误时, 开始从解析器栈中丢弃符号, 直到到达token `error`有效的点; <br/>然后丢弃输入token, 直到找到一个在当前状态可以移进的token, 并从这里继续解析; <br/> 如果解析器再次失败, 它会丢弃更多的栈符号和输入token, 直到可以恢复解析或栈为空(此时解析失败).
- 为避免大量的错误消息, 解析器通常在首次出现错误后抑制错误消息, 直到成功移进了一行中的三个token.
- 宏`yyerrok`: 在动作中告知解析器恢复已完成, 后续的错误消息将会生成.

### 4. Parsing SQL

> skip

### 5. A Reference for Flex Specifications

见[5. A Reference for Flex Specifications](./flex_spec.md)

### 6. A Reference for Bison Specifications

见[6. A Reference for Bison Specifications](./bison_spec.md)

### 7. Ambiguities and Conflicts

### 8. Error Reporting and Recovery

### 9. Advanced Flex and Bison

### Appendix: SQL Parser Grammar and Cross-Reference

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- John R. Levine. **flex & bison**. O'Reilly Media, 2009.

## 其他备注

- Dick Grune. **Parsing Techniques: A Pratical Guide**.
