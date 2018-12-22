#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<int, 2> BW;

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

    void precomp();

    unsigned W, H;
    vector<int> v;

    vector<vector<BW>> g;
};

void Table::precomp()
{
    g.resize(H);
    for(int y=0; y<H; y++)
    {
        g[y].resize(W+1);
        g[y][0] = {0, 0};
        for(int x=0; x < W; x++)
        {
            g[y][x+1] = g[y][x];
            g[y][x+1][operator()(x, y)]++;
        }
    }
}

BW Table::operator()(int x, int y, int w, int h)
{
    BW bw {0, 0};
    for(int yy=0; yy<h; yy++)
    {
        BW bwRow = g[y+yy][x+w] - g[y+yy][x];
        bw = bw + bwRow;
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