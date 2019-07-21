#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

struct P
{
    int i, j;
    bool operator<(const P& o)const {
        int dif = j-i;
        int odif = o.j-o.i;
        return !(
            dif < odif ? true :
            dif > odif ? false :
            i < o.i ? true :
            i > o.i ? false :
            j < o.j);
    }
};

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n, p;
        cin >> n >> p;
        vector<int> pp(p);
        for(int& x : pp) {
            cin >> x;
            x--;
        }
        sort(pp.begin(), pp.end());
        vector<P> intervals;
        {
            int beg = pp[0];
            for(int i=1; i<pp.size(); i++) {
                int cur = pp[i];
                int prev = pp[i-1];
                if(cur > prev+1) {
                    intervals.push_back({beg, prev});
                    beg = cur;
                }
            }
            intervals.push_back({beg, pp.back()});
        }
        sort(intervals.begin(), intervals.end());

        int res = 0;
        while(p && intervals.size())
        {
            P ij = intervals.back();
            int i = ij.i;
            int j = ij.j;
            intervals.pop_back();
            if(i <= j)
            {
                if(i < j)
                {
                    res += j-i;
                    P a {i, (i+j)/2-1};
                    P b {(i+j)/2+1, j};
                    intervals.push_back(b);
                    intervals.push_back(a);
                }
                p--;
            }
        }

        cout << "Case #" << kk << ": " << res << endl;
    }
}