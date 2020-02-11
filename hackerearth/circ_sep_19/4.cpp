#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <assert.h>

using namespace std;

typedef int64_t i64;

constexpr i64 MOD = 1'000'000'007;

/*
static vector<i64> F(2002 * 1002, +1);

i64& f(i64 n, i64 m = 0)
{
    assert(n >= 0 && n <= 2000 && m >= 0 && m <= 999);
    return F[n + 2001 * m];
}

void toHtml()
{
    ofstream fs("4.html");
    fs << "<html>" << endl;
    fs << "<table>" << endl;
    fs << "<tr>" << endl;
    fs << "<td></td> ";
    for(i64 n = 0; n <= 2000; n++)
        fs << "<td>" << n << "</td> ";
    fs << endl << "</tr>" << endl;

    for(i64 m = 0; m <= 999; m++) {
        fs << "<tr>" << endl;
        fs << "<td>" << m << "</td> ";
        for(i64 n = 0; n <= 2000; n++) {
            fs << "<td>" << F[n + 2001*m] << "</td> " << endl;
        }
        fs << endl << "</tr>" << endl;;
    }
    fs << "</table>" << endl;
    fs << "</html>" << endl;
}

i64 calcTable()
{
    for(i64 m=999; m >= 0; m--)
    {
        f(1, m) = m + 2;
        for(i64 n = 2; n <= 2*(1000 - 2*m); n++) {
            f(n, m) = f(n-1, m);
            f(n, m) += ((m+1) * f(n-2, m+1)) % MOD;
            f(n, m) %= MOD;
            //toHtml();20
        }
    }
    for(i64 n = 3; n <= 2000; n++)
        f(n, 0)--;
}
*/

static vector<i64> F(2002 * 1002, -1);

void toHtml()
{
    ofstream fs("4.html");
    fs << "<html>" << endl;
    fs << "<table>" << endl;
    fs << "<tr>" << endl;
    fs << "<td></td> ";
    for(i64 n = 0; n <= 2000; n++)
        fs << "<td>" << n << "</td> ";
    fs << endl << "</tr>" << endl;

    for(i64 m = 0; m <= 999; m++) {
        fs << "<tr>" << endl;
        fs << "<td>" << m << "</td> ";
        for(i64 n = 0; n <= 2000; n++) {
            fs << "<td>" << F[n + 2001*m] << "</td> " << endl;
        }
        fs << endl << "</tr>" << endl;;
    }
    fs << "</table>" << endl;
    fs << "</html>" << endl;
}

/*
i64 f(i64 n, i64 m = 0)
{
    if(n < 1)
        return 1;
    i64& entry = F[n + 2002*m];
    if(entry != -1)
        return entry;
    entry = (m == 0) ? 0 : 1;
    for(int i = 0; i < n; i++) {
        entry += ((m+1) * f(n-i-2, m+1)) % MOD;
        entry %= MOD;
    }
    return entry;
}
*/

i64 f(i64 n, i64 m = 0)
{
    if(n < 1)
        return 1;
    if(n == 1)
        return m+2;
    i64& entry = F[n + 2001*m];
    if(entry != -1)
        return entry;
    entry = 0;
    entry += f(n-1, m);
    entry %= MOD;
    entry += ((m+1) * f(n-2, m+1)) % MOD;
    entry %= MOD;
    return entry;
}

int main()
{
    //calcTable();
    i64 n;
    cin >> n;
    const i64 res = (f(n) + MOD -1) % MOD;
    if(n == 2)
        cout << 2 << endl;
    else
        cout << res << endl;
    //toHtml();
}