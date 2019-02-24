#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

int exp(int b, int e)
{
    int res = 1;
    for(int i=0; i<e; i++)
        res *= b;
    return res;
}

template <int N>
bool nextPerm(array<int, N>& v)
{
    const int n = v.size();
    int i = n-1;
    while(i > 0)
    {
        if(v[i-1] < v[i])
        {
            for(int j1=i, j2=n-1; j1<=j2; j1++, j2--)
            {
                swap(v[j1], v[j2]);
            }
            auto bIt = upper_bound(v.begin()+i, v.end(), v[i-1]);
            swap(v[i-1], *bIt);
            return true;
        }
        else
            i--;
    }
    return false;
}

int main()
{
    constexpr int N = 7;

    array<int, N> v;
    iota(v.begin(), v.end(), 1);

    int a = 0;
    int np = 0;
    do
    {
        np++;
        for(int x=0; x < (1<<N); x++)
        {
            for(int i=0; i<N; i++)
            {
                if((x & (1<<(v[i]-1)) ) != 0 && (x & (1<<i)) != 0) {
                    a++;
                    break;
                }
            }
        }
    } while(nextPerm<N>(v));

    int b = (1 << N) * np;

    cout << a << "/" << b << endl;
}