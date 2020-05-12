#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	printf("1\n");
	int n = 5;
	int q = 100000;
	printf("%d %d\n", n, q);
	int* nodes = (int*)malloc((n-2)*sizeof(int));
	for(int i = 1; i < n; i++) {
		printf("%d %d\n", i, i+1);
	}
	for(int i = 0; i < q; i++) {
		int a = rand() % n + 1;
		int b = rand() % n + 1;
		int da = rand() % n;
		int db = rand() % n;
		printf("%d %d  %d %d\n", a, da, b, db);
	}
}
