#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef long long ll;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        string s;
        getline(cin, s);
        getline(cin, s);
        vector<bool> v(n);
        for(int i=0; i<n; i++) {
            v[i] = s[i] == '#';
        }
        ll res = 0;
        int i = 0;
        for(; i<n && v[i]; i++);
        int k = i;
        int c = 0;
        for(; i<n; i++)
        {
            if(v[i]) {
                res += 2*c + i - k;
                c++;
                k++;
            }
            else if(c) c--;
        }
        if(c) cout << -1 << endl;
        else cout << res << endl;
    }
}