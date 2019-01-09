#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef unsigned long long ull;
ull W, H;

struct Z
{
    ull vert;
    ull hori;
    ull peri;
};

struct P
{
    int x, y;
};

Z g[21][21];
ull v[42][42];

void initV()
{
    for(int y=0; y<42; y++)
    for(int x=0; x<42; x++)
    {
        v[y][x] = numeric_limits<ull>::max();
    }
}

bool isWithinBoundaries(P p)
{
    return p.x > 0 && p.y > 0 && p.x <= 2*W && p.y <= 2*H;
};

ull timeHori(int x, int y, ull t)
{
    x = (x-1) / 2;
    y = (y-1) / 2;
    const ull cv = g[y][x].hori;
    const ull ch = g[y][x].vert;
    const ull tt = g[y][x].peri;
    const ull c = cv + ch;
    t = (t - tt + c) % c;
    if(t < ch)
        return ch - t;
    else
        return 0;
}

ull timeVert(int x, int y, ull t)
{
    x = (x-1) / 2;
    y = (y-1) / 2;
    const ull cv = g[y][x].hori;
    const ull ch = g[y][x].vert;
    const ull tt = g[y][x].peri;
    const ull c = cv + ch;
    t = (t - tt + c) % c;
    if(t < ch)
        return 0;
    else
        return c - t;
}

int main()
{
    unsigned nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        cin >> H >> W;
        for(ull y=0; y<H; y++)
        {
            for(ull x=0; x<W; x++)
            {
                auto& gg = g[H-y-1][x];
                cin >> gg.vert;
                cin >> gg.hori;
                cin >> gg.peri;
                const ull c = gg.vert + gg.hori;
                while(gg.peri >= c)
                    gg.peri -= c;
            }
        }

        initV();

        v[1][1] = 0;
        vector<P> q = {{1, 1}};

        auto pushIfBetter = [&](P p, ull nt)
        {
            if(nt < v[p.y][p.x])
            {
                v[p.y][p.x] = nt;
                q.push_back(p);
            }
        };

        auto doStep = [&](P p)
        {
            const ull t = v[p.y][p.x];
            // move left
            P np = {p.x-1, p.y};
            if(isWithinBoundaries(np))
            {
                ull nt = t;
                if(p.x % 2 == 1)
                    nt += 2;
                else
                    nt += timeHori(p.x, p.y, t) + 1;
                pushIfBetter(np, nt);
            }

            // move right
            np = {p.x+1, p.y};
            if(isWithinBoundaries(np))
            {
                ull nt = t;
                if(p.x % 2 == 0)
                    nt += 2;
                else
                    nt += timeHori(p.x, p.y, t) + 1;
                pushIfBetter(np, nt);
            }

            // move down
            np = {p.x, p.y-1};
            if(isWithinBoundaries(np))
            {
                ull nt = t;
                if(p.y % 2 == 1)
                    nt += 2;
                else
                    nt += timeVert(p.x, p.y, t) + 1;
                pushIfBetter(np, nt);
            }

            // move up
            np = {p.x, p.y+1};
            if(isWithinBoundaries(np))
            {
                ull nt = t;
                if(p.y % 2 == 0)
                    nt += 2;
                else
                    nt += timeVert(p.x, p.y, t) + 1;
                pushIfBetter(np, nt);
            }
        };

        while(q.size())
        {
            P p = q.back();
            q.pop_back();
            doStep(p);
        }

        cout << "Case #" << kk << ": " << v[2*H][2*W] << endl;
    }
}