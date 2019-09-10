#include <iostream>
#include <array>

using namespace std;
typedef int64_t i64;

constexpr i64 M = 1'000'000'007LL;
constexpr i64 MN = 1'000'008;

static array<i64, MN> factTab;
void initFactTab()
{
    i64 val = 1;
    factTab[0] = 1;
    factTab[1] = 1;
    for(i64 i = 2; i < MN; i++) {
        val *= i;
        val %= M;
        factTab[i] = val;
    }
}

i64 pow(i64 b, i64 e)
{
    if(b == 0)
        return 0;
    i64 res = 1;
    for(i64 i = 1LL << 32LL; i > 0; i >>= 1) {
        res *= res;
        res %= M;
        if(e & i) {
            res *= b;
            res %= M;
        }
    }
    return res;
}

i64 inv(i64 n)
{
    const i64 res = pow(n, M-2);
    return res;
}

i64 factorial(i64 n) 
{ 
    i64 res = factTab[n];
    return res;
}

i64 binomial(i64 n, i64 k)
{
    if(k < 0)
        return 0;
    i64 num = factorial(n);
    i64 den = (factorial(k) * factorial(n-k)) % M;
    den = inv(den);
    return (num * den) % M;
}

int main()
{
    initFactTab();
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        i64 n;
        cin >> n;
        i64 x = n;
        i64 i;
        for(i = 1; ; i <<= 1LL)
        {
            if(x < i)
                break;
            x -= i;
        }
        n = n - x;

        i64 res = 0;
        // odd root
        {
            const i64 baseOdds = i >> 1LL;
            const i64 baseEvens = n - baseOdds;
            const i64 fillOdds = x >> 1LL;
            const i64 fillEvens = x - fillOdds;
            const i64 pp = (binomial(baseOdds, fillOdds) * binomial(baseOdds, fillEvens)) % M;
            res += pp;
        }
        // even root
        {
            const i64 baseEvens = i >> 1;
            const i64 baseOdds = n - baseEvens;
            const i64 fillEvens = (x - 1LL) >> 1LL;
            const i64 fillOdds = x - fillEvens;
            const i64 pp = (binomial(baseEvens, fillOdds) * binomial(baseEvens, fillEvens)) % M;
            res += pp;
            res %= M;
        }
        i64 commonFactor = factorial((x+n) >> 1LL) * factorial((x+n) - ((x+n) >> 1LL));
        commonFactor %= M;
        res *= commonFactor;
        res %= M;

        cout << res << endl;
    }
}