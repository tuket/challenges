#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

inline bool isUgly(ll x)
{
    return x % 2L == 0L || x % 3L == 0L || x % 5L == 0L || x % 7 == 0L;
}

ll solve(const vector<ll>& v, int i, ll res, ll ac, ll s)
{
    if(i == v.size())
    {
        return isUgly(res + s * ac) ? 1L : 0L;
    }
    return
        solve(v, i+1, res,          ac*10 + v[i], s) +
        solve(v, i+1, res + s * ac, v[i],        -1) +
        solve(v, i+1, res + s * ac, v[i],        +1);
}

ll solve(const vector<ll>& v)
{
    if(v.size() == 1)
    {
        return isUgly(v[0]) ? 1 : 0;
    }
    solve(v, 1, 0, v[0], +1);
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        string s;
        cin >> s;
        const int n = s.size();
        vector<ll> v(n);
        for(int i=0; i<n; i++)
            v[i] = s[i] - '0';
        ll res = solve(v);
        cout << "Case #" << kk << ": " << res << endl;
    }
}