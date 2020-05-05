#include <stdio.h>
#include <stdint.h>
#include <algorithm>

typedef int64_t i64;

i64 iSqrt(i64 c)
{
	i64 cb = 61;
	while(((1LL << cb) & c) == 0LL) cb--;
	return c >> ((cb+1LL) / 2LL);
}

i64 surf(i64 n, i64 w, i64 h)
{
	if(n == 1LL)
		return w * h;
	i64 s = 1LL + 2LL * (n-1LL);
	return 2LL*(s+w-1LL) + 2LL*(s+h-3LL);
}

i64 f(i64 Z, i64 w, i64 h)
{
	i64 res = 0;
	i64 z = Z;
	i64 n = 1;
	while(z != 2LL) {
		res += z * surf(n, w, h);
		z -= 2LL;
		n++;
		res += z * surf(n, w, h);
		z += 1LL;
		n++;
	}
	res += z * surf(n, w, h);
	return res;
}

i64 f(i64 Z, i64 wh)
{
	i64 h = wh / 3LL + 1LL;
	i64 w = h + wh%3;
	return f(Z, w, h);
}

i64 solve(i64& z, i64 NR)
{
	if(NR < 43)
		return 0;
	i64 minZ = 1;
	i64 maxZ = std::min(iSqrt(NR), i64(1200320));
	while(minZ+1 < maxZ) {
		const i64 mid = (minZ + maxZ) / 2LL;
		const i64 midVal = f(mid, 1, 1);
		if(midVal == NR) {
			z = mid;
			return NR;
		}
		if(midVal < NR)
			minZ = mid;
		else
			maxZ = mid;
	}
	if(f(maxZ, 1, 1) == NR)
		z = maxZ;
	else
		z = minZ;

	i64 best = 0;
	for(i64 h = 1; ; h++)
	{
		i64 w = h;
		i64 nr = f(z, w, h);
		if(nr > NR)
			break;
		best = std::max(best, nr);

		w++;
		nr = f(z, w, h);
		if(nr > NR)
			continue;
		best = std::max(best, nr);
	}
	return best;
}

int main()
{
	//printf("%ld\n", f(3, 1, 5));
	int nn;
	scanf("%d", &nn);
	for(int kk = 1; kk <= nn; kk++)
	{
		i64 NR, z;
		scanf("%ld", &NR);
		const i64 res = solve(z, NR);
		if(res == 0)
			printf("Case #%d: IMPOSSIBLE\n", kk);
		else
			printf("Case #%d: %ld %ld\n", kk, z, res);
	}
}