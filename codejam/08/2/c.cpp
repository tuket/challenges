#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef long long ll;

struct SS {
    ll x, y, z, p;
};

struct RE {
    double minA, maxA;
    double minB, maxB;
    double minC, maxC;
    double minD, maxD;
};

RE getRombaedrum(const SS& ss, double P)
{
    double d = P * ss.p;
    RE res = {
        +ss.x+ss.y-ss.z-d, +ss.x+ss.y-ss.z+d,
        +ss.x+ss.y+ss.z-d, +ss.x+ss.y+ss.z+d,
        -ss.x+ss.y+ss.z-d, -ss.x+ss.y+ss.z+d,
        +ss.x-ss.y+ss.z-d, +ss.x-ss.y+ss.z+d
    };
    return res;
}

bool intersect(RE& A, const RE& B)
{
    A.minA = max(A.minA, B.minA);
    A.maxA = min(A.maxA, B.maxA);
    A.minB = max(A.minB, B.minB);
    A.maxB = min(A.maxB, B.maxB);
    A.minC = max(A.minC, B.minC);
    A.maxC = min(A.maxC, B.maxC);
    A.minD = max(A.minD, B.minD);
    A.maxD = min(A.maxD, B.maxD);
    return
        A.minA <= A.maxA &&
        A.minB <= A.maxB &&
        A.minC <= A.maxC &&
        A.minD <= A.maxD;
}

bool intersect(const vector<SS>& v, double P)
{
    RE common = getRombaedrum(v[0], P);
    for(int i=1; i<v.size(); i++)
    {
        if(!intersect(common, getRombaedrum(v[i], P)))
            return false;
    }
    return true;
}

double solve(const vector<SS>& v)
{
    double lb = 0;
    double ub = 1e15;
    while(lb + 1e-9 < ub)
    {
        double P = (lb+ub) / 2;
        if(intersect(v, P)) {
            ub = P;
        }
        else {
            lb = P;
        }
    }
    return ub;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<SS> v(n);
        for(SS& ss : v) {
            cin >> ss.x;
            cin >> ss.y;
            cin >> ss.z;
            cin >> ss.p;
        }
        double res = solve(v);
        printf("Case #%d: %.6f\n", kk, res);
    }
}