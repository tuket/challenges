#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <sstream>

using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

constexpr i64 M = 1'000'000'007;

i64 gcd(i64 a, i64 b)
{
	while(b){
		i64 bb = b;
		b = a % b;
		a = bb;
	}
	return a;
}

constexpr i64 NN = 1'000'001;
vector<i64> pf(NN, 0);

i64 simpleSolve(i64 n)
{
    vector<i64> g(n);
    i64 res = 0;
    for(int i = 1; i <= n; i++)
    {
        i64 r = 0;
        for(int j = 1; j <= n; j++)
        {
            const i64 g = gcd(i, j);
            const i64 x = (i * j) / (g*g);
            r += x;
            r %= M;
        }
        res += r;
        res %= M;
    }
    return res;
}

i64 seqSum(i64 n) {
    i64 r = n * (n+1);
    r /= 2;
    r %= M;
    return r;
}

i64 solve(i64 n)
{
    i64 res = 0;
    for(i64 i = 1; i <= n; i++) {
        res += i * (n+1) * n / 2;
        res %= M;
    }
    res %= M;
    for(i64 i = 2; i <= n; i++) {
        res += (M - (i*i-1) * seqSum(n/i));
        res %= M;
        for(i64 d = 2; d*i <= n; d++) {
            const i64 j = d*i;
            res += (M - (i*i-1) * seqSum(n/i) * d);
            res %= M;
            res += (i*i-1) * seqSum(n/j) * d * d;
            res %= M;
        }
    }
    return res;
}

int main()
{
    solve(8);
    /*i64 n;
    cin >> n;
    i64 res = simpleSolve(n);
    cout << res << endl;*/
    /*for(i64 i = 1; i <= 20; i++)
    {
        cout << i << ": " << simpleSolve(i) << " | " << solve(i) << endl;
    }*/
    cout << simpleSolve(1'0000) << endl;
}
