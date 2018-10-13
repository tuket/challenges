#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

struct Pos { int x, y; };

template <typename T>
struct Table
{
    Table(){}
    Table(int w, int h) { resize(w, h); }
    void resize(int w, int h)
    {
        W = w;
        H = h;
        d.resize(w*h);
    }
    void fill(const T& t) { fill(d.begin(), d.end(), t); }

    T& operator()(int x, int y) {
        return d[x + W*y];
    }
    const T& operator()(int x, int y)const {
        return d[x + W*y];
    }
    bool isWall(Pos p)const {
        if(p.x < 0 || p.y < 0 || p.x >= W || p.y >= H)
            return true;
        return operator()(p.x, p.y) == '#';
    }

    vector<T> d;
    int W, H;
};

struct DP
{
    void clean()
    {
        for(int y=0; y<16; y++)
        for(int x=0; x<16; x++)
        for(int py=0; py<16; py++)
        for(int px=0; px<16; px++)
            d[y][x][py][px] = numeric_limits<int>::max();
    }
    bool set(Pos o, Pos p, int val) {
        int& v = d[o.y][o.x][p.y][p.x];
        if(v <= val)
            return false;
        v = val;
        return true;
    }
    int get(Pos o, Pos p)const {
        return d[o.y][o.x][p.y][p.x];
    }
    int d[16][16][16][16];
};

int H, W;

Table<char> g;
Pos initPos;
Pos cakePos;
DP dp;

void getNewPortals(const Pos& o,
    Pos& pLeft, Pos& pRight, Pos& pUp, Pos& pDown)
{
    pLeft.y = pRight.y = o.y;
    pUp.x = pDown.x = o.x;
    int x, y;
    y = o.y;
    for(x=o.x; x>=0; x--) {
        if(g(x, y) == '#')
            break;
    }
    pLeft.x = x+1;
    for(x=o.x; x<W; x++) {
        if(g(x, y) == '#')
            break;
    }
    pRight.x = x-1;
    x = o.x;
    for(y=o.y; y>=0; y--) {
        if(g(x, y) == '#')
            break;
    }
    pDown.y = y+1;
    for(y=o.y; y<H; y++) {
        if(g(x, y) == '#')
            break;
    }
    pUp.y = y-1;
}

int solve()
{
    dp.clean();
    Pos o = initPos;
    Pos p[4];
    getNewPortals(o, p[0], p[1], p[2], p[3]);
    for(int i=0; i<4; i++)
        dp.set(o, p[i], 0);
    struct PP{Pos o, p;};
    queue<PP> q;
    for(int i=0; i<4; i++)
        q.push({o, p[i]});
    while(!q.empty())
    {
        PP pp = q.front();
        q.pop();
        int val = dp.get(pp.o, pp.p);
        auto move = [&](Pos o)
        {
            if(g.isWall(o)) {
                o = pp.p;
            }
            if(dp.set(o, pp.p, val+1))
                q.push({o, pp.p});
            Pos p[4];
            getNewPortals(o, p[0], p[1], p[2], p[3]);
            for(int i=0; i<4; i++) {
                if(dp.set(o, p[i], val+1))
                    q.push({o, p[i]});
            }
        };
        int x = pp.o.x;
        int y = pp.o.y;
        if(x == cakePos.x && y == cakePos.y)
            return val;
        move({x-1, y});
        move({x+1, y});
        move({x, y-1});
        move({x, y+1});
    }
    return -1;
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
                if(s[x] == 'O')
                    initPos = {x, y};
                else if(s[x] == 'X')
                    cakePos = {x, y};
                g(x, y) = s[x];
            }
        }
        int res = solve();
        cout << "Case #" << kk << ": ";
        if(res == -1)
            cout << "THE CAKE IS A LIE" << endl;
        else
            cout << res << endl;
        
    }
}