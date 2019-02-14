#include <iostream>
#include <vector>

using namespace std;

typedef int64_t ll;

constexpr ll MOD = 1000000007LL;

/*ll expMod(ll b, ll e)
{
    ll res = 1;
    for(int i=63; i>=0; i--)
    {
        if((e >> i) & 1) {
            res *= b;
            res %= MOD;
        }
        res *= res;
        res %= MOD;
    }
    return  res;
}*/

ll expMod(ll b, ll e) 
{ 
    ll res = 1;      // Initialize result 
    while (e > 0) 
    { 
        if (e & 1) 
            res = (res*b) % MOD; 
  
        e = e >> 1;
        b = (b*b) % MOD;   
    } 
    return res; 
} 

ll inv(ll x)
{
    return expMod(x, MOD-2);
}

class Q
{
public:
    Q(ll a = 0, ll b = 1) : a(a), b(b) {}
    Q(const Q& o) : a(o.a), b(o.b) {}

    Q operator+(Q o)const
    {
        Q res;
        res.a = ((a * o.b) % MOD + (b * o.a) % MOD) % MOD;
        res.b = (b * o.b) % MOD;
        return res;
    }

    Q operator*(Q o)const
    {
        Q res;
        res.a = (a * o.a) % MOD;
        res.b = (b * o.b) % MOD;
        return res;
    }

    ll a, b;
};

void solve()
{
    int N, K, M;
    cin >> N >> K >> M;

    ll M12 = (M+1)/2;
    ll Q = expMod(N, M12);
    ll P = expMod((MOD-N+1)%MOD, M12);
    if(M12 % 2 == 0)
        P = (MOD - P + Q) % MOD;
    else
        P = (P + Q) % MOD;
    if(M % 2 == 0)
    {
        P = (P * (N+K)) % MOD;
        P = (P + expMod(N-1, M12)) % MOD;
        Q = (Q * (N+K)) % MOD;
    }

    ll invQ = inv(Q);
    ll PQ = (P * invQ) % MOD;
    cout << PQ << endl;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
        solve();
}