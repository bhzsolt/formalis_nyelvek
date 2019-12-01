#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	int r, i;
	double rr, ri, d;
	char *string; 

	sscanf(argv[1], "%d%di", &r, &i);
	sscanf(argv[2], "%lf%lfi", &rr, &ri);
	sscanf(argv[3], "%lf", &d);
	sscanf(argv[4], "\"%s\"", string);
    strtok(string, "\""); 

	printf("%d%+di\n", r, i);
	printf("%f%+fi\n", rr, ri);
	printf("%f\n", d);
	printf("%s\n", string);

	return 0;
}
