#include <iostream>
#include <vector>
#include <map>
#include <set>

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
Table g;
int H, W;

void printG()
{
    for(int y=0; y<H; y++)
    {
        for(int x=0; x<W; x++)
        {
            cout << g(x, y);
        }
        cout << endl;
    }
}

int solve()
{
    map<int, set<Pos>> m;
    map<Pos, int> v;
    for(int y=0; y<H; y++)
    for(int x=0; x<W; x++)
    if(g(x, y) == '.')
    {
        int pr = 0;
        for(int xx=-1; xx<=+1; xx+=2)
        if(x+xx >= 0 && x+xx < W)
        {
            for(int yy=-1; yy<=1; yy++)
            if(y+yy >= 0 && y+yy < H)
            if(g(x+xx, y+yy) == '.')
            {
                pr++;
            }
        }
        auto it = m.find(pr);
        if(it == m.end()) {
            m[pr] = set<Pos>();
            it = m.find(pr);
        }
        it->second.insert({x, y});
        v[{x, y}] = pr;
    }

    int res = 0;
    auto pdel = [&](int x, int y)
    {
        if(v.count({x, y}) == 0)
            return;
        int pr = v.find({x, y})->second;
        v.erase({x, y});
        m[pr].erase({x, y});
        if(m[pr].empty())
            m.erase(pr);
        for(int xx=-1; xx<=+1; xx+=2)
        if(x+xx >= 0 && x+xx < W)
        for(int yy=-1; yy<=+1; yy++)
        if(y+yy >= 0 && y+yy < H)
        {
            Pos pos{x+xx, y+yy};
            auto it = v.find(pos);
            if(it != v.end())
            {
                int pr = it->second;
                it->second--;
                m[pr].erase(pos);
                m[pr-1].insert(pos);
                if(m[pr].empty())
                    m.erase(pr);
            }
        }
    };
    while(!m.empty())
    {
        auto mIt = m.begin();
        auto sIt = mIt->second.begin();
        Pos pos = *sIt;
        int x = pos.x, y = pos.y;
        g(x, y) = '*';
        cout << endl;
        printG();
        mIt->second.erase(sIt);
        if(mIt->second.empty())
            m.erase(mIt);
        v.erase(pos);
        res++;
        for(int xx=-1; xx<=+1; xx+=2)
        if(x+xx >= 0 && x+xx < W)
        for(int yy=-1; yy<=+1; yy++)
        if(y+yy >= 0 && y+yy < H)
        {
            pdel(x+xx, y+yy);
        }
    }
    return res;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        cin >> H >> W;
        g.resize(W, H);
        string s;
        getline(cin, s);
        for(int y=0; y<H; y++)
        {
            getline(cin, s);
            for(int x=0; x<W; x++)
            {
                g(x, y) = s[x];
            }
        }
        int res = solve();
        printG();
        cout << "Case #" << kk << ": " << res << endl;
    }
}