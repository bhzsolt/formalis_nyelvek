%{
	#include "grammar.tab.h"
	int line_count = 1;
	int column_count = 0;

	void count(int);
	void comment();

	extern int yyerror(const char *);
%}

%option noyywrap

D	[0-9]
L	[a-zA-Z_]

INT		[1-9]{D}*
REAL	{D}+"."{D}+

%%

"/*"						{ //"/*"[^*]*"*"([^*/][^*]*"*"|"*")*"/"  
							comment(); }

"//".* 						{ count(0); }
\r?\n 						{ count(1); }
[ \t] 						{ count(0); }

0|{INT} 					{ count(0); return CONSTANT; }
"0.0"|{REAL}				{ count(0); return CONSTANT; }
(0|{INT})[+\\-]{INT}i		{ count(0); return CONSTANT; }
("0.0"|{REAL})[+\\-]{REAL}i	{ count(0); return CONSTANT; }

\"[^"\n]*\"					{ count(0); return STRING_LITERAL; }

"integer"					{ count(0); return INTEGER; }
"real"						{ count(0); return REAL; }
"complex"					{ count(0); return COMPLEX; }
"string"					{ count(0); return STRING; }
"program"					{ count(0); return PROGRAM; }
"for"						{ count(0); return FOR; }
"while"						{ count(0); return WHILE; }
"if"						{ count(0); return IF; }
"else"						{ count(0); return ELSE; }
"read"						{ count(0); return READ; }
"write"						{ count(0); return WRITE; }

"+"							{ count(0); return ADD; }
"-"							{ count(0); return SUB; }
"*"							{ count(0); return MUL; }
"/"							{ count(0); return DIV; }
"%"							{ count(0); return MOD; }
"="							{ count(0); return ASSIGN; }
"=="						{ count(0); return EQ; }
"!="						{ count(0); return NEQ; }
"&&"						{ count(0); return AND; }
"||"						{ count(0); return OR; }
">"							{ count(0); return G; }
"<" 						{ count(0); return L; }
">="						{ count(0); return GE; }
"<="						{ count(0); return LE; }
"["							{ count(0); return '['; }
"]"							{ count(0); return ']'; }
"!"							{ count(0); return NOT; }

{L}({L}|{D})*				{ count(0); return IDENTIFIER; }

[(){};,]					{ count(0); return yytext[0]; }

.							{ count(0); yyerror("Lexical error."); } 

%%

void count(int line_break)
{
	if (line_break) {
		++line_count;
		column_count = 0;
		return;
	}
	column_count += strlen(yytext);
}

void comment() 
{
	char prev, c;
	prev = ' ';
	while ((c = input()) != 0) {
		if (c == '/') {
			if (prev == '*') {
				return;
			}
			count(0);
		}
		if (c == '\n') {
			count(1);
		}
		prev = c;
	}
}

