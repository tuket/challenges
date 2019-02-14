#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

array<int64_t, 2> solveSimpl(int n, const vector<int64_t>& v)
{
    int64_t B = numeric_limits<int64_t>::min();
    vector<pair<int, int>> r;

    for(int i=0; i<n; i++)
    {
        int64_t b = 0;
        for(int j=i; j<n; j++)
        {
            b += v[j];
            if(b >= B)
            {
                if(b > B)
                {
                    r.clear();
                    B = b;
                }
                r.push_back({i, j});
            }
        }
    }
    
    int K;
    if(B < 0)
    {
        B = 0;
        K = 0;
    }
    else
    {
        K = 1;
        int e = r[0].second;
        for(int i=1; i<r.size(); i++)
        {
            if(e < r[i].first)
            {
                K++;
                e = r[i].second;
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

    array<int64_t, 2> res = solveSimpl(n, v);

    cout << res[0] << " " << res[1] << endl;
}
#endif