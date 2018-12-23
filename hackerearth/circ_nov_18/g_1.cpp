#include <iostream>
#include <string>
#include <array>
#include <vector>

using namespace std;

typedef unsigned long long ul;

array<vector<ul>, 11> a;

int main()
{
    cout << "{" << endl;
    for(int b=0; b<=10; b++)
    {
        cout << "vector<ul>{";
        ul x = b;
        while(2*x < 2*x*b)
        {
            cout << 2*x << "ULL, ";
            x *= b;
        }
        cout << "}," << endl;
    }
    cout << "};" << endl;
}