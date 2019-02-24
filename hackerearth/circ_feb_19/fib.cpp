#include <iostream>

using namespace std;

typedef int64_t ll;
constexpr ll MOD = 1'000'000'007LL;

void fib(ll n, ll&x, ll&y)
{
    if(n==0){
        x = 0;
        y = 1;
        return;
    }
     
    if(n&1){
        fib(n-1, y, x);
        y=(y+x)%MOD;
    }else{
        ll a, b;
        fib(n>>1, a, b);
        y = (a*a+b*b)%MOD;
        x = (a*b + a*(MOD-a+b))%MOD;
    }
}

ll f(ll n)
{
    ll a, b;
    fib(n, a, b);
    return a;
}

ll f2(const ll n)
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
    ll x = 1'00000'00000;
    cout << f(x) << endl;
    cout << f2(x) << endl;
}