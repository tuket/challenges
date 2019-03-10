#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<unsigned> a =
        {1, 2, 3, 4, 5};
    const unsigned n = a.size();
    vector<unsigned> b(n);
    fill(b.begin(), b.end(), 1);
    // forward
    unsigned x = 1;
    for(unsigned i=0; i<n; i++) {
        b[i] *= x;
        x *= a[i];
    }
    x = 1;
    for(unsigned i=n-1; i<n; i--) {
        b[i] *= x;
        x *= a[i];
    }
    for(unsigned x : b)
        cout << x << " ";
    cout << endl;
}