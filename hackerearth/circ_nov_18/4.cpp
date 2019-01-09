#include <iostream>
#include <vector>
#include <array>
#include <map>

using namespace std;

typedef unsigned char ub;
typedef unsigned long long ull;
constexpr ull M = 1000000007ULL;

typedef array<ull, 256> AT;

ull fact(int n)
{
    static vector<ull> cache = {1, 1};
    if(n < cache.size())
        return cache[n];
    for(int i=cache.size(); i<=n; i++)
    {
        ull x = cache.back();
        x = (x * i) % M;
        cache.push_back(x);
    }
    return cache.back();
}

AT operator-(const AT& a, const AT& b)
{
    AT c;
    for(int i=0; i<256; i++)
    {
        c[i] = a[i] - b[i];
    }
    return c;
}

int main()
{
    int N;
    cin >> N;
    vector<AT> A(N+1);
    A[0] = {0};
    for(int i=1; i<=N; i++)
    {
        A[i] = A[i-1];
        int x;
        cin >> x;
        A[i][x]++;
    }
    
    array<vector<int>, 256> KK1;
    for(int x=0; x<256; x++)
    for(int i=0; i<256; i++)
    {
        if((i & x) == x)
            KK1[x].push_back(i);
    }

    array<array<vector<int>, 256>, 256> KK2;
    for(int x=0; x<256; x++)
    for(int i : KK1[x])
    for(int j : KK1[x])
    {
        if((i & j & x) == x)
            KK2[x][i].push_back(j);
    }

    //x -> zeros -> vector
    vector<array<array<ull, 256>, 256>> P3(N+1);
    for(int ia=0; ia<=N; ia++)
    for(int x=0; x<256; x++)
    {
        //P3[ia][x] = {0};
        for(int i : KK1[x])
        for(int j : KK2[x][i])
        {
            ull c = 0;
            int mask = (i & j) ^ x;
            for(int k : KK2[x][i])
            {
                if((i & j & k) == x)
                {
                    c = (c + A[ia][k]) % M;
                }
            }
            //ull val = (c * xv) % M;
            ull& p3 = P3[ia][x][mask];
            p3 = (p3 + c) % M;
        }
    }

    int NQ;
    cin >> NQ;
    for(int iq=0; iq<NQ; iq++)
    {
        int L, R;
        unsigned x;
        cin >> L >> R >> x;
        ull res = 0;
        const AT a = A[R] - A[L-1];
        vector<int> keys; keys.reserve(256);
        for(int i : KK1[x])
        if(a[i] != 0)
            keys.push_back(i);

        vector<vector<int>> keys2(256);
        for(int i : keys)
        for(int j : KK2[x][i])
        if(a[j] != 0)
        {
            keys2[i].push_back(j);
        }

        for(int i : keys)
        {
            ull ires = 0;
            for(int j : keys2[i])
            {
                int mask = (i & j) ^ x;
                ull jres = P3[R][x][mask] - P3[L-1][x][mask];
                jres = (a[j] * jres) % M;
                ires = (ires + jres) % M;
            }
            ull ar = (a[i] * ires) % M;
            res = (res + ar) % M;
        }

        cout << res << endl;
    }
}