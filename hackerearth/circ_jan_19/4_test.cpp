#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <string>
#include <memory>
#include <sstream>
#include <cstring>

using namespace std;

#define TEST
#include "4.cpp"
#include "4_simpl.cpp"

int main()
{
    srand(time(NULL));
    int64_t R = 4LL;
    int n = 3;
    vector<int64_t> v(n);
    while(true)
    {
        for(int64_t& x : v)
            x = -R + rand() % (2*R);

        array<int64_t, 2> a1 = solveSimpl(n, v);
        array<int64_t, 2> a2 = solve(n, v);

        if(a1 != a2)
        {
            for(int64_t x : v)
                cout << x << " ";
            cout << endl;
            cout << a1[0] << " " << a1[1] << endl;
            cout << a2[0] << " " << a2[1] << endl;
            cout << "-------------------" << endl;
        }
    }

}