#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>

using namespace std;

typedef uint16_t u16;
typedef uint32_t u32;
constexpr u32 MOD = 1'000'000'007;
//constexpr u32 DM = 100;

u32 n;
string s;

namespace std
{
    template <>
    struct hash<array<u16, 3>>
    {
        size_t operator()(array<u16, 3> a)const
        {
            size_t x = a[0];
            x <<= 2;
            x |= (u16)a[1];
            x <<= 2;
            x |= (u16)a[2];
            return x;
        }
    };
}

unordered_map<array<u16, 3>, u32> F;
vector<u32> vOnes(5001);
//vector<u32> F(DM*DM*DM, 0);



u32 f(u32 i, u32 minLen, u32 minOnes)
{
    if(i >= n)
        return 1;
    if(s[i] == '0')
        return 0;
    array<u16, 3> entry{i, minLen, minOnes};
    {
        auto it = F.find(entry);
        if(it != F.end()) {
            return it->second;
        }
    }

    u32 res = 0;
    u32 len = minLen-1;
    u32 ones = vOnes[len] - vOnes[i];
    for(u32 j = i + minLen-1; j < n; j++) {
        len++;
        if(s[j] == '1')
            ones++;
        if(ones >= minOnes) {
            res += f(j+1, len, ones);
            res %= MOD;
        }
    }

    F[entry] = res;
    return res;
}

int main()
{
    cin >> n;
    cin >> s;

    vOnes[0] = 0;
    for(u32 i = 1; i <= n; i++) {
        vOnes[i] = vOnes[i-1] + (s[i-1] == '1') ? 1 : 0;
    }

    cout << f(0, 1, 0) << endl;
}