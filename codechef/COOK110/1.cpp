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

i64 t[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        i64 A, B;
        cin >> A >> B;
        i64 C = A + B;
        i64 res = 0;
        if(C == 0)
            res = t[0];
        while(C) {
            res += t[C%10];
            C /= 10;
        }
        cout << res << endl;
    }
}