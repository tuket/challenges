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

i64 mkey(i64 x, i64 y) {
    return (x << 32) | y;
}

i64 n, k;
unordered_map<i64, vector<i64>> conn;
unordered_map<i64, i64> tolls;
unordered_map<i64, i64> traffic;
vector<i64> pp;

i64 bfsFill(unordered_map<i64, vector<i64>>& conn,
    unordered_map<i64, i64>& traffic,
    int prev, int cur)
{
    const auto& m = conn[cur];
    i64 c = 1;
    for(i64 b : m)
    if(b != prev) {
        c += bfsFill(conn, traffic, cur, b);
    }
    if(prev != -1) {
        traffic[mkey(cur, prev)] = c;
    }
    return c;
};

i64 f(i64 prev, i64 a)
{
    pp.clear();
    for(auto p : traffic) {
        if(p.second != 0)
            pp.push_back(p.second * tolls[p.first]);
    }
    sort(pp.begin(), pp.end());
    i64 best = 0;
    for(int i = 0; i < n-1-k; i++)
        best += pp[i];

    i64 sumA = 0;
    for(i64 b : conn[a])
        sumA += traffic[mkey(b, a)];
    for(i64 b : conn[a])
    if(b != prev) {
        const i64 ab = traffic[mkey(a, b)];
        const i64 ba = traffic[mkey(b, a)];
        traffic[mkey(a, b)] = sumA - ba + 1;
        traffic[mkey(b, a)] = 0;
        best = min(best, f(a, b));
        traffic[mkey(a, b)] = ab;
        traffic[mkey(b, a)] = ba;
    }
    return best;
}

i64 solve()
{
    cin >> n >> k;
    conn.clear();
    tolls.clear();
    traffic.clear();
    pp.reserve(n-1);

    for(int i = 0; i < n-1; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        x--; y--;
        conn[x].push_back(y);
        conn[y].push_back(x);
        tolls[mkey(x, y)] = a;
        tolls[mkey(y, x)] = b;
        traffic[mkey(x, y)] = 0;
        traffic[mkey(y, x)] = 0;
    }
    bfsFill(conn, traffic, -1, 0);
    
    i64 cur = 0;
    return f(-1, 0);
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk = 1; kk <= nn; kk++)
    {
        cout << solve() << endl;
    }
}
