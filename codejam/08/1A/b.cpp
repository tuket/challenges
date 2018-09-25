#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>

using namespace std;

struct Mk {int x, y;};

bool isUnhappy(const vector<Mk>& c, const vector<int>& m)
{
    return none_of(c.begin(), c.end(),
    [&](const Mk& mk)
    {
        return m[mk.x] == mk.y;
    });
}

int getUnhappy(const vector<vector<Mk>>& mks, const vector<int>& m)
{
    const int C = mks.size();
    vector<int> res;
    for(int c=0; c<C; c++)
    if(isUnhappy(mks[c], m))
    {
        return c;
    }
    return -1;
}

bool solve(const vector<vector<Mk>>& mks, vector<int>& m)
{
    int c;
    while((c = getUnhappy(mks, m)) != -1)
    {
        bool noOne = true;
        for(const Mk& mk : mks[c])
        if(mk.y == 1)
        {
            m[mk.x] = 1;
            noOne = false;
        }
        if(noOne)
            return false;
    }
    return true;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int N, C;
        cin >> N >> C;
        vector<int> m(N, 0);
        vector<vector<Mk>> mks(C);
        for(int c=0; c<C; c++)
        {
            int n;
            cin >> n;
            mks.reserve(n);
            for(int i=0; i<n; i++)
            {
                int x, y;
                cin >> x >> y;
                mks[c].push_back({x-1, y});
                if(n == 1) {
                    m[x-1] = y;
                }
            }
        }

        bool possible = solve(mks, m);

        cout << "Case #" << kk << ":";
        if(!possible)
            cout << " IMPOSSIBLE" << endl;
        else {
            for(int i=0; i<N; i++)
            {
                cout << " " << m[i];
            }
            cout << endl;
        }
    }
}