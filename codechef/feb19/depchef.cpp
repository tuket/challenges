#include <iostream>
#include <vector>

using namespace std;

typedef int64_t ll;

ll A[101];
ll D[101];

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        for(int i=0; i<n; i++)
            cin >> A[i];
        for(int i=0; i<n; i++)
            cin >> D[i];
        ll best = -1;
        for(int i=0; i<n; i++)
        {
            int l = (i+n-1) % n;
            int r = (i+1) % n;
            ll d = D[i];
            if(d > A[l] + A[r])
                best = max(best, d);
        }
        cout << best << endl;
    }
}