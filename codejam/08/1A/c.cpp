#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

typedef array<int, 4> M;

M operator*(const M& a, const M& b) {
    M res = {
            (a[0]*b[0] + a[1]*b[2]) % 1000,
            (a[0]*b[1] + a[1]*b[3]) % 1000,
            (a[2]*b[0] + a[3]*b[2]) % 1000,
            (a[2]*b[1] + a[3]*b[3]) % 1000
    };
    return res;
}

M pow(M m, int n)
{
    M res = {1, 0, 0, 1};
    for(int i=0; i<32; i++)
    {
        int msk = 1 << i;
        if(msk & n) {
            res = res * m;
        }
        m = m * m;
    }
    return res;
}

int solve(int n)
{
	M m = {3, 5, 1, 3};
    m = pow(m, n);
    return (2 * m[0] + 999) % 1000;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        cout << "Case #" << kk << ": " << setfill('0') << setw(3) << solve(n) << endl;
    }
}