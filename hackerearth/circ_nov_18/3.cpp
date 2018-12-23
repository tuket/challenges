#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<int, 2> BW;

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
    Table(unsigned W, unsigned H) : W(W), H(H), v(W*H) {}

    int& operator()(int x, int y) { return v[x+W*y]; }
    BW operator()(int x, int y, int w, int h);
    BW operator()(int x, int w, int h);

    void precomp();

    unsigned W, H;
    vector<int> v;

    vector<vector<vector<BW>>> g;
};

void Table::precomp()
{
    int nl = nb(H);
    g.resize(nl);
    int c = H;
    g[0].resize(c);
    for(int y=0; y<H; y++)
    {
        g[0][y].resize(W+1);
        g[0][y][0] = {0, 0};
        for(int x=0; x < W; x++)
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
            g[l][i].resize(W+1);
            for(int x=0; x < W; x++)
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

    int bestSy = 0;
    int bestSx = 0;
    int bestVal = 0;
    for(int sy=0; sy < n; sy++)
    for(int sx=0; sx < n; sx++)
    if(sy != n-sy-2 || sx != n-sx-2)
    {
        int val =
            abs(t(0, 0, sx+1, sy+1)) +
            abs(t(sx+1, 0, n-sx-1, sy+1)) +
            abs(t(0, sy+1, sx+1, n-sy-1)) +
            abs(t(sx+1, sy+1, n-sx-1, n-sy-1));
        if(val > bestVal)
        {
            bestVal = val;
            bestSx = sx;
            bestSy = sy;
        }
    }

    cout << 4 << endl;
    cout << 1 << " " << 1 << " " << bestSx+1 << " " << bestSy+1 << endl;
    cout << bestSx+2 << " " << 1 << " " << n << " " << bestSy+1 << endl;
    cout << 1 << " " << bestSy+2 << " " << bestSx+1 << " " << n << endl;
    cout << bestSx+2 << " " << bestSy+2 << " " << n << " " << n << endl;
}