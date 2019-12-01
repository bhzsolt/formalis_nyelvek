%{
	#include <stdio.h>
	#include <string.h>
	#include "grammar.tab.h"
	int line_count = 0;
	int column_count = 0;

	void count(int);
%}

%option noyywrap

D	[0-9]
L	[a-zA-Z_]

INT		[1-9]{D}*
REAL	{D}+"."{D}+

%%

"/*"[^*]*"*"([^*/][^*]*"*"|"*")*"/" { }

"//".* { count(0); }

\r?\n { count(1); }

0|{INT} 					{ count(0); return CONSTANT; }
"0.0"|{REAL}				{ count(0); return CONSTANT; }
(0|{INT})[+\\-]{INT}i		{ count(0); return CONSTANT; }
("0.0"|{REAL}[+\\-]{REAL}i	{ count(0); return CONSTANT; }

{L}({L}|{D})*				{ count(0); return IDENTIFIER; }

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

