#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef int64_t i64;

i64 fact(i64 n)
{
    i64 res = 1;
    for(i64 i = 2; i <= n; i++) {
        res *= i;
        res %= 1'000'000'007;
    }
    return res;
}

int main()
{
    i64 N, M;
    cin >> N >> M;
    const i64 res = fact(M);
    cout << res << endl;
}