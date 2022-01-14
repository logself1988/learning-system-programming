grammar Calculator;

calculation: statement | 'q' | calculation statement;

statement: declaration ';' | expression ';';

declaration: 'let' NAME '=' expression;

//expression: term | term '+' expression | term '-' expression;
expression: term | expression '+' term | expression '-' term;

term:
	primary
	| primary '*' term
	| primary '/' term
	| primary '%' term;

primary:
	NUMBER
	| NAME
	| '(' expression ')'
	| '-' primary
	| '+' primary;

SPACE: [ \t\r\n]+ -> channel(HIDDEN);
NUMBER: (DEC_DIGIT+)? '.'? DEC_DIGIT+;
NAME: [a-zA-Z_][0-9a-zA-Z_]*;

fragment DEC_DIGIT: [0-9];