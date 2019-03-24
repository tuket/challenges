#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main()
{
    vector<unsigned> v = {6, 1, 3, 3, 3, 6, 6};
    array<unsigned, 2> X = {0, 0};
    for(unsigned x : v)
    {
        unsigned w = X[1] & x;
        X[1] = ~w & x & X[0];
        X[0] = ~w & (X[0] ^ x);
    }
    cout << X[0] << endl;
}