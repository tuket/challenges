#include <iostream>
#include <unordered_map>
#include <array>

using namespace std;

int M = 1000000000;

struct P
{
    int x, y;
    bool operator==(const P& p)const
    {
        return x == p.x && y == p.y;
    }
};

namespace std
{
template<>
struct hash<P>
{
    size_t operator()(const P& p)const
    {
        size_t res = p.x;
        res <<= 32;
        res |= p.y;
        return res;
    }
};
}

constexpr bool test = false;
inline int query(int x, int y)
{
    int q = 0;
    cout << "Q " << x << " " << y << endl;
    if(!test)
    {
        cin >> q;
    }
    else
    {
        int minX = 999999999;
        int minY = 999999999;
        int maxX = 999999999;
        int maxY = 999999999;
        if(y < minY)
            q += minY - y;
        else if(y > maxY)
            q += y - maxY;
        if(x < minX)
            q += minX - x;
        else if(x > maxX)
            q += x - maxX;
        cout << q << endl;
    }
    return q;
}

void solve()
{
    unordered_map<P, int> mq;
    auto Q = [&mq](int x, int y) -> int
    {
        const P p{x, y};
        auto it = mq.find(p);
        if(it != mq.end())
            return it->second;
        int q = query(x, y);
        mq[p] = q;
        return q;
    };

    // X1
    int x1=-1, y1=-1, x2=-1, y2=-1;

    [&]() -> void
    {
        int a = 0;
        int b = M;
        int x = (a + b) / 2;
        
        int fa = Q(a, 0);
        if(fa == 0)
        {
            x1 = 0;
            y1 = 0;
            x2 = M - Q(M, 0);
            y2 = M - Q(0, M);
            return;
        }
        int fb = Q(b, 0);
        if(fb == 0)
        {
            x1 = fa;
            y1 = 0;
            x2 = M;
            y2 = M - Q(M, M);
            return;
        }
        int fx = Q(x, 0);
        if(fx == 0)
        {
            x1 = fa;
            y1 = 0;
            x2 = M - fb;
            y2 = M - Q(x, M);
            return;
        }

        if(fa < fb)
        {
            b -= (fb-fa);
            x = (a+b) / 2;
            fx = Q(x, 0);
            fb = Q(b, 0);
        }
        else if(fb < fa)
        {
            a += (fa-fb);
            x = (a+b) / 2;
            fx = Q(x, 0);
            fa = Q(a, 0);
        }
        x1 = a + (fa - fx);
        y1 = fx;
        x2 = b - (fb - fx);
        y2 = M - Q(x, M);
    }();

    cout << "A "
        << x1 << " " << y1 << " "
        << x2 << " " << y2 << endl;
}

int main()
{
    int nn;
    if(!test)
        cin >> nn;
    else
        nn = 1;
    for(int kk=0; kk<nn; kk++)
    {
        solve();
        int correct;
        cin >> correct;
    }
}