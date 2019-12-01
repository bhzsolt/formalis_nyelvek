#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE* yyin;
extern FILE* yyout;

extern int yyparse();

extern int yylex();

void yyerror(const char *);

int main(int argc, const char *argv[])
{
	if (argc != 3) {
		printf("usage: %s input output\n", argv[0]);
		return 1;
	}

	yyin = fopen(argv[1], "r");
	if (yyin == NULL) {
		printf("Couldn't open input file!\n");
		return -1;
	}

	yyout = fopen(argv[2], "w");
	if (yyout == NULL) {
		printf("Couldn't open output file!\n");
		return -1;
	}

	if (!yyparse()) {
		return -1;
	}

	fclose(yyin);
	fclose(yyout);
	return 0; 
}

int yyerror(const char *string)
{
	printf("%s\n", string);
	return 0;
}
