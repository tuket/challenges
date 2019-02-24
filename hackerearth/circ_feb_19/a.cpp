#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef uint64_t ll;
constexpr ll MOD = 1'000'000'007ULL;

ll expMod(ll b, ll e)
{
    ll res = 1;
    ll k = 0x8000'0000'0000'0000;
    while(k)
    {
        res = (res * res) % MOD;
        if(k & e)
            res = (res * b) % MOD;
        k >>= 1;
    }
    return res;
}

ll invMod(ll a)
{
    return expMod(a, MOD-2);
}

ll fib(const ll n)
{
    ll x = 0;
    ll y = 1;
    
    ll h = 0;
    for(ll i=n; i; i>>=1)
        h++;
    h--;

    for(ll i=(1ULL<<h); i; i>>=1)
    {
        ll a = x, b = y;
        y = (a*a+b*b)%MOD;
        x = (a*(MOD-a+2*b))%MOD;

        if(n&i) {
            swap(x, y);
            y=(y+x)%MOD;
        }
    }

    return x;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        ll n;
        cin >> n;

        ll b = expMod(2, n);
        ll a = (MOD - fib(n+1) + b) % MOD;
        ll ab = (a * invMod(b)) % MOD;

        cout << ab << endl;
    }
}