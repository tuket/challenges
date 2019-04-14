#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        vector<char> ss;
        {
            string s;
            cin >> s;
            ss = vector<char>(s.begin(), s.end());
        }
        bool allDec = true;
        for(int i=0; i<ss.size()-1; i++)
        {
            if(ss[i] < ss[i+1]) {
                allDec = false;
                break;
            }
        }
        if(allDec) {
            int si = 0;
            char smallestNonZero = ss[0];
            for(int i=0; i<ss.size(); i++) {
                if(ss[i] != '0' && ss[i] < smallestNonZero) {
                    smallestNonZero = ss[i];
                    si = i;
                }
            }
            swap(ss[0], ss[si]);
            sort(ss.begin()+1, ss.end());
            ss.insert(ss.begin() + 1, '0');
            string s(ss.begin(), ss.end());
            cout << "Case #" << kk << ": " << s << endl;
        }
        else {
            for(int i=ss.size()-2; i >= 0; i--)
            {
                char minGreater = '9' + 1;
                int jj = -1;
                for(int j=i+1; j<ss.size(); j++) {
                    if(ss[j] > ss[i] && ss[j] < minGreater) {
                        minGreater = ss[j];
                        jj = j;
                    }
                }
                if(jj != -1) {
                    swap(ss[i], ss[jj]);
                    sort(ss.begin() + i+1, ss.end());
                    break;
                }
            }
            string s(ss.begin(), ss.end());
            cout << "Case #" << kk << ": " << s << endl;
        }
    }
}