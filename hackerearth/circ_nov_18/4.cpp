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
        for(int i=0; i<256; i++)
        if(a[i] != 0)
            keys.push_back(i);

        for(int i : keys)
        if((i & x) == x)
        for(int j : keys)
        if((i & j & x) == x)
        for(int k : keys)
        if((i & j & k) == x)
        {
            ull ar = (a[i] * a[j]) % M;
            ar = (ar * a[k]) % M;
            res = (res + ar) % M;
        }

        cout << res << endl;
    }
}