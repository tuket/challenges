#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cassert>

static const int M = 10007;

using namespace std;

struct P
{
    int x, y;
    bool operator==(const P& p)const
        { return x == p.x && y == p.y; }
};

P sort(P p) {
    return {min(p.x, p.y), max(p.x, p.y)};
}

namespace std
{
    template <>
    struct hash<P>
    {
        std::size_t operator()(const P& p)const
        {
            std::size_t res = p.x;
            res <<= sizeof(size_t)*4;
            res |= p.y;
            return res;
        }
    };
}

vector<int> precomp()
{
    vector<int> s(M*M, 1);
    for(int y=1; y<M; y++)
    for(int x=1; x<M; x++)
    {
        s[M*y+x] = (s[M*y+x-1] + s[M*(y-1)+x]) % M;
    }
    return s;
}

int esol(P p)
{
    p.x %= M;
    p.y %= M;
    const uint i = p.y*M + p.x;
    static vector<int> s = precomp();
    return s[i];
}

class Solver
{
public:
    Solver(int W, int H, vector<P>&& rocks)
        : W(W), H(H), rocks(std::move(rocks))
    {
        for(const P& r : this->rocks)
            br.insert(r);
    }

    uint64_t solve() { return solve(W-1, H-1); }

    uint64_t solve(int x, int y)
    {
        if(x < 0 || y < 0)
            return 0;
        if(x == 0 && y == 0)
            return 1;
        
        int ix = 0, iy = 0;
        for(const P& r : rocks)
        if(r.x == x)
        {
            if(r.y < y)
                iy = max(iy, r.y+1);
        }
        for(const P& r : rocks)
        if(r.y >= iy && r.y <= y && r.x < x)
        {
            ix = max(ix, r.x+1);
        }

        if(ix == 0 && iy == 0)
            return esol({x, y});
        
        int64_t res = 0;
        if(iy > 0)
        for(int xx=ix; xx<=x; xx++)
        if(!br.count({xx, iy-1}))
        {
            res = (res + solve(xx, iy-1) * esol({x-xx, y-iy})) % M;
        }
        if(ix > 0)
        for(int yy=iy; yy<=y; yy++)
        if(!br.count({ix-1, yy}))
        {
            res = (res + solve(ix-1, yy) * esol({x-ix, y-yy})) % M;
        }
        return res;
    }

private:
    int W, H;
    vector<P> rocks;
    unordered_set<P> br;
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int W, H, R;
        cin >> H >> W >> R;
        vector<P> rocks;
        for(int i=0; i<R; i++)
        {
            int y, x;
            cin >> y >> x;
            x--; y--;
            int rx = 0;
            while(2*x > y) {
                rx++;
                x-=2;
                y-=1;
            }
            if(x >= 0 && y >= 0 && 2*x == y) {
                int ry = x;
                rocks.push_back({rx, ry});
            }
        }
        int RW = 1;
        W--; H--;
        while(2*W > H) {
            RW++;
            W-=2;
            H-=1;
        }
        if(H != 2*W) {
            cout << "Case #" << kk << ": 0" << endl;
            continue;
        }
        int RH = W+1;

        Solver solver(RW, RH, move(rocks));
        int64_t res = solver.solve();
        cout << "Case #" << kk << ": " << res << endl;
    }
}