#include <bits/stdc++.h>

using namespace std;

const double PI = atan(1) * 4;

double normalSquare(double f, double R, double t, double r, double g)
{
    if(g < 2*f) return 0;
    return (g - 2*f) * (g - 2*f);
}

vector<int> // last one is the number of full squares
squares(double f, double R, double t, double r, double g)
{
    vector<int> res;
    int n = 0;
    double R2 = (R-t) * (R-t);
    double R2f = (R-t-f) * (R-t-f);
    double x = r + g;
    auto dist = [](double x){return 2*x*x;};
    if(dist(x) <= R2)
    do {
        n++;
        x += 2*r + g;
    }
    while(dist(x) <= R2);

    int en = 0;
    x = r;
    if(x <= (R-t))
    do {
        en++;
        x += 2*r + g;
    }
    while(x <= (R-t));

    int nn = 4 * n*n;
    double y;
    auto loopFunc = [&](int i, int j)
    {
        x = r + (i-1) * (2*r + g);
        y = r + (j-1) * (2*r + g);
        if((x+f)*(x+f) + (y+f)*(y+f) < R2f) {
            if((x+g-f)*(x+g-f) + (y+g-f)*(y+g-f) < R2f) {
                nn += 4;
            }
            else {
                res.push_back(i);
                res.push_back(j);
            }
        }
    };
    for(int i=1; i <= en; i++)
    for(int j=n+1; j <= en; j++)
    {
        loopFunc(i, j);
    }
    for(int i=n+1; i <= en; i++)
    for(int j=1; j <= n; j++)
    {
        loopFunc(i, j);
    }
    res.push_back(nn);
    return res;
}

double inter(double x1, double x2, double y1, double y2, double r)
{
    if(x1 >= x2 || y1 >= y2) return 0;

    double toAdd = 0;
    double xr1, xr2, yr1, yr2, px, py;
    yr1 = sqrt(r*r - x1*x1);
    if(yr1 <= y2) {
        xr1 = x1;
        py = yr1;
    }
    else {
        xr1 = sqrt(r*r - y2*y2);
        yr1 = y2;
        double ax = xr1 - x1;
        double ay = ax * y2  / xr1;
        toAdd += 0.5 * ax*ay;
        py = y2 - ay;
    }

    xr2 = sqrt(r*r - y1*y1);
    if(xr2 <= x2) {
        yr2 = y1;
        px = xr2;
    }
    else {
        yr2 = sqrt(r*r - x2*x2);
        xr2 = x2;
        double ay = yr2 - y1;
        double ax = x2 * ay / yr2;
        toAdd += 0.5 * ax * ay;
        px = x2 - ax;
    }

    double toSubs = 0;
    toSubs += 0.5 * x1 * (py - y1);
    toSubs += 0.5 * y1 * (px - x1);

    double alpha = atan2(yr1, xr1) - atan2(yr2, xr2);

    double res = 0.5 * r*r * alpha;
    res -= toSubs;
    res += toAdd;

    return max(0.0, res);
}

double compute(double f, double R, double t, double r, double g)
{
    vector<int> v = squares(f, R, t, r, g);
    double area = normalSquare(f, R, t, r, g) * v.back();

    for(int i=0; i<(int)v.size()-1; i+=2)
    {
        int ix = v[i];
        int iy = v[i+1];
        double x1 = r + (ix-1) * (g + 2*r) + f;
        double x2 = r + (ix-1) * (g + 2*r) + g - f;
        double y1 = r + (iy-1) * (g + 2*r) + f;
        double y2 = r + (iy-1) * (g + 2*r) + g - f;
        area += 4 * inter(x1, x2, y1, y2, R - t - f);
    }

    return area;
}

int main()
{
    //ifstream fs("in.txt");
    istream& fs = cin;
    int nn;
    fs >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        double f, R, t, r, g;
        fs >> f >> R >> t >> r >> g;

        double ta = PI * R*R;
        double a = compute(f, R, t, r, g);

        printf("Case #%d: %.6f\n", kk, 1.0 - a / ta);
        //cout << "Case #" << kk << ": " <<  << endl;
    }
}