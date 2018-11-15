#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static const int M = 10007;

struct P
{
    int x, y;
    bool operator==(const P& p)const
        { return x == p.y && y == p.y; }
};

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

using namespace std;

int64_t esol(P p)
{
    if(p.x == 0 || p.y == 0)
        return 1;
    static unordered_map<P, int64_t> s;
    auto it = s.find(p);
    if(it != s.end()) {
        return it->second;
    }
    else {
        int64_t sol = esol({p.x-1, p.y}) + esol({p.x, p.y-1});
        sol %= M;
        s[p] = sol;
        return sol;
    }
}

class Solver
{
public:
    Solver(int W, int H, vector<P>&& rocks)
        : W(W), H(H), rocks(std::move(rocks))
    {}

    uint64_t solve() { return solve(W-1, H-1); }

    uint64_t solve(int x, int y)
    {
        if(x == 0 && y == 0)
            return 1;
        
        int ix = 0, iy = 0;
        unordered_set<P> br;
        for(const P& r : rocks)
        {
            // TODO
        }

        if(ix == 0 && iy == 0)
            return esol({x+1, y+1});
        
        int64_t res = 0;
        for(int xx=ix+1; ix<=x; xx++)
        if(!br.count({xx, iy-1}))
        {
            res = (res + solve(xx, iy-1)) % M;
        }
        for(int yy=iy+1; yy<=y; yy++)
        if(!br.count({ix-1, yy}))
        {
            res = (res + solve(ix-1, yy)) % M;
        }
        return res;
    }

private:
    int W, H;
    vector<P> rocks;
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int W, H, R;
        cin >> H >> W >> R;
        vector<P> rocks(R);
        for(int i=0; i<R; i++)
        {
            int y, x;
            cin >> y >> x;
            int rx = 0;
            while(x > 2*y) {
                rx++;
                x-=2;
                y-=1;
            }
            int ry = y;
            rocks[i] = {rx, ry};
        }
        int RW = 0;
        W--; H--;
        while(W > 2*H) {
            RW++;
            W-=2;
            H-=1;
        }
        if(2*H != W) {
            cout << "Case #" << kk << ": 0" << endl;
            continue;
        }
        int RH = H;

        Solver solver(RW, RH, move(rocks));
        int64_t res = solver.solve();
        cout << "Case #" << kk << ": " << res << endl;
    }
}