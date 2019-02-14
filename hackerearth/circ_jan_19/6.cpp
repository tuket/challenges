#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;
typedef int64_t ll;

const ll M = 1000000007LL;

int n;
map<int, int> A;
vector<int> B;
int RB;

vector<ll> factTable;

void compFactTable()
{
    constexpr ll N = 1000001;
    factTable.resize(N);
    factTable[0] = factTable[1] = 1;
    for(int n=2; n<N; n++)
        factTable[n] = (n * factTable[n-1]) % M;
}

ll fact(ll x)
{
    return factTable[x];
}

template <class T>
T mul_mod(T a, T b, T m) { 
    if (m == 0) return a * b;

    T r = T();

    while (a > 0) {
        if (a & 1)
            if ((r += b) > m) r %= m;
        a >>= 1;
        if ((b <<= 1) > m) b %= m;
    }
    return r;
}

template <class T>
T pow_mod(T a, T n, T m) {
    T r = 1;

    while (n > 0) {
        if (n & 1)
            r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        n >>= 1;
    }
    return r;
}

ll inv(ll x)
{
    static unordered_map<ll, ll> cache;
    auto it = cache.find(x);
    if(it != cache.end())
        return it->second;
    ll res = pow_mod(x, M-2, M);
    cache[x] = res;
    cache[res] = x;
    return res;
}

ll multinomal()
{
    ll res = fact(RB);
    ll denom = 1;
    for(auto& p : A)
    {
        denom *= fact(p.second);
        denom %= M;
    }
    denom = inv(denom);
    res *= denom;
    res %= M;
    return res;
}

vector<ll> va;

class HowManySmaller
{
public:
    HowManySmaller() : v(1 << B, 0) {}

    void add(ll x)
    {
        for(ll i=0; i<B; i++)
        {
            ll shift = B-i-1;
            ll b = x >> shift;
            if((b & 1) == 0)
            {
                v[(b|1)<<shift]++;
            }
        }
    }

    void remove(ll x)
    {
        for(ll i=0; i<B; i++)
        {
            ll shift = B-i-1;
            ll b = x >> shift;
            if((b & 1) == 0)
            {
                v[(b|1)<<shift]--;
            }
        }
    }

    ll countLower(ll x)const
    {
        ll res = 0;
        ll b = x;
        for(ll i = 0; i<B; i++)
        {
            if(b & 1)
            {
                res += v[b<<i];
            }
            b >>= 1;
        }
        return res;
    }

private:
    const ll B = 18;
    vector<ll> v;
};

HowManySmaller hms;

ll solve()
{
    RB = n;
    ll res = 0;

    for(ll x : va)
        hms.add(x);
    
    ll mn = multinomal();
    for(int i=0; i<n; i++)
    {
        int c = B[i];
        auto up = A.lower_bound(c);
        hms.remove(c);
        
        RB--;
        ll MN = hms.countLower(c);
        MN = (MN * mn) % M;
        MN = (MN * inv(RB+1)) % M;
        res = (res + MN) % M;
        if(up->first == c)
        {
            mn = (mn * inv(RB+1)) % M;
            mn = (mn * up->second) % M;
            up->second--;
            if(up->second == 0)
                A.erase(up);
        }
        else
            break;
    }
    return res;
}   

int main()
{
    compFactTable();
    cin >> n;

    for(int i=0; i<n; i++)
    {
        int x;
        cin >> x;
        if(A.count(x))
            A[x]++;
        else
            A[x] = 1;
        va.push_back(x);
    }

    B.resize(n);
    for(int i=0; i<n; i++)
        cin >> B[i];

    ll res = solve();

    cout << res << endl;
}