# 5. A Reference for Flex Specifications

## 5.1 程序结构

Flex程序由三部分构成:

```
<definition section>
%%
<rules section>
%%
<user subroutines>
```

## 5.2 定义部分

- 包含: 选项(option)、字面量块(literal block)、定义(definition)、开始条件(start condition)和翻译(translation).
- 以空白符开始的行被拷贝到C文件中.

## 5.3 规则部分

- 包含: 模式行(pattern line)和C代码.
- 以空白符开始的行、被包裹在`%{`和`%}`中的内容是被拷贝到`yylex()`中的C代码.
- 规则部分开始处的C代码将出现在`yylex()`的开始处, 可以包含在扫描器中使用的变量声明和每次`yylex()`被调用时执行的代码; 其他位置的C代码行只应该包含注释.
- 以其他内容开始的行是模式行: 一个模式, 后接一些空白符和当输入匹配模式时执行的C代码. 如果C代码有多个语句或跨多行, 必须包裹在`{}`或`%{%}`中.

扫描器运行时, 将输入与规则中模式匹配:

- 每次找到匹配时, 执行与该模式匹配的C代码; 被匹配的输入称为token;
- 如果模式后接`|`而不是C代码, 则执行文件中下一个规则关联的C代码;
- 当输入字符不匹配任何模式, 则调用宏`ECHO`打印token到输出.

## 5.4 用户例程

该部分内容被拷贝到C文件:

- 规则中调用的例程;
- 重定义`yywrap()`时的支持例程等.

## 5.5 Features

### (1) `BEGIN`

`BEGIN`宏切换开始状态(start states), 通常在模式的动作代码中调用, 例:

```
BEGIN statename;
```

扫描器从状态0(`INITIAL`)开始, 其他状态必须在定义部分的`%s`或`%x`行中命名.

### (2) Context sensitivity

提供了一些方法处理模式与左右上下文敏感的情况.

(a) 左上下文

三种方式:

- 特殊的行开始模式字符`^`.
- 使用开始状态

token `second`在`first`后被识别:

```
%s MYSTATE
%%
first             { BEGIN MYSTATE; }
<MYSTATE>second   { BEGIN 0; }
```

- 使用显式的代码

通过设置标记来在模式动作代码间传递上下文信息:

```
%{
  int flag = 0;
%}
%%
a   { flag = 1; }
b   { flag = 2; }
zzz {
      switch(flag) {
        case 1: a_zzz_token(); break;
        case 2: b_zzz_token(); break;
        default: plain_zzz_token(); break;
      }
      flag = 0;
    }
```

(b) 右上下文

三种方式:

- 特殊的行结束模式字符`$`.
- 使用操作符`/`

模式中使用`/`字符可以包含显式的后继上下文. 例如, 只在`abc`立即后继`de`时匹配token`abc`:

```
abc/de
```

`/`本身不匹配任何字符.

在确定哪个模式有最长匹配时, 会考虑后继上下文字符; 但这些字符不会出现在`yytext`中, 也不会计入`yyleng`.

- 使用`yyless()`

`yyless()`函数告知扫描器放回(push back)刚读取到的token的一部分, 其参数是token中保留的字符的数量.

与`abc/de`效果相同, 但被放回的字符会出现在`yytext`中, 也计入`yyleng`中.

```
abcde   { yyless(3); }
```

### (3) Definitions/Subsitutions

定义或置换允许给正则表达式命名, 并在规则部分中通过该名称引用. 名称`NAME`可以包含字母、数字、`-`和`_`, 但不能以数字开始.

```
NAME expression
```

在规则部分中通过`{NAME}`引用:

```
DIG       [0-9]
%%
{DIG}+              { process_integer(); }
{DIG}+\.{DIG}*      |
\.{DIG}+            { process_real(); }
```

### (4) `ECHO`

在模式关联的C代码中, 宏`ECHO`将token写入当前输出文件`yyout`, 等价于`fprintf(yyout, "%s", yytext)`.

在flex中, 输入文本不匹配任何模式的默认动作是将该文本输出, 等价于`ECHO`. 而`%option nodefault`或命令行中`-s`或`--nodefault`标记, 将默认动作改为中止(abort).

### (5) Input Management

在程序开始的地方, 可以赋值`yyin`任何打开的stdio文件, 让扫描器从该文件读取.

(5.1) stdio文件链

通过调用`yyrestart(file)`告知词法器从任意stdio文件`file`读取.

当使用`%option yywrap`构建的词法器达到输入文件的末尾时, 会调用`yywrap()`, 切换到一个不同的输入文件.

(5.2) 输入缓冲

Flex扫描器从输入缓冲中读取输入. 输入缓冲可以与stdio文件关联, 也可以与内存中字符串关联.

`YY_BUFFER_STATE`是指向flex输入缓冲的指针:

``` c
YY_BUFFER_STATE bp;
FILE *f;

f = fopen(..., "r");
bp = yy_create_buffer(f, YY_BUF_SIZE);  // new buffer reading from f

// YY_CURRENT_BUFFER: current buffer
yy_switch_to_buffer(bp);                // use the buffer we just made
...
yy_flush_buffer(bp);                    // discard buffer contents
...
void yy_delete_buffer(bp);              // free buffer
```

(5.3) 字符串输入

``` c
// scan a copy of bytes
bp = yy_scan_bytes(char *bytes, len);            

// scan a copy of null-terminated string
bp = yy_scan_string("string");          

// scan (size-2) bytes in place
bp = yy_scan_buffer(char *base, yy_size_t size);  
```

(5.4) 文件嵌套

管理输入缓冲的栈:

``` c
void yypush_buffer_state(bp); // switch to bp, stack old buffer
void yypop_buffer_state();    // delete current buffer, return to previous
```

帮助维护输入栈的特殊token模式`<<EOF>>`, 在调用`yywrap()`之后匹配文件结尾.

(5.5) `input()`

概念上, `input()`给词法器提供字符.

例: 处理C注释

```
"/*"  {
        int c1 = 0, c2 = input();
        for(;;) {
          if (c2 == EOF) break;
          if (c1 == '*' && c2 == '/') break;
          c1 = c2;
          c2 = input();
        }
      }
```

(5.6) `YY_INPUT`

Flex使用宏`YY_INPUT(buf, result, max_size)`读取输入到缓冲中.

重定义`YY_INPUT`的场景有读取不是字符串或stdio文件的输入源.

### (6) Flex Library

在`cc`命令行中使用`-lfl`链接flex库. 库中包含了`main()`和`yywrap()`:

``` c
main(int ac, char **av)
{
  return yylex();
}

int yywrap() { return 1; }
```

### (7) Interactive and Batch Scanners

Flex扫描器有时需要在输入中前瞻一个字符以确定当前token是否已完成.

- 批模式: 总是前瞻, `%option batch`;
- 交互模式: 只在需要时前瞻, `%option interactive`.

### (8) Line Numbers and `yylineno`

如果设置了`%option yylineno`, flex定义包含当前行号的`yylineno`.

词法器并不初始化`yylineno`, 所以需要在开始读取文件时将其赋值为1.

### (9) Literal Block

定义部分的字面量块是由`%{`和`%}`包裹的C代码.

```
%{
  <C code and declarations>
%}
```

每个字面量块的内容被拷贝到生成的C文件中. 定义部分的字面量块中C代码放置在`yylex()`之前.

字面量块通常包含用于规则部分的变量和函数声明, 以及`#include`行.

以`%top{`开始的字面量块中C代码被拷贝到生成文件的顶部, 通常用于`#include`文件或设置`YY_BUF_SIZE`的`#define`行.

规则部分的字面量块:

- 在规则部分开始处的字面量块中C代码被拷贝到`yylex()`中的在局部变量声明之后的顶部, 故可以包含更多的声明和设置代码.
- 规则部分中其他位置的字面量块只能包含注释.

### (10) Multiple Lexers in One Program

处理一个程序中两个词法器的两个基本方法:

(1) 组合词法器

使用开始状态组合两个词法器, 每个词法器的模式有单独的开始状态. 需要在词法器开始前将其设置为恰当的初始状态, 例如设置`first_lex`为初始状态:


```
%s INITA INITB INITC
%%
%{
  extern first_tok, first_lex;

  if (first_lex) {
    BEGIN first_lex;
    first_lex =0;
  }
  if (first_tok) {
    int holdtok = first_tok;
    first_tok = 0;
    return holdtok;
  }
%}
```

(2) 在一个程序中放置两个完整的词法器

需要修改两个词法器使用的函数和变量名称, 以便可以编译到一个程序中.

使用前缀`foo`而不是`yy`, 将生成的扫描器放到`foolex.c`中:

```
%option prefix=foo
%option outfile="foolex.c"
```

使用命令行选项:

```
$ flex --outfile=foolex.c --prefix=foo foo.l
```

这样, 生成的词法器有入口点`foolex()`, 从stdio文件`fooin`读取等.

### (11) Options when Building a Scanner

Flex提供了构建扫描器的选项:

```
%option <name>
--<name>

// 关闭选项
%option no<name>  // 例: %option noyywrap
--no<name>        // 例: --noyywrap
```

### (12) Portability of Flex Lexers

Flex词法器的可移植性体现在两个层次: 原始的flex规范、生成的C源文件.

移植生成的C词法器:

- 确保使用`%option noyywrap`或使用自己的`yywrap()`版本以避免使用flex库.
- 默认的两个输入缓冲均是16K, 在定义部分中调整大小:

```
%{
#define YY_BUF_SIZE 4096
%}
```

- 如果词法器使用`REJECT`, 会分配后备状态缓冲, 大小为`YY_BUF_SIZE`的4倍(64位机器上为8倍).
- 生成的C代码使用字符编码作为词法器中表的索引. 如果源和目标机器使用不同的字符集, 词法器将不工作.

### (13) Reentrant Scanners

通常flex扫描器将状态信息放在静态变量中, 每次调用`yylex()`会使用前一次调用的状态信息, 包括已有的输入缓冲、输入文件、开始状态等. Flex提供了`%option reentrant`和`--reentrant`, 支持多个扫描器副本同时存在.

在可重入扫描器中:

- 所有扫描状态信息存放在`yyscan_t`变量中, 它通常指向状态结构体.
- 调用`yylex_init()`时传入`yyscan_t`创建独立的扫描器, 返回0表示成功.
- 调用`yylex()`时传入`yyscan_t`.
- 使用`yylex_destroy()`销毁`yyscan_t`.

``` c
yyscan_t scanner;

if (yylex_init(&sanner)) {
  printf("no scanning\n");
  abort();
}
while(yylex(scanner)) {
  // do something
}
yylex_destroy(scanner);
```

在可重入扫描器中:

- 一些在`yylex`中使用的变量被重定义为宏, 可以像在常规扫描器中一样使用: `yyin`、`yyout`、`yyextra`、`yyleng`、`yytext`、`yylineno`、`yycolumn`、`yy_flex_debug`;
- 也被修改可以使用的宏和函数: `BEGIN`、`YY_START`、`YYSTATE`、`yymore()`、`unput()`、、`yyless()`;
- 创建和处理输入缓冲的例程接受`yyscan_t`参数: `yyrestart()`、`yy_switch_to_buffer`、`yy_create_buffer`、`yy_delete_buffer`、`yy_flush_buffer`、`yypush_buffer_state`、`yypop_buffer_state`、`yy_scan_buffer`、`yy_scan_string`、`yy_scan_bytes`.


可重入扫描器中的额外数据:

- 使用`yylex_init_extra`并传入自定义的每扫描器数据指针, 在`yylex()`中使用`yyextra`访问该数据指针.
- 额外数据的类型是`YY_EXTRA_TYPE`, 通常是`void *`, 但可以使用`#define`重定义为具体类型:

``` c
yyscan_t scanner;
symbol *symp;       // 额外数据为符号表

symp = symtabinit();

if (yylex_init_extra(symp, &scanner) {
  printf("no scanning\n");
  abort();
}
while(yylex(scanner)) {
  // do something
}
yylex_destroy(scanner);

// 在yylex中
[a-z]+  { symlookup(yyextra, yylval); }
```
- 在常规扫描器中, `yylex()`外部的代码可以直接访问`yyin`、`yyout`等全局变量, 在可重入扫描器中访问和设置这里变量的例程有:

``` c
YY_EXTRA_TYPE yyget_extra (yyscan_t yyscanner );                      // yyextra
void yyset_extra (YY_EXTRA_TYPE user_defined ,yyscan_t yyscanner );

FILE *yyget_in (yyscan_t yyscanner );                                 // yyin
void yyset_in (FILE * in_str ,yyscan_t yyscanner );

FILE *yyget_out (yyscan_t yyscanner );                                // yyout
void yyset_out (FILE * out_str ,yyscan_t yyscanner );

int yyget_lineno (yyscan_t yyscanner );
void yyset_lineno (int line_number ,yyscan_t yyscanner );

int yyget_leng(yyscan_t yyscanner);                                   // yyleng, read only

char *yyget_text(yyscan_t yyscanner);                                 // yytext
```

可重入扫描器、嵌套文件、多个扫描器:

- 可重入扫描器允许有多个同时活跃的实例, 将同一组模式应用到不同的输入源上;
- 嵌套文件(使用`yy_switch_to_buffer`和相关例程)允许单个扫描器读取一个文件, 再读取另一个文件;
- 多个扫描器允许将不同的模式集合应用到不同的输入源上.

组合使用:

- 在可重入扫描器中调用`yy_switch_to_buffer`改变特定实例的输入源;
- 使用`%option reentrant prefix="foo"`创建可被多次调用的扫描器、可与其他可重入或不可重入的扫描器链接入同一个程序中.


Bison有创建可重入解析器`pure-parser`的选项, 通常`pure-parser`通过向`yylex`传入放置token值的指针来获取token, 而不是使用flex需要的`yyscan_t`.

Flex提供了`%option reentrant bison-bridge`, 修改了`yylex`声明, 并自动设置`yylval`指针:

``` c
int yylex(YYSTYPE * yylval_param, yyscan_t yyscanner);
```

### (14) Regular Expression Syntax

正则表达式由表示自身的常规字符、具有特殊模式含义的元字符构成.

元字符:

- `.`: 匹配除换行符`\n`之外的任一字符;
- `[]`: 字符类, 例如`[0123456789]`、`[0-9]`、`[a-z]`;
- `[a-z]{-}[jv]` [a-f]{+}[0-9]: 字符类的差集和并集;
- `*`: 匹配其之前的正则表达式的零次或多次出现, 例如`[ \t]*`;
- `+`: 匹配其之前的正则表达式的一次或多次出现, 例如`[0-9]+`;
- `?`: 匹配其之前的正则表达式的零次或一次出现, 例如`-?[0-9]+`;
- `{}`: 包含一个或两个数字时, 表示其之前的模式出现的最小和最大次数, 例如`A{1,3}`、`0{5}`; 包含名称时表示引用命名的模式;
- `\`: 用于转义字符, 例如`\n`、`\*`;
- `()`: 将一组正则表达式组装成一个新的正则表达式, 例如`(01)`、`a(bc|de)`;
- `|`: 备选操作符, 例如`faith|hope|charity`;
- `"..."`: 字面量匹配`""`中的内容;
- `/`: 后继上下文(trailing context), 只在匹配`/`之后的正则表达式时匹配`/`之前的正则表达式, 例如`0/1`在`01`中匹配`0`, 但不会在`0`或`02`中获得匹配; 一个模式中只允许出现一个`/`, 模式不能同时包含`/`和`$`;
- `^`: 匹配行首;
- `$`: 匹配行尾;
- `<>`: 模式开始处的尖括号中一个或多个名字, 标记模式只在这些开始状态下应用;
- `<<EOF>>`: 匹配文件末尾;
- `(?# comment)`: Perl风格的表达式注释;
- `(?a:pattern)` `(?a-x:pattern)`: Perl风格的模式修饰符. 使用修饰符`a`但不是用修饰符`x`解释模式. `i`大小写不敏感, `s`匹配单行(使用`.`匹配`\n`字符), `x`忽略空白符和C风格注释

```
(?i:xyz)                  [Xx][Yy][Zz]
(?i:x(?-i:y)z)            [Xx]y[Zz]
(?s:a.b)                  a(.|\n)b
(?x:a /* hi */ b)         ab
```

Flex也支持一组POSIX字符集:

```
[:alnum:] [:alpha:] [:blank:] [:cntrl:] [:digit:] [:graph:]
[:lower:] [:print:] [:punct:] [:space:] [:upper:] [:xdigit:]
```

`[[:digit:]]`等价于`[0123456789]`, `[x[:xdigit:]]`等价于`[x0123456789AaBbCcDdEeFf]`.

### (15) `REJECT`

通常lex将输入拆分为不重叠的token, 特殊的动作`REJECT`帮助处理存在重叠的token.

执行`REJECT`动作时, flex将匹配模式的文本放回(put back), 并查找下一个最佳匹配.

例: 找出文件中出现的单词pink、pin和ink

```
%%
pink  { npink++; REJECT; }
ink   { nink++; REJECT; }
pin   { npin++; REJECT; }
. |
\n    { /*discard other characters */ }
%%
```

使用`REJECT`的扫描器通常较大且较慢.

### (16) Returing Values from `yylex()`

模式匹配token时执行的动作C代码中可以包含返回语句, 从`yylex()`返回值到其调用者(通常是yacc生成的解析器). 下次`yylex()`被调用时, 扫描器继续执行.

当扫描器匹配到解析器感兴趣的token(关键字、变量名、操作符)时, 它返回并将该token传递给解析器; 当匹配到解析器不感兴趣的token时, 它不返回, 立即尝试匹配下一个token.

这意味着不能仅调用`yylex()`来重启词法器, 而是使用`BEGIN INITIAL`将其重置为默认状态, 并充值输入状态使得下次调用`input()`时会开始读到新的输入. 调用`yyrestart(file)`(`file`是stdio文件), 将开始从该文件读取内容.

### (17) Start States

在定义部分可以声明开始状态(start states):

- 开始状态用于限制特定规则的作用域, 或改变词法器处理文件特定部分的方式;
- 有两个版本: 包含声明的`%s`、独有声明的`%x`. 两者的区别是在包含状态中, 没有开始状态的规则也适用; 在独有状态中则不适用.

例: C预处理器指令`#include <somefile.h>`

```
%s INCLMODE
%%
^"#include"               { BEGIN INCLMODE; }
<INCLMODE>"<" [^>\n]+">"  { /* handle name */ }
<INCLMODE>\n              { BEGIN INITIAL; /* return to normal */ }
```

当前状态`YY_START`或`YYSTATE`:

```
%s A B C X
<A,B,C>start  { save = YY_START; BEGIN X; }
<X>end        { BEGIN save; }
```

例: 识别C注释

```
%x COMMENT
%%
"/*"          { BEGIN COMMENT; /* switch to comment mode */ }
<COMMENT>.    |
<COMMENT>\n   { /* throw awya comment text */ }
<COMMENT>"*/" { BEGIN INITIAL; /* return to regular mode */ }
```

### (18) `unput()`

宏`unput(c)`将字符`c`放回输入流. 能够放回字符数量至少是词法器能够识别的最长token长度.

例: 展开宏

``` c
// 在动作代码中
char *p = macro_contents();
char *q = p + strlen(p);
while (q > p)
  unput(*--q);  /* push back right-to-left */
```

### (19) `yyinput()` `yyunput()`

- C `input()`, C++ `yyinput()`.
- C `unput()`, C++ `yyunput()`.

### (20) `yyleng`

每当扫描器匹配到token时, token的文本存储到以`\0`结尾的字符串`yytext`, 其长度是`yyleng` (`yyleng == strlen(yytext)`).

### (21) `yyless()`

在规则关联的动作代码中调用`yyless(n)`将匹配到的token的除首`n`个字符外的字符放回输入流.

在不方便使用正则表达式确定token边界时这一特性很有用.

例: 匹配引号包裹的字符串, 可以带`\"`

```
\" [^"]*\"  { /* is the char before close quote a \ ? */
              if (yytext[yyleng-2] == '\\') {
                yyless(yyleng-1); // 将"放回
                yymore();         // 追加下一个token
              } else {
                /* process string */
              }
            }
```

通常`yyless()`比多次调用`unput()`高效些.

另一种使用`yyless()`的场景是使用规则切换到另一个开始状态:

```
sometoken   { BEGIN OTHER_STATE; yyless(0); }
```

如果新的开始状态没有匹配到优先级比当前规则高的规则中模式, `yyless(0)`将导致无限循环.

### (22) `yylex()` and `YY_DECL`

通常不使用参数调用`yylex`, 它主要通过全局变量与余下的程序交互. 宏`YY_DECL`声明了`yylex`的调用序列, 可以给它添加任何参数:

```
%{
#define YY_DECL int yylex(int *fruitp)
%}
%%
apple|orange { (*fruipt)++; }
```

在可重入解析器或bison桥接解析器中, 也可以重定义`YY_DECL`.

例: 在bison桥接扫描器中

```
#define YY_DECL int yylex(YYSTYPE * yylval_param, yyscan_t yyscanner)
```

### (23) `yymore()`

在规则关联的动作代码中调用`yymore()`, 告知lex将下一个token追加到当前token中.

```
%%
hyper   yymore();
text    printf("Token is %s\n", yytext);
```

输入是`hypertext`时, 输出为`Token is hyptertext`.

使用`yymore()`的主要场景是不方便使用正则表达式定义token边界时.


### (24) `yyrestart()`

调用`yyrestart(f)`设置扫描器从打开的stdio文件中读取输入.

### (25) `yy_scan_string` and `yy_scan_buffer`

设置扫描器从内存中字符串或缓冲中读取输入.

### (26) `YY_USER_ACTION`

这个宏在每个扫描器动作代码之前、`yytext`和`yyleng`设置了之后展开. 通常用于设置bison token的位置.

### (27) `yywrap()`

当词法器遇到文件末尾时, 可选的调用例程`yywrap()`以确定下一步的动作:

- 如果`yywrap()`返回0, 扫描器继续扫描;
- 如果返回1, 扫描器返回零token并报告文件结束.

如果词法器不使用`yywrap()`切换文件, 选项`%option noyywrap()`移除对`yywrap()`的调用. Token `<<EOF>>`通常是处理文件结束情况的更好方式.

Flex库中的`yywrap()`版本总是返回1. 如果需要使用`yywrap()`, 应该替换为自己的`yywrap()`版本. 如果`yywrap()`返回0标识有其他额外输入, 需要首先调整`yyin`指向新的文件(例如使用`fopen()`).
