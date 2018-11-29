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
    bool operator!=(const P& p)const
        { return !operator==(p); }
    bool isParent(const P& p)const
        { return x <= p.x && y <= p.y; }
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

int powMod(unsigned x, unsigned n)
{
    unsigned res = 1;
    unsigned b = 1 << (sizeof(unsigned)*8-2);
    while(b != 0)
    {
        res = (res * res) % M;
        if(b & n)
            res = (res * x) % M;
        b >>= 1;
    }
    return res;
}

int binCoef(int k, int n)
{
    int me = 0; // number of times you can divide k! by M
    int pm = M;
    while(pm <= k)
    {
        me += k / pm;
        pm *= M;
    }

    int used = 0;
    int a = 1;  // numerator
    for(int i=n-k+1; i<=n; i++)
    {
        int ii=i;
        while(used < me && ii % M == 0) {
            ii /= M;
            used++;
        }
        a = (a*ii) % M;
    }

    int b = 1;  // denominator
    for(int i=1; i<=k; i++)
    {
        int ii=i;
        while(ii % M == 0) {
            ii /= M;
        }
        b = (b*ii) % M;;
    }

    // invert b
    b = powMod(b, M-2);

    return (a*b) % M;
}

int esol(P p)
{
    return binCoef(p.x, p.x + p.y);
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

    uint64_t solve() { return solve(W, H); }

    uint64_t solve(int X, int Y)
    {
        if(X < 0 || Y < 0)
            return 0;
        if(X == 0 && Y == 0)
            return 1;
        
        int res =  esol({X, Y});
        struct SW { P r; int val; };
        vector<SW> layer;
        for(const P& r : rocks)
        {
            int val = esol({r.x, r.y}) * esol({X-r.x, Y-r.y}) % M;
            res = (M + res - val) % M;
            layer.push_back({r, esol({r.x, r.y})});
        }
        int sign = +1;
        while(layer.size())
        {
            vector<SW> newLayer;
            for(const SW& sw : layer)
            {
                for(const P& r : rocks)
                if(sw.r != r)
                {
                    if(sw.r.isParent(r))
                    {
                        int val = (sw.val * esol({r.x - sw.r.x, r.y - sw.r.y})) % M;
                        res = (M + res + sign * (val * esol({X-r.x, Y-r.y}))%M) % M;
                        newLayer.push_back({r, val});
                    }
                }
            }
            sign *= -1;
            layer = newLayer;
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

        W--; H--;
        int RW = (2*W - H) / 3;
        int RH = (2*H - W) / 3;
        bool impossible = RW < 0 || RH < 0 || (2*W-H) % 3 != 0;
        
        vector<P> rocks;
        for(int i=0; i<R; i++)
        {
            int y, x;
            cin >> y >> x;
            x--; y--;
            int rx = (2*x - y) / 3;
            int ry = (2*y - x) / 3;
            if (rx >= 0 && ry >= 0 && rx <= RW && ry <= RH && (2*x-y) % 3 == 0)
            {
                rocks.push_back({rx, ry});
            }
        }
        
        if(impossible) {
            cout << "Case #" << kk << ": 0" << endl;
        }
        else {
            Solver solver(RW, RH, move(rocks));
            int64_t res = solver.solve();
            cout << "Case #" << kk << ": " << res << endl;
        }
        
    }
}