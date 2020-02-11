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

int main()
{
    i64 n;
    cin >> n;
    vector<i64> g(n);
    i64 res = 0;
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
    {
        const i64 g = gcd(i, j);
        const i64 x = (i * j) / (g*g);
        res += x;
        res %= M;
    }
    cout << res << endl;
}
