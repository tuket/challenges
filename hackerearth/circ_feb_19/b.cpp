#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int nt, nb;
    cin >> nt >> nb;
    vector<int> bp(nb, 0);
    for(int i=0; i<nt; i++)
    {
        int p, b;
        cin >> p >> b;
        b--;
        bp[b] = max(bp[b], p);
    }
    int res = 0;
    for(int p : bp)
        res += p;
    cout << res << endl;
}