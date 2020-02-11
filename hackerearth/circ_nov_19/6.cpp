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
#include <numeric>

using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

i64 gcd(i64 a, i64 b){
	while(b){
		i64 bb = b;
		b = a % b;
		a = bb;
	}
	return a;
}

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

char results[10*1024];

struct P { i64 x, y; };

bool visible(int n, int x, int y)
{
    for(int xx = x; xx < x+n; xx++)
    for(int yy = y; yy < y+n; yy++)
    if(gcd(xx, yy) == 1)
        return true;
    return false;
}

P calc(i64 n)
{
    for(i64 x = n+1; ; x++)
    {
        i64 ap = x;
        for(i64 xx = x+1; xx <= x + n; xx++)
            ap *= xx;
        for(i64 y = n-1; y <= x; y++)
        {
            bool visible = [&]()
            {
                
            }();
            if(!visible)
                return P{x, y};
        }
    }
}

int main()
{
    i64 n;
    cin >> n;
    P p = calc(n);
    cout << p.x << " " << p.y << endl;
}
