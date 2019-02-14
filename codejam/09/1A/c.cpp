#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

using namespace std;

double pt(int a, int b, int c, int d)
{
    static unordered_map<int, double> cache;
    const int index = d + 64*(c + 64*(b + 64*a));
    if(a < 0 || b < 0 || c < 0 || d < 0 ||
        c < d || b < d)
        return 0;
    if(c == 0) {
        if(d == 0)
            return 1;
        else
            return 0;
    }
    if(cache.count(index))
        return cache[index];
    double res = 0;
    if(a != 0)
        res += (double)a/(a+b) * pt(a-1, b, c-1, d);
    if(b != 0)
        res += (double)b/(a+b) * pt(a, b-1, c-1, d-1);
    cache[index] = res;
    return res;
};

double solve(int C, int c)
{
    vector<double> p(C+1, 0.f);
    vector<double> p2(C+1);
    p[0] = 1.f;
    double avg = 0;
    const int NS = 10000;
    for(int step=1; step<=NS; step++)
    {
        fill(p2.begin(), p2.end(), 0.f);
        for(int i=0; i<C+1; i++)
        {
            for(int j=i; j < min(C+1, i+c+1); j++)
            {
                p2[j] += p[i] * pt(i, C-i, c, j-i);
            }
        }
        p.swap(p2);
        avg =  avg + (p[C] - p2[C]) * step;
    }
    return avg;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int C, c;
        cin >> C >> c;
        cout << setprecision(7);
        cout << fixed;
        cout << "Case #" << kk << ": " << solve(C, c) << endl;
    }
}