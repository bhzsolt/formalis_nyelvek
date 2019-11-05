%{
	#include <stdio.h>
	int line_count;
	int column_count;
%}

NONZERO	[1-9]
DIGIT	[0-9]
CHAR	[a-zA-Z]

%%

0|-?{NONZERO}{DIGIT}* {
	printf("[%d, %d, %d] integer: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

0|-?{NONZERO}{DIGIT}*"."{DIGIT}+{NONZERO} {
	printf("[%d, %d, %d] real: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

return|if|else|function|for|while|switch|case {
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

"{"|"}" {
	printf("[%d, %d, %d] block: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

";"|"," {
	printf("[%d, %d, %d] punctuation: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

"+"|"-"|"*"|"/"|"%"|"="|"=="|"!=" {
	printf("[%d, %d, %d] operator: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

_?{CHAR}+{DIGIT}* {
	printf("[%d, %d, %d] identifier: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

[ \t] {
	column_count += strlen(yytext);
}

\n {
	column_count = 0;
	line_count++;
}

. {
	printf("[%d, %d, %d] else: \t%s\n", line_count, column_count, strlen(yytext), yytext);
	column_count += strlen(yytext);
}

%%

int main(int argc, const char *argv[]) {
	yyin = fopen(argv[1], "r");
	yylex();
}
