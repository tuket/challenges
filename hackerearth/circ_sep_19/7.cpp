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

vector<i64> a;
vector<vector<i64>> c;

struct DFS
{
    i64 t;
};

int main()
{
    i64 n;
    cin >> n;
    a.resize(n);
    c.resize(n);
    for(i64 i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++) {
        i64 p;
        cin >> p;
        c[p].push_back(i);
    }


}