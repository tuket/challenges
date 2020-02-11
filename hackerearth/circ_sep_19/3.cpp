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

int main()
{
    int an, bn, cn;
    cin >> an >> bn >> cn;
    string a, b, c;
    cin >> a >> b >> c;
    vector<int> v(bn);
    v[bn-1] = bn-1;
    for(int i = b.size()-2; i >= 0 ; i--) {
        if(b[i] <= b[v[i+1]])
            v[i] = i;
        else
            v[i] = v[i+1];
    }

    bool goesUp = false;
    for(int i=1; i<c.size(); i++) {
        if(c[i] != c[0]) {
            goesUp = c[i] > c[0];
            break;
        }
    }

    string s;
    int i = v[0];
    while((b[i] < c[0] || (b[i] == c[0] && goesUp)) && i < b.size())
    {
        s += b[i];
        if(i+1 < b.size())
            i = v[i+1];
        else
            break;
    }

    cout << a << s << c << endl;
}