#include <bits/stdc++.h>

using namespace std;

int c(char x)
{
    return x - '0';
}

int main()
{
    string s;
    int nn;
    ifstream fs("B-large-practice.in");
    //istream& fs = cin;
    fs >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int T;
        int AB[2] = {0, 0};
        vector<tuple<int, int, bool>> a[2];
        fs >> T;
        fs >> AB[0];
        fs >> AB[1];
        getline(fs, s);
        for(int ai = 0; ai < 2; ai++)
        {
            a[ai] = vector<tuple<int, int, bool>>(AB[ai]);

            for(int i=0; i<AB[ai]; i++)
            {
                getline(fs, s);
                int h = c(s[0]) * 10 + c(s[1]);
                int m = c(s[3]) * 10 + c(s[4]);
                get<0>(a[ai][i]) = 60 * h + m;
                h = c(s[6]) * 10 + c(s[7]);
                m = c(s[9]) * 10 + c(s[10]);
                get<1>(a[ai][i]) = 60 * h + m + T;
                get<2>(a[ai][i]) = false;        
            }
            sort(a[ai].begin(), a[ai].end());
        }

        if(AB[0] == 0 && AB[1] == 0) {
            cout << "Case #" << kk << ": 0" << endl;
            continue;
        }

        int res[] = {0, 0};
        int n = 0;
        int ai;
        while(n != AB[0] + AB[1]) {
            int ij[2];
            for(int ai = 0; ai < 2; ai++) for(ij[ai] = 0; ij[ai]<AB[ai] && get<2>(a[ai][ij[ai]]); ij[ai]++);
            if(ij[0] == AB[0]) ai = 1;
            else if(ij[1] == AB[1]) ai = 0;
            else {
                if(a[0][ij[0]] < a[1][ij[1]])
                    ai = 0;
                else
                    ai = 1;
            }
            res[ai]++;

            while(true)
            {
                int ni = 1-ai;
                auto& cur = a[ai][ij[ai]];
                int t = get<1>(cur);
                get<2>(cur) = true;
                n++;
                for(;ij[ni] < AB[ni]; ij[ni]++) {
                    auto& next = a[ni][ij[ni]];
                    if(!get<2>(next) && get<0>(next) >= t) {
                        ai = ni;
                        break;
                    }
                }
                if(ij[ni] == AB[ni]) break;
            }
        }

        cout << "Case #" << kk << ": " << res[0] << " " << res[1] << endl;
    }
}