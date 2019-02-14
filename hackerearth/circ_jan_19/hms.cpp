#include <iostream>
#include <vector>

using namespace std;

typedef int64_t ll;

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
                v[(b|1)<<shift]++;
            }
        }
    }

    ll countLower(ll x)const
    {
        ll res = 0;
        ll prev = x+1;
        for(ll i = 0; i<B; i++)
        {
            ll b = (x >> i) << i;
            if(prev != b)
            {
                res += v[b];
                prev = b;
            }
        }
        return res;
    }

private:
    const ll B = 5;
    vector<ll> v;
};

int main()
{
    HowManySmaller hms;
    vector<ll> v{10, 5, 9, 5, 2, 8, 8, 5, 2, 1, 5, 5, 7, 6, 10, 8, 6, 3, 3, 2};
    for(ll x : v)
        hms.add(x);
    {
        ll n = hms.countLower(1);
        cout << n << endl;
    }
    {
        ll n = hms.countLower(2);
        cout << n << endl;
    }
    {
        ll n = hms.countLower(3);
        cout << n << endl;
    }
    {
        ll n = hms.countLower(5);
        cout << n << endl;
    }
    {
        ll n = hms.countLower(8);
        cout << n << endl;
    }
}