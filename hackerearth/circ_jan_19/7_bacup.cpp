#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef int32_t ll;

int N, Q;
vector<vector<int>> ch;
vector<int> pa;
vector<vector<int>> dl;
vector<ll> tot;
vector<int> de;
vector<array<int, 2>> queries;

int dist(int a, int b)
{
    int res = 0;
    while(de[a] > de[b])
    {
        a = pa[a];
        res++;
    }
    while(de[b] > de[a])
    {
        b = pa[b];
        res++;
    }
    while(a != b)
    {
        a = pa[a];
        b = pa[b];
        res += 2;
    }
    return res;
}

int main()
{
    cin >> N >> Q;
    ch.resize(N);
    dl.resize(N);
    de.resize(N);
    tot.resize(N, 0);
    pa = vector<int>(N, -1);
    for(int i=0; i<N-1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ch[a].push_back(b);
        ch[b].push_back(a);
    }

    queries.resize(Q);
    for(int i=0; i<Q; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        queries[i][0] = a;
        queries[i][1] = b;
    }

    vector<int> q = {-1, 0};
    while(q.size())
    {
        int a = q.back();
        q.pop_back();
        int ap = q.back();
        q.pop_back();
        pa[a] = ap;
        
        for(int b : ch[a])
        if(b != ap)
        {
            q.push_back(a);
            q.push_back(b);
        }
    }

    for(int i=0; i<N; i++)
    {
        for(auto it=ch[i].begin(); it != ch[i].end(); ++it)
        if(*it == pa[i])
        {
            ch[i].erase(it);
            break;
        }
    }

    // depth levels
    q.push_back(-1);
    while(q.size())
    {
        int a = q.back();
        q.pop_back();
        if(a < 0)
        {
            a = -a-1;
            q.push_back(a);
            for(int b : ch[a])
            {
                q.push_back(-b-1);
            }
        }
        else
        {
            int size = 1;
            for(int b : ch[a])
                size = max(size, (int)dl[b].size()+1);
            dl[a] = vector<int>(size, 0);
            dl[a][0] = 1;
            dl[a][1] = ch[a].size();
            for(int b : ch[a])
                for(int i = 1; i < dl[b].size(); i++)
                    dl[a][i+1] += dl[b][i];
        }
    }

    // depth
    q.push_back(0);
    de[0] = 0;
    while(q.size())
    {
        int a = q.back();
        q.pop_back();
        for(int b : ch[a])
        {
            de[b] = de[a] + 1;
            q.push_back(b);
        }
    }

    q.push_back(-1);
    while(q.size())
    {
        int a = q.back();
        q.pop_back();
        if(a < 0)
        {
            a = -a-1;
            for(int b : ch[a])
            {
                q.push_back(-b-1);
            }
        }
        else
        {
            ll& res = tot[a];
            for(int i=0; i<ch[a].size(); i++)
            {
                int b1 = ch[a][i];
                res += tot[b1];
                for(int di=0; di<dl[b1].size(); di++)
                {
                    res += (ll)(di+1) * dl[b1][di];
                }
                for(int j=i+1; j<ch[a].size(); j++)
                {
                    int b2 = ch[a][j];
                    for(int di=0; di<dl[b1].size(); di++)
                    {
                        for(int dj=0; dj<dl[b2].size(); dj++)
                        {
                            ll d1 = dl[b1][di];
                            ll d2 = dl[b2][dj];
                            res += (di+dj+2) * d1 * d2;
                        }
                    }
                }
            }
        }
    }
    /*for(int i=0; i<N; i++)
    for(int j=i+1; j<N; j++)
    {
        int d = dist(i, j);
        tot += d;
    }*/

    // queries
    for(const auto& eq : queries)
    {
        ll res = 0;
        /*for(int i=0; i<N; i++)
        {
            for(int j=i+1; j<N; j++)
            {
                int d = dist(i, j);
                int sd1 = dist(i, eq[0]) + dist(j, eq[1]);
                int sd2 = dist(i, eq[1]) + dist(j, eq[0]);
                d = min(d, min(sd1, sd2)+1);
                res += d;
            }
        }*/
        cout << res << endl;
    }
}