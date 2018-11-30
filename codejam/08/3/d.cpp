#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cassert>

static const int64_t M = 10007;

using namespace std;

struct P
{
    int64_t x, y;
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

int64_t powMod(int64_t x, int64_t n)
{
    int64_t res = 1;
    int64_t b = 1LL << (sizeof(int64_t)*8LL-2LL);
    while(b != 0)
    {
        res = (res * res) % M;
        if(b & n)
            res = (res * x) % M;
        b >>= 1LL;
    }
    return res;
}

int64_t binCoef(int64_t k, int64_t n)
{
    int64_t me = 0; // number of times you can divide k! by M
    int64_t pm = M;
    while(pm <= k)
    {
        me += k / pm;
        pm *= M;
    }

    int64_t used = 0;
    int64_t a = 1;  // numerator
    for(int64_t i=n-k+1; i<=n; i++)
    {
        int64_t ii=i;
        while(used < me && ii % M == 0) {
            ii /= M;
            used++;
        }
        a = (a*ii) % M;
    }

    int64_t b = 1;  // denominator
    for(int64_t i=1; i<=k; i++)
    {
        int64_t ii=i;
        while(ii % M == 0) {
            ii /= M;
        }
        b = (b*ii) % M;
    }

    // invert b
    b = powMod(b, M-2);

    return (a*b) % M;
}

int64_t esol(P p)
{
    return binCoef(p.x, p.x + p.y);
}

class Solver
{
public:
    Solver(int64_t W, int64_t H, vector<P>&& rocks)
        : W(W), H(H), rocks(std::move(rocks))
    {
        for(const P& r : this->rocks)
            br.insert(r);
    }

    int64_t solve() { return solve(W, H); }

    int64_t solve(int64_t X, int64_t Y)
    {
        if(X < 0 || Y < 0)
            return 0;
        if(X == 0 && Y == 0)
            return 1;
        
        int64_t res =  esol({X, Y});
        struct SW { P r; int64_t val; };
        vector<SW> layer;
        for(const P& r : rocks)
        {
            int64_t val = esol({r.x, r.y}) * esol({X-r.x, Y-r.y}) % M;
            res = (M + res - val) % M;
            layer.push_back({r, esol({r.x, r.y})});
        }
        int64_t sign = +1;
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
                        int64_t val = (sw.val * esol({r.x - sw.r.x, r.y - sw.r.y})) % M;
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
    int64_t W, H;
    vector<P> rocks;
    unordered_set<P> br;
};

int main()
{
    int64_t nn;
    cin >> nn;
    for(int64_t kk=1; kk<=nn; kk++)
    {
        int64_t W, H, R;
        cin >> H >> W >> R;

        W--; H--;
        int64_t RW = (2*W - H) / 3;
        int64_t RH = (2*H - W) / 3;
        bool impossible = RW < 0 || RH < 0 || (2*W-H) % 3 != 0;
        
        vector<P> rocks;
        for(int64_t i=0; i<R; i++)
        {
            int64_t y, x;
            cin >> y >> x;
            x--; y--;
            int64_t rx = (2*x - y) / 3;
            int64_t ry = (2*y - x) / 3;
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