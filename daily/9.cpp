#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v{5, 1, 1, 5};
    int x0 = 0;
    int x1 = v[0];
    for(int i=1; i<v.size(); i++) {
        int x2 = max(x0+v[i], x1);
        x0 = x1;
        x1 = x2;
    }
    cout << x1 << endl;
}

