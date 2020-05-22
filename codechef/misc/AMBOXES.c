#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef int64_t i64;

i64 hdiv(i64 a, i64 b) {
	return (a+b-1) / b;
}

int main()
{
	i64 n, nq;
	scanf("%lu %lu", &n, &nq);
	i64* A = malloc(sizeof(i64) * (n + n+1));
	i64* skip = A + n;
	for(i64 i = 0; i < n; i++)
		scanf("%lu", A+i);

	i64 skipSize = 1;
	skip[0] = 0;
	for(int i = 0; i < n; i++) {
		if(A[i] == 1)
			skip[skipSize-1]++;
		else {
			skip[skipSize] = 1;
			A[skipSize-1] = A[i];
			skipSize++;
		}
	}

	/*printf("A: ");
	for(i64 i = 0; i < skipSize-1; i++)
		printf("%ld ", A[i]);
	printf("\n");
	printf("skip: ");
	for(i64 i = 0; i < skipSize; i++)
		printf("%ld ", skip[i]);
	printf("\n");*/

	for(i64 iq = 0; iq < nq; iq++)
	{
		i64 cc;
		scanf("%ld", &cc);
		i64 res = skip[0] * cc;
		i64 l = skip[0];
		for(i64 i = 0; i < skipSize-1; i++)
		{
			const i64 d = hdiv(cc, A[i]);
			//res += d;
			res += d*skip[i+1];
			l += skip[i+1];
			cc = d;
			if(cc == 1) {
				res += n - l;
				break;
			}
		}
		printf("%ld\n", res);
	}
}