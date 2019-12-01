%{
	#include <stdio.h>
	
	extern int yylex();
	extern int yyerror(const char *);

%}

%error-verbose

%left '+' '-'
%left '*' '/' '%'
%right '='

%left "&&" "||"
%nonassoc "==" "!="

%token CONSTANT
%token IDENTIFIER

%%

s
	: PROGRAM '(' IDENTIFIER ')' block
	;




%%
