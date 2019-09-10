#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include <algorithm>

using namespace std;

struct Pos {
    double x, y;
};

Pos operator+(Pos a, Pos b) {
    return {a.x + b.x, a.y + b.y};
}

Pos operator*(double a, Pos b) {
    return {a * b.x, a * b.y};
}

double distanceSquared(Pos a, Pos b)
{
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

double distance(Pos a, Pos b) {
    return sqrt(distanceSquared(a, b));
}

struct Plant {
    Pos p;
    double r;
};

double binarySearch(double from, double to, const function<bool(double)>& fn)
{
    while(from < to - 0.000001)
    {
        const double mid = 0.5 * (from + to);
        const bool enough = fn(mid);
        if(enough)
            to = mid;
        else
            from = mid;
    }
    return from;
}

bool isPlantCovered(Pos spk, double r, const Plant& plant)
{
    //const double d = distance(spk, plant.p);
    const double d2 = distanceSquared(spk, plant.p);
    //return d + plant.r < r;
    return d2 - 0.00000001 <= (r - plant.r) * (r - plant.r);
}

bool areAllPlantsCoveredWithOneSprinkler(vector<bool>& covered,
    const Pos& spk, double r, const vector<Plant>& plants)
{
    const int n = plants.size();
    for(int i=0; i<n; i++) {
        const Plant& plant = plants[i];
        covered[i] = isPlantCovered(spk, r, plant);
    }
    return all_of(covered.begin(), covered.end(), [](bool b){return b;});
}

bool areAllPlantsCovered(const vector<bool>& covered, const Pos& spk, double r, const vector<Plant>& plants)
{
    const int n = plants.size();
    for(int i=0; i<n; i++) {
        const Plant& plant = plants[i];
        if(!covered[i] && !isPlantCovered(spk, r, plant))
            return false;
    }
    return true;
}

struct TwoCircIntersectResult {
    bool valid;
    Pos p1, p2;
};

TwoCircIntersectResult calcTwoCircIntersect(Pos p1, double r1, Pos p2, double r2)
{
    TwoCircIntersectResult res;
    const double d = distance(p1, p2);
    const double l = (r1*r1 - r2*r2 + d*d) / (2*d);
    const double h_2 = r1*r1 - l*l;
    if(h_2 < 0) {
        res.valid = false;
        return res;
    }
    res.valid = true;
    const double h = sqrt(h_2);
    const double xa = (l / d) * (p2.x - p1.x) + p1.x;
    const double xb = (h / d) * (p2.y - p1.y);
    res.p1.x = xa + xb;
    res.p2.x = xa - xb;
    const double ya = (l / d) * (p2.y - p1.y) + p1.y;
    const double yb = (h / d) * (p2.x - p1.x);
    res.p1.y = ya - yb;
    res.p2.y = ya + yb;
    return res;
}

TwoCircIntersectResult calcCircPosTangentToTwoCircs(double R, Pos p1, double r1, Pos p2, double r2)
{
    return calcTwoCircIntersect(p1, R-r1, p2, R-r2);
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<Plant> P(n);
        double largestPlant = 0;
        for(int i=0; i<n; i++) {
            cin >> P[i].p.x >> P[i].p.y >> P[i].r;
            largestPlant = max(largestPlant, P[i].r);
        }

        const double minRad =
        binarySearch(largestPlant, 99999999.0,
        [&](double r)
        {
            vector<Pos> candidates;
            for(Plant plant : P) {
                candidates.push_back({plant.p.x, plant.p.y});
            }
            for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++) {
                const auto res = calcCircPosTangentToTwoCircs(r, P[i].p, P[i].r, P[j].p, P[j].r);
                if(res.valid) {
                    candidates.push_back(res.p1);
                    candidates.push_back(res.p2);
                }
            }

            for(int i=0; i<candidates.size(); i++) {
                vector<bool> covered(n, false);
                const Pos& p1 = candidates[i];
                if(areAllPlantsCoveredWithOneSprinkler(covered, p1, r, P))
                    return true;
                for(int j=i+1; j<candidates.size(); j++) {
                    const Pos& p2 = candidates[j];
                    if(areAllPlantsCovered(covered, p2, r, P))
                        return true;
                }
            }
            return false;
        });
        
        printf("Case #%d: %.8f\n", kk, minRad);
        //cout << "Case #" << kk << ": " << minRad << endl;
    }
}