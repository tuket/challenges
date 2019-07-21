#include <iostream>
#include <array>
#include <vector>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

template <typename T, unsigned DIMENSIONS>
struct Table
{
    static_assert(DIMENSIONS > 0, "!");

    array<int, DIMENSIONS> dims;
    vector<T> values;

    Table() {}
    Table(array<int, DIMENSIONS> dims)
        : dims(dims)
    {
        int n = 1;
        for(int d : dims) n *= d;
        values.resize(n);
    }

    void setAll(const T& val) { for(auto x : values) x = val; }

    typename vector<T>::reference operator()(const array<int, DIMENSIONS>& indices) {
        int i = getOneIndex(indices);
        return values[i];
    }
    typename vector<T>::const_reference operator()(const array<int, DIMENSIONS>& indices)const {
        int i = getOneIndex(indices);
        return values[i];
    }

    template <typename... Args>
    typename vector<T>::reference operator()(Args... indices)
    {
        int i = getOneIndex({indices...});
        return values[i];
    }

    template <typename... Args>
    typename vector<T>::const_reference operator()(Args... indices)const
    {
        int i = getOneIndex({indices...});
        return values[i];
    }

    int getOneIndex(const array<int, DIMENSIONS>& indices)const {
        int i = 0;
        int n = 1;
        for(int j = 0; j < indices.size(); j++) {
            assert(indices[j] >= 0 && indices[j] < dims[j]);
            i *= n;
            i += indices[DIMENSIONS - j - 1];
            n *= dims[j];
        }
        return i;
    }

    int size(int i)const {
        assert(i >= 0 && i < DIMENSIONS);
        return dims[i];
    }

    int rows()const{ return dims[0]; }
    int cols()const{ return dims[1]; }

    int W()const{ return dims[0]; }
    int H()const{ return dims[1]; }
};

struct P { int r, c; };

P operator+(P a, P b) { return {a.r + b.r, a.c + b.c}; }
P operator-(P a, P b) { return {a.r - b.r, a.c - b.c}; }

struct Sol
{
    Sol() : m(0), count(0) { visited.setAll(false); }
    int m;
    int count;
    vector<P> route;
    Table<bool, 2> visited;
};

vector<P> solve(const Table<int, 2>& g)
{
    static const array<P, 4> dirs = {P{-1, 0}, {0, -1}, {+1, 0}, {0, +1}};
    static const array<P, 4> sideDirs = {P{0, -1}, {-1, 0}, {0, +1}, {+1, 0}};
    const int R = g.rows();
    const int C = g.cols();

    unordered_map<int, int> numGreater;

    Table<Sol, 2> bestSol({R, C});
    for(int r=0; r<R; r++)
    for(int c=0; c<C; c++) {
        bestSol(r, c).count = numeric_limits<int>::max();
    }

    Sol initSol;
    initSol.m = g(0, 0);
    initSol.route.push_back({0, 0});
    initSol.visited = Table<bool, 2>({R, C});
    initSol.visited(0, 0) = true;
    queue<Sol> q;
    q.push(initSol);
    while(!q.empty())
    {
        Sol s = q.front();
        q.pop();
        P p = s.route.back();
        if(s.route.size() == R * C) {
            if(s.count < bestSol(p.r, p.c).count) {
                bestSol(p.r, p.c) = s;
            }
            continue;
        }

        auto canBeThere = [&](P p) -> bool {
            return p.r >= 0 && p.c >= 0 &&
                p.r < R && p.c < C &&
                !s.visited(p.r, p.c);
        };
        
        for(int idir = 0; idir < 4; idir++) {
            P fwd = dirs[idir];
            P dest = p + fwd;
            if(!canBeThere(dest))
                continue;

            if(!canBeThere(dest + fwd) &&
                canBeThere(p + sideDirs[idir]) && canBeThere(p - sideDirs[idir])
            ) continue;

            Sol newSol;
            newSol.route = s.route;
            newSol.route.push_back(dest);
            newSol.count = s.count;
            int newVal = g(dest.r, dest.c);
            if(newVal > s.m) {
                newSol.count++;
                newSol.m = newVal;
            }
            else {
                newSol.m = s.m;
            }
            newSol.visited = s.visited;
            newSol.visited(dest.r, dest.c) = true;
            q.push(newSol);
        }
    }

    int bestCount = bestSol(0, 0).count;
    int bestRow, bestCol;
    bestRow = bestCol = 0;
    for(int r=0; r<R; r++)
    for(int c=0; c<C; c++) {
        if(bestSol(r, c).count < bestCount) {
            bestRow = r;
            bestCol = c;
        }
    }
    return bestSol(bestRow, bestCol).route;
}

int main()
{
    int R, C;
    cin >> R >> C;
    Table<int, 2> g({R, C});
    for(int r=0; r<R; r++)
    for(int c=0; c<C; c++) {
        cin >> g(r, c);
    }

    vector<P> sol = solve(g);

    for(P p : sol)
        cout << p.r << " " << p.c << endl;
}