#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef int64_t i64;

i64 costOnline(i64 d, i64 baseCost, i64 baseKm, i64 priceKm)
{
    i64 res = baseCost;
    if(d > baseKm)
        res += (d - baseKm) * priceKm;
    return res;
}

i64 costClassic(i64 d, i64 speed, i64 base, i64 priceMin, i64 priceKm)
{
    i64 res = base;
    res += d * priceKm;
    res += ((d + speed - 1) / speed) * priceMin;
    return res;
}

int main()
{
    i64 D,
        Oc, Of, Od,
        Cs, Cb, Cm, Cd;
    cin >> D
        >> Oc >> Of >> Od
        >> Cs >> Cb >> Cm >> Cd;

    if(costOnline(D, Oc, Of, Od) < costClassic(D, Cs, Cb, Cm, Cd))
        cout << "Online Taxi" << endl;
    else
        cout << "Classic Taxi" << endl;
}