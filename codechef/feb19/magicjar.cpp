#include <iostream>

using namespace std;

typedef int64_t ll;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int N;
        cin >> N;
        ll res = 0;
        for(int i=0; i<N; i++)
        {
            ll a;
            cin >> a;
            res += a;
        }
        res -= N-1;
        cout << res << endl;
    }
}