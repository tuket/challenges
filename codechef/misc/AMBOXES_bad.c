#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef int64_t i64;
typedef int64_t u64;

const i64 I64_MAX = 0x7FFFFFFFFFFFFFFF;
const u64 U64_MAX = 0xFFFFFFFFFFFFFFFF;

int main()
{
	u64 n, nq;
	scanf("%lu %lu", &n, &nq);
	u64* A = malloc(sizeof(u64) * (n + n+1 + n+1 + n+1));
	u64* B = A + n;
	u64* C = B + n+1;
	u64* skip = C + n+1;
	for(u64 i = 0; i < n; i++)
		scanf("%lu", A+i);
/*	printf("A: ");
	for(u64 i = 0; i < n; i++)
		printf("%lu ", A[i]);
	printf("\n");*/

	B[0] = 0;
	for(u64 i = 0; i < n; i++) {
		B[i+1] = A[i] * B[i] + 1;
		if((B[i+1]-1) / A[i] != B[i]) { // overflow
			do {
				B[i+1] = U64_MAX;
				i++;
			} while(i < n);

		}
	}
/*	printf("B: ");
	for(u64 i = 0; i < n+1; i++)
		printf("%lu ", B[i]);
	printf("\n");*/

	C[0] = 1;
	for(u64 i = 0; i < n; i++) {
		C[i+1] = A[i] * C[i];
		if(C[i+1] / A[i] != C[i]) { // overflow
			do {
				C[i+1] = U64_MAX;
				i++;
			} while(i < n);
		}
	}
/*	printf("C: ");
	for(u64 i = 0; i < n+1; i++)
		printf("%lu ", C[i]);
	printf("\n");*/

	skip[0] = 0;
	skip[1] = 1;
	for(u64 i = 1; i < n; i++) {
		if(A[i] == 1)
			skip[i+1] = skip[i] + 1;
		else
			skip[i+1] = 1;
	}
/*	printf("skip: ");
	for(u64 i = 0; i < n+1; i++)
		printf("%lu ", skip[i]);
	printf("\n");*/

	for(u64 iq = 0; iq < nq; iq++)
	{
		u64 cc; scanf("%lu", &cc);
		if(cc == 0) {
			printf("0\n");
			continue;
		}
		u64 l0 = 0;
		u64 l1 = n;
		while(l0+1 < l1) {
			u64 l = (l0 + l1) / 2;
			if(C[l] <= cc)
				l0 = l;
			else
				l1 = l;
		}
		u64 l = l0;
		u64 c = 0;
		u64 res = n - l0;
		while(1) {
			if(cc - c >= C[l]) {
				const u64 q = (cc - c) / C[l]; 
				res += q * B[l];
				c += q * C[l];
			}
			if(c == cc)
				break;
			res += skip[l];
			l -= skip[l];
		}

		printf("%lu\n", res);
	}
}