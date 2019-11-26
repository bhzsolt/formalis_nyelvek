%{
	#include <stdio.h>
	#include "grammar.tab.h"
	int line_count;
	int column_count;
%}

%option noyywrap

NONZERO	[1-9]
DIGIT	[0-9]
CHAR	[a-zA-Z]

%%

0|-?{NONZERO}{DIGIT}* {
	int number;
	sscanf(yytext, "%d", &number);
	column_count += strlen(yytext);
}

0"."0|-?{NONZERO}{DIGIT}*"."{DIGIT}+ {
	printf("[%d, %d, %d] real: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

break|continue|return|if|else|for|while|switch|case {
	printf("[%d, %d, %d] keyword: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

int|char|double|float|long {
	printf("[%d, %d, %d] type: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

"("|")" {
	printf("[%d, %d, %d] parantheses: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

"["|"]" {
	printf("[%d, %d, %d] array-parantheses: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

"{"|"}" {
	printf("[%d, %d, %d] block: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

";"|","|"\""|"'" {
	printf("[%d, %d, %d] punctuation: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

"+"|"-"|"*"|"/"|"%"|"="|"=="|"!="|"&&"|"||" {
	printf("[%d, %d, %d] operator: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

_?|{CHAR}({CHAR}|_|{DIGIT})* {
	printf("[%d, %d, %d] identifier: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

\"[^\"]+?\" {
	printf("[%d, %d, %d] string: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

[ \t]+ {
	column_count += strlen(yytext);
}

\r?\n {
	column_count = 0;
	line_count++;
}

. {
	printf("[%d, %d, %d] unknown token: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

%%
