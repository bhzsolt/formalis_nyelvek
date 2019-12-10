%{
	extern int yylex();
	extern int yyerror(const char *);

	extern int line_count;
	extern int column_count;

%}

%define parse.error verbose

%token CONSTANT
%token IDENTIFIER
%token STRING_LITERAL
%token INTEGER REAL COMPLEX STRING
%token ADD SUB MUL DIV MOD ASSIGN EQ NEQ AND OR G L GE LE NOT
%token PROGRAM FOR WHILE IF ELSE
%token READ WRITE

%%

s
	: PROGRAM IDENTIFIER block
	| error PROGRAM IDENTIFIER block
	| PROGRAM error IDENTIFIER block
	| error block
	;

block 
	: '{' '}'
	| '{' lines '}'
	;

atom 
	: line ';'
	| line error
	| loop
	| decision
	;

lines 
	: atom
	| lines atom
	;

line
	: expression
	| declaration
	| write
	| read
	;

write 
	: WRITE '(' IDENTIFIER ')'
	| WRITE '(' STRING_LITERAL ')'
	| WRITE '(' STRING_LITERAL ',' expression ')'
	;

read 
	: READ '(' IDENTIFIER ')'
	;

declaration
	: type expression
	;

type 
	: INTEGER
	| REAL
	| COMPLEX
	| STRING
	;

identifier 
	: IDENTIFIER
	| IDENTIFIER '[' ']'
	| IDENTIFIER '[' expression ']'
	;

primary 
	: '(' expression ')'
	| identifier
	| CONSTANT
	| STRING_LITERAL
	;

unary_op 
	: ADD
	| SUB
	| NOT
	;

unary 
	: primary
	| unary_op primary
	| unary_op error primary
	;

multiplicative
	: unary 
	| multiplicative MUL unary
	| multiplicative DIV unary
	| multiplicative MOD unary
	;

additive
	: multiplicative
	| additive ADD multiplicative
	| additive SUB multiplicative
	;

relational
	: additive
	| additive L additive
	| additive G additive
	| additive LE additive
	| additive GE additive
	;

equality
	: relational
	| relational EQ relational
	| relational NEQ relational
	;

and 
	: equality
	| and AND equality
	;

or
	: and
	| or OR and
	;

type_conversion
	: or
	| '(' type ')' type_conversion
	;

assignment 
	: type_conversion
	| identifier ASSIGN assignment
	;

expression 
	: assignment
	| expression ',' assignment
	;

loop
	: for
	| while
	;
	
decision 
	: if
	;

for 
	: FOR '(' declaration ';' expression ';' expression ')' block
	| FOR '(' expression ';' expression ';' expression ')' block
	;

while 
	: WHILE '(' expression ')' block
	;

if 
	: IF '(' expression ')' block
	| IF '(' expression ')' block ELSE block
	| IF '(' expression ')' block ELSE if
	;

%%
