#include <iostream>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n, k;
        cin >> n >> k;
        bool w = n % (k+1) != 0;
        cout << (w ? "Arpa" : "Dishant") << endl;
    }
}