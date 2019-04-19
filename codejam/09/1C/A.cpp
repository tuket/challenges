#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        string s;
        cin >> s;
        array<int64_t, 256> B;
        fill(B.begin(), B.end(), -1);
        vector<int64_t> v;
        v.reserve(s.size());
        B[s[0]] = 1;
        v.push_back(1);
        int i;
        for(i=1; i<s.size() && B[s[i]] == 1LL; i++)
        {
            v.push_back(1LL);
        }
        int64_t b = 2;
        if(i < s.size())
        {
            B[s[i]] = 0;
            v.push_back(0);
            for(i++; i<s.size(); i++)
            {
                char c = s[i];
                if(B[c] == -1) {
                    B[c] = b;
                    b++;
                }
                v.push_back(B[c]);
            }
        }
        int64_t res = 0;
        for(int64_t x : v)
        {
            res *= b;
            res += x;
        }
        cout << "Case #" << kk << ": " << res << endl;
    }
}