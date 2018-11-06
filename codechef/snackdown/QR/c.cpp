#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        ull x = 0;
        vector<ull> a(n);
        for(int i=0; i<n; i++)
        {
            ull xx;
            cin >> xx;
            x += xx;
            a[i] = x;
        }
        int res = 0;
        ull p = 1;
        while(p < n)
        {
            p += a[p-1];
            res++;
        }
        cout << res << endl;
    }
}