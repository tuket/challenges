#include <iostream>
#include <cstdint>
#include <array>

using namespace std;

inline int ones(int i)
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
//#define ones(x) __builtin_popcount(x)

/*inline int next(int a)
{
    int t = (a | (a - 1)) + 1;  
    return t | ((((t & -t) / (a & -a)) >> 1) - 1);
}*/

inline int next(int a)
{
    unsigned int t = a | (a - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(a) + 1));
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        int ca = ones(A);
        int cb = ones(B);
        int res = 0;
        for(int a=(1<<ca)-1; a < C; a = next(a))
        {
                int b = C-a;
                if(ones(b) == cb)
                    res++;
        }
        printf("%d\n", res);
    }
}