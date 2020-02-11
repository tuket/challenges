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

int main()
{
    i64 n, k, m;
    cin >> n >> k >> m;
    string s;
    cin >> s;
    string initS = s;
    i64 co = 0;
    for(i64 i = 0; i < k; i++) {
        if(s[i] == '1') {
            co++;
            if(co > m) {
                s[i] = '0';
                co--;
            }
        }
    }
    
    i64 i = 0;
    for(i64 j = k; j < n; i++, j++)
    {
        if(s[i] == '1')
            co--;
        if(s[j] == '1')
            co++;
        if(co > m) {
            s[j] = '0';
            co--;
        }
    }

    i64 res = 0;
    for(i = 0; i < n; i++)
    if(initS[i] != s[i])
        res++;
    cout << res << endl;
    cout << s << endl;
}
