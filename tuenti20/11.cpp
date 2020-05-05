#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <sstream>
#include <set>

using namespace std;

typedef int8_t i8;
typedef int32_t i32;

i32 n;
i32 x;
i8 d[101];
i32 tot = 0;

void f(i32 i, i32 rem, i32 l)
{
    if(i == n-1) {
        l += (i32)rem / (i32)d[i];
        if(rem % d[i] == 0 && l > 1)
            tot++;
    }
    else {
        i32 lp = 0;
        while(rem >= 0) {
            f(i+1, rem, l+lp);
            rem -= d[i];
            lp += 1;
        }
    }
}

int main()
{
    int tmp;
    i8 nn;
    cin >> tmp;
    nn = tmp;
    string line; getline(cin, line);
    for(i8 kk = 1; kk <= nn; kk++)
    {
        getline(cin, line);
        stringstream ss;
        ss << line;
        ss >> x;
        i32 nExcl = 0;
        for(i32 i = 0; i < line.size(); i++)
            if(line[i] == ' ')
                nExcl++;
        set<i32> a;
        for(i32 i = 0; i < x-1; i++)
            a.insert(i+1);
        for(i32 i = 0; i < nExcl; i++) {
            ss >> tmp;
            a.erase(tmp);
        }
        n = 0;
        for(i32 i : a) {
            d[a.size()-n-1] = i;
            n++;
        }
        tot = 0;
        f(0, x, 0);
        cout << "Case #" << int(kk) << ": " << tot << endl;
    }
}