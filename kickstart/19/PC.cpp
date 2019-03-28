#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

typedef uint64_t u64;

u64 MOD = 1000000007LL;

inline u64 powMod(u64 b, u64 e)
{
    u64 res = 1LL;
    for(u64 i = (1LL << 63LL); i; i>>=1LL) {
        res = (res * res) % MOD;
        if((i&e) != 0LL) {
            res = (res * b) % MOD;
        }
    }
    return res;
}

inline u64 inv(u64 x)
{
    return powMod(x, MOD-2LL);
}

inline u64 geoProg(u64 b, u64 k)
{
    u64 numer = powMod(b, k+1) - 1LL;
    u64 denom = inv(b-1LL);
    u64 res = (numer * denom) % MOD;
    res = (MOD + res - 1) % MOD;
    return res;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        u64 N, K, x1, y1, C, D, E1, E2, F;
        cin >> N >> K >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
        vector<u64> A(N);
        for(u64 i=0; i<N; i++) {
            A[i] = (x1 + y1) % F;
            u64 x2 = (C * x1 + D * y1 + E1) % F;
            u64 y2 = (D * x1 + C * y1 + E2) % F;
            x1 = x2;
            y1 = y2;
        }
        
        u64 res = 0LL;
        u64 ac = K;
        for(u64 i=0LL; i<N; i++)
        {
            u64 inc = ((N-i) * A[i]) % MOD;
            inc = (inc * ac) % MOD;
            res = (res + inc) % MOD;
            ac = (ac + geoProg(i+2LL, K)) % MOD;
        }        

        cout << "Case #" << kk << ": " << res << endl;
    }
}