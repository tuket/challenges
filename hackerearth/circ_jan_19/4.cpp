#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

array<int64_t, 2> solve(int n, const vector<int64_t>& v)
{
    int64_t B = numeric_limits<int64_t>::min();
    int64_t minV = 0;
    map<int64_t, set<int>> mv;

    int64_t val = 0;
    for(int i=0; i<n; i++)
    {
        val += v[i];
        if(!mv.count(val))
            mv[val] = set<int>();
        mv[val].insert(i);

        int64_t b = val - minV;
        B = max(B, b);
        minV = min(minV, val);
    }
    
    int K;
    if(B < 0)
    {
        B = 0;
        K = 0;
    }
    else
    {
        vector<array<int, 2>> r;

        int64_t val = 0;
        for(int i=0; i<n; i++)
        {
            int64_t a = B + val;
            if(mv.count(a))
            {
                set<int>& inds = mv[a];
                auto it = inds.begin();
                for(; it != inds.end(); ++it)
                {
                    int j = *it;
                    if(i <= j)
                    {
                        r.push_back({i, j});
                        break;
                    }
                }
            }
            val += v[i];
        }
        
        //sort(r.begin(), r.end());

        K = 1;
        const int rn = r.size();
        int s = r[rn-1][0];
        for(int i=rn-2; i>=0; i--)
        {
            if(s > r[i][1])
            {
                K++;
                s = r[i][0];
            }
        }
    }

    return {B, K};
}

#ifndef TEST
int main()
{
    int n;
    cin >> n;
    vector<int64_t> v(n);
    for(int64_t& x : v)
        cin >> x;

    array<int64_t, 2> res = solve(n, v);

    cout << res[0] << " " << res[1] << endl;
}
#endif