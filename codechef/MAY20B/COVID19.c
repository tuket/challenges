#include <stdio.h>
#include <stdlib.h>

int cmpInt (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a < b ? b : a; }

int main()
{
	int nn;
	scanf("%d", &nn);
	for(int kk = 1; kk <= nn; kk++)
	{
		int n;
		scanf("%d", &n);
		int X[8];
		for(int i = 0; i < n; i++)
			scanf("%d", X+i);
		qsort(X, n, sizeof(int), cmpInt);
		int minVal = 100;
		int maxVal = 0;
		int val = 1;
		for(int i = 1; i < n; i++) {
			if(X[i] - X[i-1] <= 2)
				val++;
			else {
				minVal = min(minVal, val);
				maxVal = max(maxVal, val);
				val = 1;
			}
		}
		minVal = min(minVal, val);
		maxVal = max(maxVal, val);
		printf("%d %d\n", minVal, maxVal);
	}
}
