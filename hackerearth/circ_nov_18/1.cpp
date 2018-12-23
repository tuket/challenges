#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long ll;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        ll n, k;
        cin >> n >> k;
        string w;
        if(k == 1)
        {
            if(n % 2 == 0)
                w = "Bob";
            else
                w = "Alice";
        }
        else
        {
            ll x = k;
            while(true)
            {
                if(x > n)
                {
                    w = "Bob";
                    break;
                }
                n -= x;
                if(x > n)
                {
                    w = "Alice";
                    break;
                }
                n -= x;
                x *= k;
            }
        }
        cout << w << endl;
    }
}