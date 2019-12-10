#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	int n;
	int a = 0;
	int b = 1;

	int 4;

	printf("n = ");
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		int aux = b;
		b = a + b;
		a = aux;
	}

	printf("nth fibonacci number: %d\n", a);

	return 0;
}
