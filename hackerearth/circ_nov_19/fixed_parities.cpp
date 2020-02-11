#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <sstream>

using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

template <typename T>
string toString(const vector<T>& v, string sep = " ")
{
    if(v.size() == 0)
        return "";
    stringstream ss;
    for(size_t i=0; i<v.size()-1; i++)
    {
        ss << v[i] << sep;
    }
    ss << v.back() << endl;
    return ss.str();
}

int main()
{
    int n;
    cin >> n;
    vector<int> X(n), Y(n);
    for(int i = 0; i < n; i++) {
        cin >> X[i];
        X[i] %= 2;
    }
    for(int i = 0; i < n; i++) {
        cin >> Y[i];
        Y[i] %= 2;
    }
    int q;
    cin >> q;
    auto pr = [&](int x, int y) { return (Y[y] + X[x]) % 2; };
    for(int qq = 0; qq < q; qq++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        if(pr(x1, y1) != pr(x2, y2)) {
            cout << "NO" << endl;
        }
        else {
            if(x1 > x2)
                swap(x1, x2);
            if(y1 > y2)
                swap(y1, y2);

            bool changeX = false;
            for(int x = 1; x < n; x++)
            if(X[0] != X[x]) {
                changeX = true;
                break;
            }
            bool changeY = false;
            for(int y = 1; y < n; y++)
            if(Y[0] != Y[y]) {
                changeY = true;
                break;
            }

            bool changeBetweenX = false;
            for(int x = x1+1; x <= x2; x++)
            if(X[x1] != X[x]) {
                changeBetweenX = true;
                break;
            }
            bool changeBetweenY = false;
            for(int y = y1+1; y <= y2; y++)
            if(Y[y1] != Y[y]) {
                changeBetweenY = true;
                break;
            }

            if(changeBetweenX && !changeY || changeBetweenY && !changeX)
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }
    }
}
