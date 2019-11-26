%{
	#include <stdio.h>
	
	extern int yylex();
	int yyerror(const char *);

%}

%union {
	int 	integer;
	double	real;
	char   *string;
	int	   *i_array;
	double *d_array;
	char	boolean;
	char   *id;
}

%error-verbose

%left '+' '-'
%left '*' '/' '%'
%right '='

%left "&&" "||"
%nonassoc "==" "!="

%token<integer> INTEGER
%token<real>	REAL
%token<string>	STRING
%token<i_array>	INT_ARRAY
%token<d_array> DOUBLE_ARRAY
%token<boolean>	BOOLEAN
%token<id>		ID

%%

line : expr ';'
	 | block
;

expr : INTEGER
;

block : '{' REAL '}'
;

%%

int main(int argc, const char *argv[]) {
	if (!yyparse()) {
		return 1;
	}
	return 0;
}

int yyerror(const char *string) {
	printf("%s\n", string);
	return 0;
}
