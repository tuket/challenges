#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        vector<string> w(n);
        for(int i=0; i<n; i++)
            cin >> w[i];
        
        set<string> seen;
        int tt = 0;
        for(int j=0; j<n; j++)
        {
            char prev = 0;
            int t = 0;
            for(int i=0; i<w[j].size(); i++)
            {
                char cur = w[j][i];
                if(prev == 0)
                    t += 2;
                else if(prev == 'd' || prev == 'f')
                {
                    if(cur == 'd' || cur == 'f')
                        t += 4;
                    else
                        t += 2;
                }
                else {
                    if(cur == 'd' || cur == 'f')
                        t += 2;
                    else
                        t += 4;
                }
                prev = cur;
            }
            if(seen.count(w[j]))
                t /= 2;
            tt += t;
            seen.insert(w[j]);
        }
        cout << tt << endl;
    }
}