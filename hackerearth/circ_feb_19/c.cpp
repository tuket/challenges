#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct Pos
{
    int x, y;
    Pos operator+(const Pos& o)const
    {
        Pos res{x+o.x, y+o.y};
        return res;
    }
    Pos operator-(const Pos& o)const
    {
        Pos res{x-o.x, y-o.y};
        return res;
    }
    double len()const{ return hypot(x, y); }
    double len2()const{ return (double)x*x + (double)y*y; }
    double dist(const Pos& o)const { hypot(x-o.x, y-o.y); }
    double dist2(const Pos& o)const { return (*this-o).len2(); }
};

int main()
{
    random_device rd;
    mt19937 re(rd());

    int nh, poleCost, maxK, maxPoles;
    cin >> nh >> poleCost >> maxK >> maxPoles;
    const int minPoles = nh / maxK + (nh%maxK != 0);
    int nPoles = (minPoles+maxPoles) / 2;
    vector<Pos> posHouses(nh);
    for(int i=0; i<nh; i++) {
        cin >> posHouses[i].x >> posHouses[i].y;
    }
    // random poles positions
    vector<Pos> posPoles(nPoles);
    {
        vector<int> indices(nh);
        iota(indices.begin(), indices.end(), 0);
        for(int pi=0; pi < nPoles; pi++) {
            uniform_int_distribution<int> dist(0, indices.size()-1);
            int i = dist(re);
            int hi = indices[i];
            posPoles[pi] = posHouses[hi];
            indices[i] = indices.back();
            indices.pop_back();
        }
    }
    // the houses assigned to each pole
    vector<vector<int>> hPoles(nPoles);
    for(int i=0; i<nh; i++)
    {
        double minDist = numeric_limits<double>::max();
        int minPi = -1;
        for(int pi=0; pi<nPoles; pi++)
        if(hPoles[pi].size() < maxK)
        {
            double d2 = posPoles[pi].dist2(posHouses[i]);
            if(d2 < minDist) {
                minPi = pi;
                minDist = d2;
            }
        }
        hPoles[minPi].push_back(i);
    }

    cout << nPoles << endl;
    for(int pi; pi < nPoles; pi++) {
        cout << posPoles[pi].x << " " << posPoles[pi].y
            << " " << hPoles[pi].size();
        for(int i : hPoles[pi])
            cout << " " << i+1;
        cout << endl;
    }
}