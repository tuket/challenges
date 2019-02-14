#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<bool, 26> AB;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        AB ab;
        AB a;
        for(bool& b : ab)
            b = true;
        for(int i=0; i<n; i++)
        {
            for(bool& b : a)
                b = false;
            string s;
            cin >> s;
            for(char c : s)
            {
                a[c-'a'] = true;
            }
            for(char c=0; c<26; c++)
                ab[c] &= a[c];
        }
        int res = 0;
        for(char c=0; c<26; c++)
        {
            if(ab[c])
                res++;
        }
        cout << res << endl;
    }
}