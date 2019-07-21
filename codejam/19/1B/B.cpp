#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

template <typename T>
string toString(const vector<T>& v, string sep = " ")
{
    if(v.size() == 0)
        return "";
    stringstream ss;
    for(size_t i=0; i<v.size()-1; i++)
    {
        ss << v[i] << sep;
    }
    ss << v.back() << endl;
    return ss.str();
}
// -------------------------------------------------------------------------

u64 M = 0x8000000000000000;

u64 add(u64 a, u64 b)
{
    return (a + b) & (~M);
}

u64 subs(u64 a, u64 b)
{
    return (M - b + a) & (~M);
}

u64 mul(u64 a, u64 b)
{
    return (a * b) & (~M);
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        u64 x1, x2;
        cout << 1 << endl;
        cin >> x1;
        cout << 383 << endl;
        cin >> x2;
        u64 R1 = ((M - x2) + x1) & (~M);
        
        cout << 2 << endl;
        u64 x3; cin >> x3;
        u64 R2 = subs(subs(x3, x1), mul(2, R1));
    }
}
