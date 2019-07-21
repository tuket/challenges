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
        vector<int> xx;
        xx.reserve(n);
        for(int i=0; i<n; i++) {
            string s;
            cin >> s;
            int x;
            for(x=s.size()-1; x >= 0; x--) {
                if(s[x] == '1')
                    break;
            }
            xx.push_back(x);
        }
        int res = 0;
        for(int i=0; i<n; i++) {
            int x = xx[i];
            if(x > i) {
                for(int j=i+1; j<n; j++) {
                    int y = xx[j];
                    if(y <= i) {
                        for(int ij=j; ij>i; ij--) {
                            xx[ij] = xx[ij-1];
                        }
                        xx[i] = y;
                        res += (j-i);
                        break;
                    }
                }
            }
        }
        cout << "Case #" << kk << ": " << res << endl;
    }
}