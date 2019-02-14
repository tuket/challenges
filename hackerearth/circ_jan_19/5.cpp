#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef int64_t i64;

i64 n, m;

inline i64 edge(i64 i, i64 j)
{
    return i*n + j;
}

inline i64 tri(i64 i, i64 j, i64 k)
{
    return n*(i*n + j) + k;
}

int main()
{
    cin >> n >> m;
    vector<vector<i64>> W(n);
    vector<array<i64, 2>> E;
    for(i64 i=0; i<m; i++)
    {
        i64 w1, w2;
        cin >> w1 >> w2;
        if(w1 > w2)
            swap(w1, w2);
        w1--; w2--;
        W[w1].push_back(w2);
        W[w2].push_back(w1);
        E.push_back({w1, w2});
        E.push_back({w2, w1});
    }

    for(auto& v : W)
        sort(v.begin(), v.end());
    sort(E.begin(), E.end());

    i64 l2 = 0;
    for(auto e : E)
    {
        i64 i = e[0];
        i64 j = e[1];
        const auto& C1 = W[j];
        auto it = upper_bound(C1.begin(), C1.end(), e[0]);
        l2 += C1.size() - (it - C1.begin());
    }
    i64 res = 0;

    for(i64 i=1; i<n-1; i++)
        res += i * (n-i-1);
    
    res -= E.size()/2 * (n-2);
    res += l2;

    cout << res << endl;
}