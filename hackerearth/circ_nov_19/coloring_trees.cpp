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

unordered_map<int, unordered_set<int>> con;
unordered_set<int> dd;
vector<bool> cwd;
vector<int> pv;

void rec(int a, int pa = -1)
{
    if(dd.count(a)) {
        for(int b = a; b >= 0; ) {
            cwd[b] = true;
            int pb = b;
            b = pv[b];
            pv[pb] = -1;
        }
    }
    for(int b : con[a])
    if(b != pa) {
        pv[b] = a;
        rec(b, a);
    }
}

int main()
{
    int n, k;
    cin >> n >> k;    
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].insert(b);
        con[b].insert(a);
    }
    cwd = vector<bool>(n, false);
    pv = vector<int>(n, -1);
    
    for(int i = 0; i < k; i++) {
        int x; cin >> x; x--;
        dd.insert(x);
    }

    int a = *dd.begin();
    rec(a);

    int res = 0;
    for(int i = 0; i < n; i++) {
        if(cwd[i])
            res++;
    }

    cout << res << endl;
}
