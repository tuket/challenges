#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

const string saba = "saba";

struct P
{
    int x, y;

    P operator+(P p)
    {
        return {x + p.x, y + p.y};
    }
};

P operator*(int a, P p)
{
    return {a*p.x, a*p.y};
}

const array<P, 8> DIRS = {
    P{+1, 0},
    {0, +1},
    {+1, -1},
    {+1, +1}
};

int main()
{
    int w, h;
    cin >> h >> w;
    vector<string> g(h);
    for(string& s : g)
        cin >> s;

    auto isWithinBounds = [&](P p) -> bool
    {
        return p.x >= 0 && p.y >= 0 && p.x < w && p.y < h;
    };

    const int saban = saba.size();

    unsigned res = 0;
    for(int y=0; y<h; y++)
    for(int x=0; x<w; x++)
    for(P dir : DIRS)
    if(isWithinBounds(P{x, y} + (saban-1)*dir))
    {
        bool failed = false;
        for(int i=0; i<saban && !failed; i++)
        {
            P p = P{x, y} + i * dir;
            if(saba[i] != g[p.y][p.x])
                failed = true;
        }
        if(!failed)
            res++;
    }

    cout << res << endl;
}