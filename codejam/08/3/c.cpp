#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <functional>

using namespace std;

struct Pos { int x, y;
    bool operator<(const Pos& o)const {
        return x < o.x ? true :
               x > o.x ? false :
               y < o.y;
    }
};

struct Table
{
    void resize(int W, int H)
    {
        this->W = W;
        this->H = H;
        d.resize(W*H);
    }
    void fill(char v)
    {
        std::fill(d.begin(), d.end(), v);
    }
    char& operator()(int x, int y)
    {
        return d[x + W*y];
    }
    vector<char> d;
    int W, H;
};
Table t;
int H, W;

template <typename T>
void sort(T& a, T& b) {
    if(a > b) swap(a, b);
}

struct Edge
{
    int a, b;
    Edge(int a, int b)
    {
        sort(a, b);
        this->a = a;
        this->b = b;
    }
    bool operator<(const Edge& o) const
    {
        return
            a < o.a ? true :
            a > o.a ? false :
            b < o.b;
    }
};

class BipGraph
{
public:
    void addVertLeft(int p) { v[0].insert(p); }
    void addVertRight(int p) { v[1].insert(p); }
    void addEdge(int a, int b)
    {
        v[0].insert(a);
        v[1].insert(b);
        c.insert({a, b});
        c.insert({b, a});
    }

    unsigned getNumVerts()const
    {
        return v[0].size() + v[1].size();
    }

    void clear()
    {
        v[0].clear();
        v[1].clear();
        c.clear();
    }

    set<Edge> hopcroftKarp()
    {
        set<Edge> M;
        set<int> m;
        while(true)
        {
            vector<set<int>> L = {{}};
            set<int> visited;
            for(int p : v[0])
            if(!m.count(p)) {
                visited.insert(p);
                L[0].insert(p);
            }
            // BFS
            int k = 0;
            while(true)
            {
                int nk = k+1;
                L.push_back({});
                for(int a : L[k])
                {
                    auto range = c.equal_range(a);
                    for(auto it = range.first; it != range.second; ++it)
                    {
                        int b = it->second;
                        if(visited.count(b))
                            continue;
                        if(k%2 != M.count({a, b}))
                            continue;
                        L[nk].insert(b);
                        visited.insert(b);
                    }
                }
                k = nk;
                if(L[k].empty())
                    break;
                bool end = false;
                for(int p : L[k])
                if(v[1].count(p) && !m.count(p)) {
                    end = true;
                    break;
                }
                if(end)
                    break;
            }
            
            // run until we can't find more augmenting paths
            if(L.back().empty())
                break;

            // the last layer must only include free verts
            vector<int> toRemove;
            for(int p : L.back())
            if(m.count(p))
                toRemove.push_back(p);
            for(int p : toRemove)
                L.back().erase(p);

            // DFS paths
            vector<vector<int>> AP; // augmenting paths
            visited.clear();
            for(int p : L[0])
            {
                vector<int> path;
                vector<function<bool()>> stack;
                function<bool(int)> sf = [&](int a) 
                {
                    const int k = path.size();
                    const bool hasToBeMatching = k % 2 == 1;
                    path.push_back(a);
                    visited.insert(a);
                    if(k == L.size()-1)
                        return true;
                    auto range = c.equal_range(a);
                    for(auto it = range.first; it != range.second; ++it)
                    {
                        const int b = it->second;
                        if(!L[k+1].count(b))
                            continue;
                        if(visited.count(b))
                            continue;
                        bool isMatching = M.count({a, b});
                        if(hasToBeMatching != isMatching)
                            continue;
                        stack.push_back([&path, &visited, a]{
                            path.pop_back();
                            visited.erase(a);
                            return false;
                        });
                        stack.push_back(bind(sf, b));
                    }
                    return false;
                };
                stack.push_back(bind(sf, p));
                bool found = false;
                while(!stack.empty() && !found)
                {
                    function<bool()> f = stack.back();
                    stack.pop_back();
                    if(f())
                        found = true;
                }
                if(found)
                    AP.push_back(path);
            }

            // flip aumenting paths
            for(const auto& path : AP)
            {
                for(int i=0; i<path.size()-1; i++)
                {
                    const int a = path[i];
                    const int b = path[i+1];
                    if(i % 2 == 0)
                        M.insert({a, b});
                    else
                        M.erase({a, b});
                }
                m.insert(path[0]);
                m.insert(path.back());
            }
        }

        return M;
    }
private:
    set<int> v[2];
    multimap<int, int> c;
}
g;

int solve()
{
    g.clear();
    for(int y=0; y<H; y+=1)
    for(int x=1; x<W; x+=2)
    if(t(x, y) == '.')
    {
        int b = x + W*y;
        g.addVertRight(b);
    }

    for(int y=0; y<H; y+=1)
    for(int x=0; x<W; x+=2)
    if(t(x, y) == '.')
    {
        int a = x + W*y;
        g.addVertLeft(a);
        for(int yy=-1; yy<=+1; yy+=1)
        for(int xx=-1; xx<=+1; xx+=2)
        {
            int x2 = x+xx;
            int y2 = y+yy;
            if(x2 < 0 || x2 >= W || y2 < 0 || y2 >= H)
                continue;
            int b = x2 + W*y2;
            if(t(x2, y2) == '.')
            {
                g.addEdge(a, b);
            }
        }
    }
    auto M = g.hopcroftKarp();
    return g.getNumVerts() - M.size();
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        cin >> H >> W;
        t.resize(W, H);
        string s;
        getline(cin, s);
        for(int y=0; y<H; y++)
        {
            getline(cin, s);
            for(int x=0; x<W; x++)
            {
                t(x, y) = s[x];
            }
        }
        int res = solve();
        cout << "Case #" << kk << ": " << res << endl;
    }
}