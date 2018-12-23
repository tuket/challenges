#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<int, 2> BW;

struct Rect {
    int x, y;
    int w, h;
};

void rombusIterate(int d, std::function<void(int xx, int yy)>& f)
{
    int xx = d;
    int yy = 0;
    while(xx != 0)
    {
        f(xx, yy);
        xx--;
        yy++;
    }
    while(yy != 0)
    {
        f(xx, yy);
        xx--;
        yy--;
    }
    while(xx != 0)
    {
        f(xx, yy);
        xx++;
        yy--;
    }
    while(yy != 0)
    {
        f(xx, yy);
        xx++;
        yy++;
    }
}

int nb(int n)
{
    int res = 0;
    while(n)
    {
        n >>= 1;
        res++;
    }
    return res;
}

BW operator+(BW a, BW b)
{
    BW bw = {a[0] + b[0], a[1] + b[1]};
    return bw;
}

BW operator-(BW a, BW b)
{
    BW bw = {a[0] - b[0], a[1] - b[1]};
    return bw;
}

int abs(BW bw)
{
    return abs(bw[0]-bw[1]);
}

struct Table
{
    Table(unsigned N) : N(N), v(N) {}

    bool isValid(int x, int y)const { return x >= 0 && x < N && y >= 0 && y < N; }
    bool isValid(int x, int y, int w, int h)
        { return x >= 0 && y >= 0 && x+w-1 < N && y+h-1 < N; }

    int& operator()(int x, int y) { return v[x+N*y]; }
    BW operator()(int x, int y, int w, int h);
    BW operator()(int x, int w, int h);

    void use(int x, int y);
    void precomp();
    int index(int x, int y) { return x + N*y; }

    void iterate(std::function<bool(vector<int>& v, vector<float>& F, vector<int>& used, int x, int y)> f);
    void iterate(Rect rect, std::function<bool(vector<int>& v, vector<float>& F, vector<int>& used, int x, int y)> f);

    unsigned N;
    vector<int> v;

    vector<float> F;
    vector<vector<vector<BW>>> g;
    vector<int> used;

    constexpr int D = 10;
    constexpr float e = 0.8f;
};

void Table::use(int x, int y)
{
    const ind = index(x, y);
    if(used[ind)
        return;
    used[ind] = true;
    float v = F[ind];
    F[ind] = 0;

    float w = e;
    for(int d = 1; d < D; d++)
    {
        rombusIterate(d, [&](int xx, int yy)
        {
            const int ind = index(x+xx, y+yy);
            F[ind] -= w * v;
        });
        w *= e;
    }
}

void Table::precomp()
{
    used.resize(N*N);
    for(int& b : used)
        b = false;

    // F
    for(int y=0; y<N; y++)
    for(int x=0; x<N; x++)
    {
        float w = e;
        float val = operator()(x, y);
        for(int d=1; d<=D; d++)
        {
            float v = 0;
            rombusIt(d, [&](int xx, int yy)
            {
                if(isValid(x+xx, y+yy))
                    v += operator(x+xx, y+yy);
            });
            val += w * v;
            w *= e;
        }
    }

    // g
    int nl = nb(N);
    g.resize(nl);
    int c = N;
    g[0].resize(c);
    for(int y=0; y<N; y++)
    {
        g[0][y].resize(N+1);
        g[0][y][0] = {0, 0};
        for(int x=0; x < N; x++)
        {
            g[0][y][x+1] = g[0][y][x];
            g[0][y][x+1][operator()(x, y)]++;
        }
    }
    for(int l=1; l<nl; l++)
    {
        c >>= 1;
        g[l].resize(c);
        for(int i=0; i<c; i++)
        {
            g[l][i].resize(N+1);
            for(int x=0; x < N; x++)
            {
                g[l][i][x] = g[l-1][2*i][x] + g[l-1][2*i+1][x];
            }
        }
    }
}

BW Table::operator()(int x, int y, int w, int h)
{
    return operator()(x, w, y+h) - operator()(x, w, y);
}

BW Table::operator()(int x, int w, int h)
{
    BW bw {0, 0};
    if(h == 0)
        return bw;
    
    int c = h;
    int l = 0;
    while(c)
    {
        if(c & 1)
        {
            auto& gy = g[l][c-1];
            bw = bw + (gy[x+w] - gy[x]);
        }
        c >>= 1;
        l++;
    }
    return bw;
}

void Table::iterate(std::function<bool(vector<int>& v, vector<float>& F, vector<int>& used, int x, int y)> f)
{
    for(int y=0; y<N; y++)
    for(int x=0; x<N; x++)
    if(!f(v, F, used, x, y))
        break;
}

void Table::iterate(Rect r, std::function<bool(vector<int>& v, vector<float>& F, vector<int>& used, int x, int y)> f)
{
    for(int yy=0; yy<r.h; yy++)
    for(int xx=0; xx<r.w; xx++)
    if(!f(v, F, used, r.x+xx, r.y+yy))
        break;
}

int main()
{
    int n;
    cin >> n;
    Table t(n, n);
    for(int y=0; y<n; y++)
    for(int x=0; x<n; x++)
    {
        cin >> t(x, y);
    }
    t.precomp();

    vector<Rect> result;
    unordered_set<pair<int, int>> usedShapes;
    while(true)
    {
        int lowestCell = -1, greatestCell;
        float lowestVal = 0, greatestVal = 0;
        t.iterate([&](vector<int>& v, vector<float>& F, vector<int>& used, int x, int y)
        {
            const int ind = t.index(x, y);
            if(used[ind])
                return;
            const float val = F[ind];
            if(val < lowestVal)
            {
                lowestCell = ind;
                lowestVal = val;
            }
            if(val > greatestVal)
            {
                greatestCell = ind;
                greatestVal = val;
            }
            return true;
        });

        int startCell = greatestVal > -lowestVal ? greatestCell : lowestCell;
        if(startCell == -1)
            break;

        Rect rect{startCell % N, startCell / N, 1, 1};

        while(true) // try to grow the rectangle
        {
            // left?
            float leftScore = 0;
            if(rect.x >= 1)
            {
                t.iterate(Rect{rect.x-1, rect.y, 1, rect.h},
                [&](vector<int>& v, vector<float>& F, vector<int>& used, int x, int y)
                {
                    const int ind = index(x, y);
                    if(used[ind])
                    {
                        leftScore = 0;
                        return false;
                    }
                    leftScore += 
                    return true;
                });
            }

            // right?

            // up?

            // down?
        }
    }
}