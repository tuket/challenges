#include <iostream>
#include <array>
#include <vector>

using namespace std;

typedef long long ll;

template <int N>
int p10(int x, int n)
{
    static vector<int> t = []()
    {
        vector<int> t(50);
        int x = 1;
        for(int i=0; i<t.size(); i++) {
            x %= N;
            t[i] = x;
            x *= 10;
        }
        return t;
    }();
    return (x * t[n])%N;
}

typedef array<array<array<array<array<array<ll, 7>, 5>, 3>, 2>, 2>, 41> Table;
    
ll solve(const vector<int>& v)
{
    int n = v.size();
    vector<Table> T(2);
    auto setZeros = [=](Table& t)
    {
        for(int j=0; j<n; j++)
        for(int s=0; s<2; s++)
        for(int r1=0; r1<2; r1++)
        for(int r2=0; r2<3; r2++)
        for(int r3=0; r3<5; r3++)
        for(int r4=0; r4<7; r4++)
        {
            t[j][s][r1][r2][r3][r4] = 0;
        }
    };
    for(int i=0; i<2; i++)
        setZeros(T[i]);

    const int M = 2 * 3 * 5 * 7;
    {
        Table& t = T[(n-1)%2];
        int x = v[n-1];
        int r1 = x % 2;
        int r2 = x % 3;
        int r3 = x % 5;
        int r4 = x % 7;
        t[0][1][r1][r2][r3][r4] = 1;
        x = M-x;
        r1 = x % 2;
        r2 = x % 3;
        r3 = x % 5;
        r4 = x % 7;
        t[0][0][r1][r2][r3][r4] = 1;
    }

    for(int i=n-2; i>=0; i--)
    {
        Table& t1 = T[i%2];
        Table& t2 = T[(i+1)%2];
        setZeros(t1);
        const ll x = v[i];
        //
        for(int j=0; j<n-1-i; j++)
        {
            int xr1 = p10<2>(x, j+1);
            int xr2 = p10<3>(x, j+1);
            int xr3 = p10<5>(x, j+1);
            int xr4 = p10<7>(x, j+1);
            for(int r1=0; r1<2; r1++)
            for(int r2=0; r2<3; r2++)
            for(int r3=0; r3<5; r3++)
            for(int r4=0; r4<7; r4++)
            {
                ll v1 = t2[j][1][r1][r2][r3][r4];
                t1[j+1][1] [(r1+xr1)%2] [(r2+xr2)%3] [(r3+xr3)%5][(r4+xr4)%7] += v1;
                
                ll v2 = t2[j][0][r1][r2][r3][r4];
                t1[j+1][0] [(M+r1-xr1)%2] [(M+r2-xr2)%3] [(M+r3-xr3)%5] [(M+r4-xr4)%7] += v2;
            }
        }
        // + -
        for(int j=0; j<n-1-i; j++)
        {
            for(int r1=0; r1<2; r1++)
            for(int r2=0; r2<3; r2++)
            for(int r3=0; r3<5; r3++)
            for(int r4=0; r4<7; r4++)
            {
                ll w = t2[j][0][r1][r2][r3][r4] + t2[j][1][r1][r2][r3][r4];
                t1[0][1] [(r1+x)%2] [(r2+x)%3] [(r3+x)%5] [(r4+x)%7] += w;
                t1[0][0] [(M+r1-x)%2] [(M+r2-x)%3] [(M+r3-x)%5] [(M+r4-x)%7] += w;
            }
        }
    }

    ll res = 0;
    for(int j=0; j<n; j++)
    for(int r1=0; r1<2; r1++)
    for(int r2=0; r2<3; r2++)
    for(int r3=0; r3<5; r3++)
    for(int r4=0; r4<7; r4++)
    if(r1*r2*r3*r4 == 0)
    {
        ll v = T[0][j][1][r1][r2][r3][r4];
        res += v;
    }

    return res;
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
        vector<int> v(n);
        for(int i=0; i<n; i++)
            v[i] = s[i] - '0';
        ll res = solve(v);
        cout << "Case #" << kk << ": " << res << endl;
    }
}