#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i=0; i<n; i++)
            cin >> v[i];
        
        int miss = 0;
        for(int i=0; i<n-1; i++)
        {
            if(v[i+1] < v[i])
            {
                miss++;
                if(miss > 1)
                    break;
            }
        }
        bool yes = false;
        if(miss == 0)
            yes = true;
        else if(miss == 1)
        {
            yes = v[n-1] <= v[0];
        }
        cout << (yes ? "YES" : "NO") << endl;
    }
}