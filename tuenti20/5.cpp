#include <iostream>
#include <inttypes.h>

using namespace std;

typedef int64_t i64;

int main()
{
    int nn;
    cin >> nn;
    for(int kk = 1; kk <= nn; kk++)
    {
        i64 x;
        cin >> x;
        i64 n = x / 20;
        i64 r = x % 20;
        cout << "Case #" << kk << ": ";
        if(r <= n * 9) {
            cout << n << endl;
        }
        else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
}