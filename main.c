#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE* yyin;
extern FILE* yyout;

extern int yyparse();

extern int yylex();

extern int line_count;
extern int column_count;

int yyerror(const char *);

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		printf("usage: %s input\n", argv[0]);
		return 1;
	}

	yyin = fopen(argv[1], "r");
	if (yyin == NULL) {
		printf("Couldn't open input file!\n");
		return -1;
	}

//	yyout = fopen(argv[2], "w");
//	if (yyout == NULL) {
//		printf("Couldn't open output file!\n");
//		return -1;
//	}

	if (!yyparse()) {
		return -1;
	}

	fclose(yyin);
//	fclose(yyout);
	return 0; 
}

int yyerror(const char *string)
{
	printf("[%d:%d] %s\n", line_count, column_count, string);
	return 0;
}
