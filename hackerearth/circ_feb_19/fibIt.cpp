#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef uint64_t ll;
constexpr ll MOD = 1'000'000'007ULL;

ll f(const ll n)
{
    ll x = 0;
    ll y = 1;
    
    ll h = 0;
    for(ll i=n; i; i>>=1)
        h++;
    h--;

    for(ll i=(1<<h); i; i>>=1)
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