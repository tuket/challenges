#include <iostream>

using namespace std;

inline unsigned seqSum(unsigned n)
{
    return ((n+1) * n) / 2;
}

int main()
{
    unsigned n;
    cin >> n;
    unsigned res = 0;
    for(unsigned a = 1; a<n; a++)
    {
        res += seqSum(a) * ((n-a)/2);
    }
    cout << res << endl;
}