#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<int, 32> A32;

int N, Q;
vector<int> v;
vector<A32> dp;

int main()
{
    cin >> N >> Q;
    
    v.resize(N);
    for(int& x : v)
    {
        cin >> x;
        x--;
    }

    int last = 0;
    for(int iq=0; iq<Q; iq++)
    {
        int a, b;
        cin >> a >> b;
        a = (a+last-1) % N;
        b = (b+last-1) % N;
        int n = b-a+1;
        dp.resize(b-a+1);
        for(int i=0; i<32; i++)
            dp[0][i] = abs(v[a] - i);
        for(int i=0; i<n-1; i++)
        {
            int mn = dp[i][0];
            dp[i+1][0] = mn + v[a+i+1];
            for(int j=1; j<32; j++)
            {
                mn = min(mn, dp[i][j]);
                dp[i+1][j] = mn + abs(v[a+i+1] - j);
            }
        }

        int res = dp[n-1][0];
        for(int i=1; i<32; i++)
            res = min(res, dp[n-1][i]);

        cout << res << endl;
        last = res;
    }
}