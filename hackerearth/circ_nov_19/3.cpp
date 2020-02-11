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
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        
    }
}
