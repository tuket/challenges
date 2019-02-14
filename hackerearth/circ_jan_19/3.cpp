#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <limits>
#include <unordered_set>

using namespace std;

constexpr int MAX = numeric_limits<int>::max();

struct P
{
    int a, b;
    bool operator==(const P& o)const
    {
        return a == o.a && b == o.b;
    }
};

namespace std
{
    template <>
    struct hash<P>
    {
        size_t operator()(const P& p)const
        {
            size_t a = p.a;
            size_t b = p.b;
            return (a << 16) | b;
        }
    };
}

vector<int> s;
int K;
int n;

vector<vector<int>> G;
vector<int> cache;

void initCache()
{
    cache.resize(n*n);
    vector<int> cc(26 * (n+1), 0);
    for(int i=0; i<n; i++)
    {
        char c = s[i];
        for(int ic=0; ic<26; ic++)
        {
            cc[26*(i+1) + ic] = cc[26*i + ic] + (26 + ic - c) % 26;
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; i+j<n; j++)
        {
            int l = s[i+j];
            int best = MAX;
            for(char c=0; c<26; c++)
            {
                int res = cc[26*(i+j+1) + c] - cc[26*i + c];
                best = min(best, res);
            }
            cache[i*n + j] = best;
        }
    }
}

int reqChanges(int beg, int end)
{
    int cv = cache[n*beg + (end-beg-1)];
    return cv;
}

int main()
{
    string str;
    cin >> str;
    n = str.size();
    s = vector<int>(n);
    for(int i=0; i<n; i++)
        s[i] = str[i] - 'a';
    cin >> K;

    initCache();

    G.resize(n+1);
    for(int i=0; i<=n; i++)
    {
        G[i] = vector<int>(K+2, MAX);
    }
    G[0][0] = 0;

    for(int i=0; i<n; i++)
    {
        int lg = MAX;
        for(int k=0; k<=K; k++)
        {
            int g = G[i][k];
            if(g >= lg)
                continue;
            lg = g;
            for(int j=i+1; j<=n; j++)
            {
                int& ng = G[j][k+1];
                int ex = g + reqChanges(i, j);
                ng = min(ng, ex);
            }
        }
    }
    
    int lowChanges = G[n][0];
    for(int k = 1; k<=K+1; k++)
    {
        lowChanges = min(lowChanges, G[n][k]);
    }

    cout << lowChanges << endl;
}