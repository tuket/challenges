#include <bits/stdc++.h>

using namespace std;

typedef bitset<128> B;

void bs(B& b, int S)
{
    b = B();
    b = ~b;
    b <<= 128-S;
    b >>= 128-S;
}

int solve(const vector<int>& v, int S)
{
    int n = v.size();
    int res = 0;
    B b; bs(b, S);
    for(int i = 0; i < n; i++)
    {
        b.set(v[i], false);
        if(!b.any()) {
            res++;
            bs(b, S);
            b.set(v[i], false);
        }
    }

    return res;
}

int main()
{
    string garbage;
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int S;
        cin >> S;
        getline(cin, garbage);
        map<string, int> em;
        int e = 0;
        string es;
        for(int i=0; i<S; i++)
        {
            getline(cin, es);
            em[es] = e;
            e++;
        }

        vector<int> v;
        int Q;
        cin >> Q;
        getline(cin, garbage);
        for(int i=0; i<Q; i++)
        {
            getline(cin, es);
            v.push_back(em[es]);
        }

        cout << "Case #" << kk << ": " << solve(v, S) << endl;
    }
}