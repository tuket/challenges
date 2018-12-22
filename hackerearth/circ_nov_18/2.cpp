#include <iostream>
#include <string>
#include <array>
#include <vector>

using namespace std;

const int NA = 26;
typedef array<int, NA> A;

A operator+(const A& a, const A& b)
{
    A res;
    for(int i=0; i<NA; i++)
        res[i] = a[i] + b[i];
    return res;
}

A operator-(const A& a, const A& b)
{
    A res;
    for(int i=0; i<NA; i++)
        res[i] = a[i] - b[i];
    return res;
}

void setZero(A& a)
{
    for(auto& x : a)
        x = 0;
}

int ctoi(char c)
{
    return c - 'a';
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<A> v(n+1);
        setZero(v[0]);
        for(int i=0; i<n; i++)
        {
            v[i+1] = v[i];
            v[i+1][ctoi(s[i])]++;
        }

        int res = [&]() {
            for(int sn = n; sn >= 3; sn--)
            {
                const int sn2 = sn/2;
                for(int i=0; i<=n-sn;)
                {
                    A a = v[i+sn] - v[i];
                    int mx = 1;
                    for(int x : a)
                        mx = max(mx, x);
                    if(mx >= sn2)
                        return sn;
                    i += (sn2 - mx);
                }
            }
            return 2;
        }();

        cout << res << endl;
    }
}