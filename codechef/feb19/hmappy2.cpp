#include <iostream>
#include <numeric>

using namespace std;

typedef uint64_t ull;

ull gcd(ull a, ull b)
{
    while(true)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

ull lcm(ull a, ull b)
{
    ull temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        ull N, A, B, K;
        cin >> N >> A >> B >> K;
        ull AB = lcm(A, B);
        ull res = N/A + N/B - 2*(N/AB);
        if(res >= K)
            cout << "Win" << endl;
        else
            cout << "Lose" << endl;
    }
}